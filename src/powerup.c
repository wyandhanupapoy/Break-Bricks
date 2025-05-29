#include "powerup.h"
#include "paddle.h"  // For PaddleNode definition, ActivePowerUp, PADDLE_WIDTH_DEFAULT etc.
#include "BOLA.h"    // For BolaList definition and AddBola function
#include "sound.h"   // For PlaySfx
#include <stdlib.h>  // For malloc, free

#define POWERUP_SPEED 3.0f
#define POWERUP_WIDTH 30
#define POWERUP_HEIGHT 30
// #define SCREEN_WIDTH needs to be contextually correct, e.g. from game_state.h or passed if needed for spawn/despawn logic
// Using GetScreenHeight() from raylib for despawn.

void InitPowerUp(PowerUpList *list) {
    if (!list) return;
    list->head = NULL;
}

void AddPowerUp(PowerUpList *list, PowerUpType type, Vector2 position) {
    if (!list) return;
    PowerUpNode *newNode = (PowerUpNode*)malloc(sizeof(PowerUpNode));
    if (!newNode) return;

    newNode->rect = (Rectangle){position.x - POWERUP_WIDTH/2, position.y, POWERUP_WIDTH, POWERUP_HEIGHT}; // Center spawn
    newNode->type = type;
    newNode->active = true;
    newNode->duration = 10.0f; // Default duration for power-up effect (e.g., 10 seconds)
    newNode->next = list->head;
    list->head = newNode;
}

void UpdatePowerUp(PowerUpList *fallingPowerUpList, PaddleList *paddleList, BolaList *bolaList, float deltaTime) {
    if (!fallingPowerUpList) return;

    PowerUpNode *prev = NULL;
    PowerUpNode *curr = fallingPowerUpList->head;

    while (curr != NULL) {
        if (!curr->active) { // If collected or despawned
            PowerUpNode *toDelete = curr;
            if (prev == NULL) {
                fallingPowerUpList->head = curr->next;
                curr = fallingPowerUpList->head;
            } else {
                prev->next = curr->next;
                curr = curr->next;
            }
            free(toDelete);
            continue;
        }

        // Move power-up downwards
        curr->rect.y += POWERUP_SPEED;

        // Check collision with any active paddle
        if (paddleList) {
            PaddleNode *p_node = paddleList->head;
            while (p_node != NULL) {
                if (CheckCollisionRecs(curr->rect, p_node->rect)) {
                    ActivatePowerUp(curr->type, p_node, bolaList, curr->duration);
                    curr->active = false; // Mark falling power-up as collected
                    // No need to break from inner loop if multiple paddles can collect (though unlikely for same item)
                    // but break outer loop's current iteration by going to 'continue' after freeing.
                    break; 
                }
                p_node = p_node->next;
            }
        }
        
        // If collected, the active flag will be false, and it will be removed at the start of the next iteration for 'curr'
        if (!curr->active) {
             // This path is taken if collected in the loop above.
             // The node will be removed in the next main loop iteration by the first 'if (!curr->active)' block.
             // To remove immediately:
            PowerUpNode *toDelete = curr;
            if (prev == NULL) {
                fallingPowerUpList->head = curr->next;
                curr = fallingPowerUpList->head;
            } else {
                prev->next = curr->next;
                curr = curr->next;
            }
            free(toDelete);
            continue; // Restart loop for the new 'curr'
        }


        // Despawn if it falls off screen
        if (curr->rect.y > GetScreenHeight()) {
            curr->active = false;
            // Node will be removed in the next iteration by the first 'if' block.
        }

        prev = curr;
        curr = curr->next;
    }
}

void DrawPowerUp(PowerUpList *list) {
    if (!list) return;
    PowerUpNode *curr = list->head;
    while (curr != NULL) {
        if (curr->active) {
            Color color;
            const char *symbol;
            switch (curr->type) {
                case POWERUP_TRIPLE_BALL:
                    color = RED;
                    symbol = "3B"; 
                    break;
                case POWERUP_LONG_PADDLE:
                    color = BLUE;
                    symbol = "LP"; 
                    break;
                default:
                    color = GRAY;
                    symbol = "?";
                    break;
            }
            DrawRectangleRec(curr->rect, color);
            int fontSize = (POWERUP_HEIGHT < 25) ? 10:20;
            int textWidth = MeasureText(symbol, fontSize);
            int textX = curr->rect.x + (curr->rect.width - textWidth) / 2;
            int textY = curr->rect.y + (curr->rect.height - fontSize) / 2;
            DrawText(symbol, textX, textY, fontSize, WHITE);
        }
        curr = curr->next;
    }
}

void ActivatePowerUp(PowerUpType type, PaddleNode *paddle_node, BolaList *bolaList, float duration) {
    if (!paddle_node) return;
    PlaySfx("power_up"); // Assuming this function exists in sound.c

    bool alreadyActive = false;
    ActivePowerUp* existingEffect = paddle_node->activePowerUps;
    while(existingEffect != NULL) {
        if (existingEffect->type == type) {
            existingEffect->remainingTime = duration; // Refresh duration
            alreadyActive = true;
            break;
        }
        existingEffect = existingEffect->next;
    }

    if (alreadyActive) return; // Don't stack the same type, just refresh

    // Add new power-up effect to the paddle's list of active effects
    ActivePowerUp *newEffect = (ActivePowerUp*)malloc(sizeof(ActivePowerUp));
    if (!newEffect) return;

    newEffect->type = type;
    newEffect->remainingTime = duration;
    newEffect->next = paddle_node->activePowerUps;
    paddle_node->activePowerUps = newEffect;

    // Apply immediate effect
    if (type == POWERUP_TRIPLE_BALL && bolaList) {
        // Spawn two additional balls near the paddle that collected the power-up
        Vector2 spawnPos = {paddle_node->rect.x + paddle_node->rect.width / 2, paddle_node->rect.y - 15};
        AddBola(bolaList, spawnPos, (Vector2){-4, -6}); // Speed left
        AddBola(bolaList, spawnPos, (Vector2){4, -6});  // Speed right
        // The original ball continues, this adds two more.
    }
    if (type == POWERUP_LONG_PADDLE) {
        paddle_node->rect.width = PADDLE_WIDTH * 1.5f; // Increase width by 50%
        // Add clamping if necessary, e.g., not wider than screen
        // float gameScreenWidth = SCREEN_WI; // from paddle.c
        // if (paddle_node->rect.x + paddle_node->rect.width > gameScreenWidth) {
        //     paddle_node->rect.width = gameScreenWidth - paddle_node->rect.x;
        // }
    }
}

void UpdateActivePowerUps(PaddleNode *paddle_node, float deltaTime) {
    if (!paddle_node) return;

    ActivePowerUp *curr = paddle_node->activePowerUps;
    ActivePowerUp *prev = NULL;

    while (curr != NULL) {
        curr->remainingTime -= deltaTime;
        if (curr->remainingTime <= 0) {
            // Effect has expired, revert it
            if (curr->type == POWERUP_LONG_PADDLE) {
                paddle_node->rect.width = PADDLE_WIDTH_DEFAULT; // Reset to default width
            }
            // For POWERUP_TRIPLE_BALL, the effect is instantaneous (spawning balls). No specific reversion needed here.

            // Remove effect from list
            ActivePowerUp *toDelete = curr;
            if (prev == NULL) { // Effect was at the head of the list
                paddle_node->activePowerUps = curr->next;
                curr = paddle_node->activePowerUps;
            } else {
                prev->next = curr->next;
                curr = prev->next;
            }
            free(toDelete);
            // 'curr' is already updated, 'prev' remains correct if curr was not head.
            // If curr was head, prev is NULL, and next loop iteration will handle prev correctly.
        } else {
            prev = curr;
            curr = curr->next;
        }
    }
}

void FreePowerUp(PowerUpList *list) { // Frees the list of *falling* power-ups
    if (!list) return;
    PowerUpNode *curr = list->head;
    while (curr != NULL) {
        PowerUpNode *next = curr->next;
        free(curr);
        curr = next;
    }
    list->head = NULL;
}