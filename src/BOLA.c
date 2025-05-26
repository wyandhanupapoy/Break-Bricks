#include <raylib.h>
#include "BOLA.h"
#include "sound.h"
#include <stdlib.h>
#include <float.h>
#include <raymath.h>

#define SCREEN_W 830
#define SCREEN_H 600
#define MIN_BALL_SPEED 6.0f
#define MAX_BALL_SPEED 9.0f

void InitBola(BolaList* list) {
    list->head = NULL;
    AddBola(list, (Vector2){SCREEN_W / 2, SCREEN_H / 2}, (Vector2){6, -6});
}

void AddBola(BolaList* list, Vector2 position, Vector2 speed) {
    BolaNode* newBall = (BolaNode*)malloc(sizeof(BolaNode));
    if (newBall == NULL) return;

    // Clamp speed values
    speed.x = fminf(fmaxf(speed.x, -MAX_BALL_SPEED), MAX_BALL_SPEED);
    speed.y = fminf(fmaxf(speed.y, -MAX_BALL_SPEED), MAX_BALL_SPEED);

    newBall->position = position;
    newBall->speed = speed;
    newBall->radius = 10;
    newBall->color = RED;
    newBall->active = true;
    newBall->next = list->head;
    list->head = newBall;
}

void UpdateBola(BolaList* list, Paddle paddles[PADDLE_ROWS][PADDLE_COLS],
              Block blocks[BLOCK_ROWS][BLOCK_COLS], GameState* state,
              Skor* skor, Stopwatch sw[STOPWATCH_ROWS][STOPWATCH_COLS],
              PowerUpList* powerUpList) {
    BolaNode* prev = NULL;
    BolaNode* curr = list->head;

    while (curr != NULL) {
        if (!curr->active) {
            // Remove inactive ball
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
            // Ball movement
            curr->position.x += curr->speed.x;
            curr->position.y += curr->speed.y;

            // Speed regulation
            float speedMagnitude = Vector2Length(curr->speed);
            if (speedMagnitude < MIN_BALL_SPEED || speedMagnitude > MAX_BALL_SPEED) {
                float factor = (speedMagnitude < MIN_BALL_SPEED) 
                    ? MIN_BALL_SPEED / speedMagnitude 
                    : MAX_BALL_SPEED / speedMagnitude;
                curr->speed = Vector2Scale(Vector2Normalize(curr->speed), MAX_BALL_SPEED);
            }

            // Wall collision
            if (curr->position.x < curr->radius) {
                curr->speed.x *= -1;
                curr->position.x = curr->radius;
            }
            if (curr->position.x > SCREEN_W - curr->radius) {
                curr->speed.x *= -1;
                curr->position.x = SCREEN_W - curr->radius;
            }
            if (curr->position.y < curr->radius) {
                curr->speed.y *= -1;
                curr->position.y = curr->radius;
            }

            // Paddle collision
            for (int j = 0; j < PADDLE_ROWS; j++) {
                for (int k = 0; k < PADDLE_COLS; k++) {
                    if (CheckCollisionCircleRec(curr->position, curr->radius, paddles[j][k].rect)) {
                        float paddleCenter = paddles[j][k].rect.x + paddles[j][k].rect.width / 2;
                        float hitPos = (curr->position.x - paddleCenter) / (paddles[j][k].rect.width / 2);
                        curr->speed = (Vector2){hitPos * 7.0f, -fabsf(curr->speed.y)};
                        PlayPaddleHit();
                        curr->position.y = paddles[j][k].rect.y - curr->radius - 1;
                    }
                }
            }

            // Block collision
            Block* closestBlock = NULL;
            float closestDistance = FLT_MAX;
            
            for (int r = 0; r < BLOCK_ROWS; r++) {
                for (int c = 0; c < BLOCK_COLS; c++) {
                    if (!blocks[r][c].active) continue;
                    
                    if (CheckCollisionCircleRec(curr->position, curr->radius, blocks[r][c].rect)) {
                        float dist = Vector2Distance(curr->position,
                            (Vector2){
                                blocks[r][c].rect.x + blocks[r][c].rect.width/2,
                                blocks[r][c].rect.y + blocks[r][c].rect.height/2
                            });
                        
                        if (dist < closestDistance) {
                            closestBlock = &blocks[r][c];
                            closestDistance = dist;
                        }
                    }
                }
            }

            if (closestBlock != NULL) {
                closestBlock->hitPoints--;
                
                if (closestBlock->hitPoints <= 0) {
                    PlayBlockHit();
                    closestBlock->active = false;
                    TambahSkorDenganWaktu(skor, sw[0][0].time);

                    // Spawn power-up (30% chance)
                    if (GetRandomValue(0, 100) < 30) {
                        PowerUpType type = GetRandomValue(0, 1);  // POWERUP_TRIPLE_BALL = 0, POWERUP_LONG_PADDLE = 1
                        AddPowerUp(powerUpList, type, (Vector2){
                            closestBlock->rect.x + closestBlock->rect.width/2,
                            closestBlock->rect.y
                        });
                } else {
                    closestBlock->color = (closestBlock->hitPoints == 2) ?
                        (Color){255, 140, 26, 255} :
                        (Color){255, 204, 77, 255};
                }

                // Calculate collision response
                Vector2 ballCenter = curr->position;
                Vector2 blockCenter = {
                    closestBlock->rect.x + closestBlock->rect.width/2,
                    closestBlock->rect.y + closestBlock->rect.height/2
                };
                
                Vector2 normal = {0};
                if (fabsf(ballCenter.x - blockCenter.x) / closestBlock->rect.width >
                    fabsf(ballCenter.y - blockCenter.y) / closestBlock->rect.height) {
                    // Horizontal collision
                    normal.x = (ballCenter.x < blockCenter.x) ? -1 : 1;
                } else {
                    // Vertical collision
                    normal.y = (ballCenter.y < blockCenter.y) ? -1 : 1;
                }
                
                if (normal.x != 0) curr->speed.x *= -1;
                if (normal.y != 0) curr->speed.y *= -1;
            }

            // Check win condition
            if (AllBlocksDestroyed(blocks)) {
                *state = GAME_WIN;
            }

            // Check if ball fell below screen
            if (curr->position.y > SCREEN_H) {
                curr->active = false;
            }
        }

        prev = curr;
        curr = curr->next;
        }
    }
}

bool SemuaBolaMati(BolaList *list) {
    BolaNode *curr = list->head;
    while (curr != NULL) {
        if (curr->active) {  // Jika ada 1 bola yang masih aktif
            return false;    // → Belum mati semua
        }
        curr = curr->next;
    }
    return true;  // Semua bola tidak aktif
}

void DrawBola(BolaList* list) {
    for (BolaNode* curr = list->head; curr != NULL; curr = curr->next) {
        if (curr->active) {
            DrawCircleV(curr->position, curr->radius, curr->color);
        }
    }
}

void ResetBola(BolaList* list) {
    FreeBola(list);
    InitBola(list);
}

void FreeBola(BolaList* list) {
    BolaNode* curr = list->head;
    while (curr != NULL) {
        BolaNode* next = curr->next;
        free(curr);
        curr = next;
    }
    list->head = NULL;
}