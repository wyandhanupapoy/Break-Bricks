#include <raylib.h>
#include "BOLA.h"
#include "sound.h"   // For PlaySfx
#include "paddle.h"  // For PaddleNode definition (to access rect)
#include "powerup.h" // For AddPowerUp and PowerUpType (if needed directly)
#include "LinkedList-Block.h" // For NodeBlock
#include <stdlib.h>
#include <float.h>
#include <raymath.h> // For Vector2Length, Vector2Normalize, Vector2Scale, Vector2Distance

// Game area dimensions, consistent with paddle.c
#define SCREEN_W 830
#define SCREEN_H 600

#define MIN_BALL_SPEED 6.0f
#define MAX_BALL_SPEED 9.0f

void InitBola(BolaList* list) {
    if(!list) return;
    list->head = NULL;
    // Add initial ball
    AddBola(list, (Vector2){SCREEN_W / 2.0f, SCREEN_H / 2.0f}, (Vector2){GetRandomValue(-1,1)? MIN_BALL_SPEED : -MIN_BALL_SPEED, -MIN_BALL_SPEED});
}

void AddBola(BolaList* list, Vector2 position, Vector2 speed) {
    if(!list) return;
    BolaNode* newBall = (BolaNode*)malloc(sizeof(BolaNode));
    if (newBall == NULL) return;

    // Clamp speed values
    speed.x = fminf(fmaxf(speed.x, -MAX_BALL_SPEED), MAX_BALL_SPEED);
    speed.y = fminf(fmaxf(speed.y, -MAX_BALL_SPEED), MAX_BALL_SPEED);
    // Ensure minimum vertical speed if speed.y is too low (e.g. 0)
    if (fabsf(speed.y) < MIN_BALL_SPEED / 2) speed.y = (speed.y >=0 ? 1:-1) * MIN_BALL_SPEED/2;


    newBall->position = position;
    newBall->speed = speed;
    newBall->radius = 10;
    newBall->color = RED; // Or make it a parameter
    newBall->active = true;
    newBall->next = list->head;
    list->head = newBall;
}

void UpdateBola(BolaList* list, PaddleList* paddleList,
              LinkedList* blockList, GameState* state,
              Skor* skor, Stopwatch* stopwatchList,
              PowerUpList* powerUpList) {
    if (!list) return;

    BolaNode* prev = NULL;
    BolaNode* curr = list->head;

    while (curr != NULL) {
        if (!curr->active) {
            BolaNode* toDelete = curr;
            if (prev == NULL) {
                list->head = curr->next;
                curr = list->head;
            } else {
                prev->next = curr->next;
                curr = curr->next;
            }
            free(toDelete);
            continue;
        }

        if (*state == GAME_PLAY || *state == GAME_START) {
            curr->position.x += curr->speed.x;
            curr->position.y += curr->speed.y;

            float currentSpeedMag = Vector2Length(curr->speed);
            if (currentSpeedMag > MAX_BALL_SPEED) {
                curr->speed = Vector2Scale(Vector2Normalize(curr->speed), MAX_BALL_SPEED);
            } else if (currentSpeedMag < MIN_BALL_SPEED && currentSpeedMag > 0) {
                 curr->speed = Vector2Scale(Vector2Normalize(curr->speed), MIN_BALL_SPEED);
            }


            // Wall collision
            if (curr->position.x <= curr->radius) { // Left wall
                curr->speed.x *= -1;
                curr->position.x = curr->radius;
                PlaySfx("paddle_hit"); // Using paddle_hit for wall bounce, or a new sound
            }
            if (curr->position.x >= SCREEN_W - curr->radius) { // Right wall
                curr->speed.x *= -1;
                curr->position.x = SCREEN_W - curr->radius;
                PlaySfx("paddle_hit");
            }
            if (curr->position.y <= curr->radius) { // Top wall
                curr->speed.y *= -1;
                curr->position.y = curr->radius;
                PlaySfx("paddle_hit");
            }

            // Paddle collision - iterate through all paddles in paddleList
            if (paddleList) {
                PaddleNode *paddle_node = paddleList->head;
                while (paddle_node != NULL) {
                    if (CheckCollisionCircleRec(curr->position, curr->radius, paddle_node->rect)) {
                        // Ensure ball is moving downwards towards paddle for a valid hit
                        if (curr->speed.y > 0) {
                            float paddleCenter = paddle_node->rect.x + paddle_node->rect.width / 2;
                            float hitPos = (curr->position.x - paddleCenter) / (paddle_node->rect.width / 2); // -1 to 1

                            // Adjust horizontal speed based on hit position, vertical speed inverted
                            curr->speed.x = hitPos * MAX_BALL_SPEED * 0.75f; // Adjust multiplier as needed
                            curr->speed.y = -fabsf(curr->speed.y); // Bounce up
                            if (fabsf(curr->speed.y) < MIN_BALL_SPEED) curr->speed.y = -MIN_BALL_SPEED;


                            // Reposition ball slightly above the paddle to prevent sticking
                            curr->position.y = paddle_node->rect.y - curr->radius - 0.1f;
                            PlaySfx("paddle_hit");
                            break; // Ball hit one paddle, stop checking for this frame
                        }
                    }
                    paddle_node = paddle_node->next;
                }
            }

            // Block collision
            NodeBlock* closestBlockNode = NULL;
            float closestDistance = FLT_MAX;
            NodeBlock* blockNode = blockList->head;

            while (blockNode != NULL) {
                if (blockNode->data.active) {
                    // Predict next position to check which side is hit for more accurate normal
                    
                    if (CheckCollisionCircleRec(curr->position, curr->radius, blockNode->data.rect)) {
                        // Simple distance check for "closest" (can be improved)
                        float dist = Vector2Distance(curr->position,
                            (Vector2){
                                blockNode->data.rect.x + blockNode->data.rect.width/2,
                                blockNode->data.rect.y + blockNode->data.rect.height/2
                            });
                        if (dist < closestDistance) {
                            closestBlockNode = blockNode;
                            closestDistance = dist;
                        }
                    }
                }
                blockNode = blockNode->next;
            }

            if (closestBlockNode != NULL) {
                closestBlockNode->data.hitPoints--;
                PlaySfx("block_hit");

                if (closestBlockNode->data.hitPoints <= 0) {
                    closestBlockNode->data.active = false;
                    TambahSkorDenganWaktu(skor, stopwatchList->time);
                    // Spawn power-up (30% chance)
                    if (GetRandomValue(1, 100) <= 30 && powerUpList) { // Check powerUpList not NULL
                        PowerUpType type = (PowerUpType)GetRandomValue(0, 1); // POWERUP_TRIPLE_BALL or POWERUP_LONG_PADDLE
                        AddPowerUp(powerUpList, type, (Vector2){
                            closestBlockNode->data.rect.x + closestBlockNode->data.rect.width / 2,
                            closestBlockNode->data.rect.y + closestBlockNode->data.rect.height / 2 // Spawn from center of block
                        });
                    }
                } else {
                    // Update block color based on remaining hitPoints
                    if (closestBlockNode->data.hitPoints == 2) closestBlockNode->data.color = (Color){255, 140, 26, 255}; // Orange
                    else if (closestBlockNode->data.hitPoints == 1) closestBlockNode->data.color = (Color){255, 204, 77, 255}; // Yellow
                }

                // Collision response: Determine which side of the block was hit
                float overlapLeft = (curr->position.x + curr->radius) - closestBlockNode->data.rect.x;
                float overlapRight = (closestBlockNode->data.rect.x + closestBlockNode->data.rect.width) - (curr->position.x - curr->radius);
                float overlapTop = (curr->position.y + curr->radius) - closestBlockNode->data.rect.y;
                float overlapBottom = (closestBlockNode->data.rect.y + closestBlockNode->data.rect.height) - (curr->position.y - curr->radius);

                bool fromLeft = overlapLeft < overlapRight;
                bool fromTop = overlapTop < overlapBottom;

                float minOverlapX = fromLeft ? overlapLeft : overlapRight;
                float minOverlapY = fromTop ? overlapTop : overlapBottom;

                if (minOverlapX < minOverlapY) { // Horizontal collision
                    curr->speed.x *= -1;
                    // Adjust position to prevent sticking
                    curr->position.x += (fromLeft ? -overlapLeft : overlapRight) * (curr->speed.x > 0 ? -1:1) *0.1f; // A bit of nudge
                } else { // Vertical collision
                    curr->speed.y *= -1;
                     curr->position.y += (fromTop ? -overlapTop : overlapBottom) * (curr->speed.y > 0 ? -1:1) *0.1f;
                }
            }

            if (AllBlocksDestroyed(blockList)) {
                *state = GAME_WIN;
            }

            if (curr->position.y > SCREEN_H + curr->radius * 2) { // Ball fell below screen
                curr->active = false;
            }
        }
        prev = curr;
        if(curr) curr = curr->next; // curr might have been freed if it was the head and became inactive
    }
}

bool SemuaBolaMati(BolaList *list) {
    if (!list) return true;
    BolaNode *curr = list->head;
    while (curr != NULL) {
        if (curr->active) {
            return false;
        }
        curr = curr->next;
    }
    return true;
}

void DrawBola(BolaList* list) {
    if (!list) return;
    for (BolaNode* curr = list->head; curr != NULL; curr = curr->next) {
        if (curr->active) {
            DrawCircleV(curr->position, curr->radius, curr->color);
        }
    }
}

void ResetBola(BolaList* list) {
    FreeBola(list); // Clear all existing balls
    InitBola(list); // Initialize with one new ball
}

void FreeBola(BolaList* list) {
    if (!list) return;
    BolaNode* curr = list->head;
    while (curr != NULL) {
        BolaNode* next = curr->next;
        free(curr);
        curr = next;
    }
    list->head = NULL;
}