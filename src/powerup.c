#include "powerup.h"
#include <stdlib.h>
#include "sound.h"
#include <math.h>
#include "game_state.h"

#define POWERUP_SIZE 15
#define POWERUP_DROP_CHANCE 30  // 30% chance to drop power-up when block is destroyed
#define POWERUP_FALL_SPEED 2.0f
#define DEFAULT_POWERUP_DURATION 10.0f  // Power-up lasts for 10 seconds by default

// Original paddle width to restore after power-up ends
static float originalPaddleWidth = PADDLE_WIDTH;
static float originalBallSpeed = 0.0f;
static Color originalBallColor = RED;
static bool isBallStrong = false;

// Initializes the power-up system
void InitPowerUpSystem(void) {
    // Initialize any global variables for power-ups
    originalPaddleWidth = PADDLE_WIDTH;
    isBallStrong = false;
    // Reset can happen here
}

// Spawns a power-up at the given position with random type
void SpawnPowerUp(float x, float y) {
    // Only spawn a power-up with a certain probability
    if (GetRandomValue(1, 100) <= POWERUP_DROP_CHANCE) {
        PowerUp* newPowerUp = (PowerUp*)malloc(sizeof(PowerUp));
        if (newPowerUp == NULL) return;
        
        // Random power-up type
        PowerUpType type = GetRandomValue(0, POWERUP_COUNT - 1);
        
        newPowerUp->rect = (Rectangle){x, y, POWERUP_SIZE, POWERUP_SIZE};
        newPowerUp->active = true;
        newPowerUp->speed = POWERUP_FALL_SPEED;
        newPowerUp->type = type;
        newPowerUp->duration = DEFAULT_POWERUP_DURATION;
        newPowerUp->timer = 0.0f;
        newPowerUp->isEffectActive = false;
        newPowerUp->next = NULL;
        
        // Set color based on power-up type
        switch (type) {
            case POWERUP_WIDER_PADDLE:
                newPowerUp->color = (Color){50, 200, 50, 255};  // Green
                break;
            case POWERUP_SLOW_BALL:
                newPowerUp->color = (Color){50, 50, 200, 255};  // Blue
                break;
            case POWERUP_MULTI_BALL:
                newPowerUp->color = (Color){200, 50, 200, 255}; // Purple
                break;
            case POWERUP_EXTRA_LIFE:
                newPowerUp->color = (Color){255, 50, 50, 255};  // Red
                break;
            case POWERUP_STRONGER_BALL:
                newPowerUp->color = (Color){255, 165, 0, 255};  // Orange
                break;
            default:
                newPowerUp->color = WHITE;
                break;
        }
        
        // Add to linked list - FIXED: Use pointer to powerUpList passed from main
        PowerUp** powerUpList = GetPowerUpListPtr();  // Get the pointer to the global powerUpList
        newPowerUp->next = *powerUpList;
        *powerUpList = newPowerUp;
    }
}

// Updates all power-ups (movement, collision, etc.)
void UpdatePowerUps(PowerUp** powerUpList, Paddle paddles[PADDLE_ROWS][PADDLE_COLS], 
                   Bola bola[BOLA_ROWS][BOLA_COLS], Nyawa nyawa[NYAWA_BARIS][NYAWA_KOLOM]) {
    if (powerUpList == NULL) return;
    
    PowerUp* current = *powerUpList;
    PowerUp* previous = NULL;
    
    while (current != NULL) {
        // Move power-up down
        if (current->active) {
            current->rect.y += current->speed;
            
            // Check if power-up is caught by paddle
            for (int i = 0; i < PADDLE_ROWS; i++) {
                for (int j = 0; j < PADDLE_COLS; j++) {
                    if (CheckCollisionRecs(current->rect, paddles[i][j].rect)) {
                        // Power-up is caught
                        current->active = false;
                        current->isEffectActive = true;
                        current->timer = 0.0f;
                        
                        // Apply power-up effect
                        ApplyPowerUpEffect(current->type, paddles, bola, nyawa, current);
                        
                        // Play power-up sound
                        PlayPowerUpSound();
                    }
                }
            }
            
            // Remove power-up if it falls off the screen
            if (current->rect.y > SCREEN_HEIGHT) {
                current->active = false;
            }
        }
        
        // Update timer for active effects
        if (current->isEffectActive) {
            current->timer += GetFrameTime();
            
            // Check if effect duration is over
            if (current->timer >= current->duration && current->type != POWERUP_EXTRA_LIFE) {
                RevertPowerUpEffect(current->type, paddles, bola);
                current->isEffectActive = false;
            }
        }
        
        // Remove inactive power-ups that have completed their effects
        if (!current->active && !current->isEffectActive) {
            PowerUp* toRemove = current;
            
            if (previous == NULL) {
                // First node
                *powerUpList = current->next;
                current = *powerUpList;
            } else {
                // Middle or end node
                previous->next = current->next;
                current = current->next;
            }
            
            free(toRemove);
        } else {
            previous = current;
            current = current->next;
        }
    }
}

// Draws all active power-ups
void DrawPowerUps(PowerUp* powerUpList) {
    PowerUp* current = powerUpList;
    
    while (current != NULL) {
        if (current->active) {
            DrawRectangleRec(current->rect, current->color);
            
            // Draw icon or symbol based on power-up type
            switch (current->type) {
                case POWERUP_WIDER_PADDLE:
                    DrawText("W", current->rect.x + 4, current->rect.y + 1, 12, BLACK);
                    break;
                case POWERUP_SLOW_BALL:
                    DrawText("S", current->rect.x + 4, current->rect.y + 1, 12, BLACK);
                    break;
                case POWERUP_MULTI_BALL:
                    DrawText("M", current->rect.x + 4, current->rect.y + 1, 12, BLACK);
                    break;
                case POWERUP_EXTRA_LIFE:
                    DrawText("+", current->rect.x + 4, current->rect.y + 1, 12, BLACK);
                    break;
                case POWERUP_STRONGER_BALL:
                    DrawText("P", current->rect.x + 4, current->rect.y + 1, 12, BLACK);
                    break;
                default:
                    break;
            }
        }
        
        current = current->next;
    }
}

// Cleans up all power-ups
void CleanupPowerUps(PowerUp** powerUpList) {
    PowerUp* current = *powerUpList;
    
    while (current != NULL) {
        PowerUp* next = current->next;
        free(current);
        current = next;
    }
    
    *powerUpList = NULL;
}

// Applies power-up effect based on type
void ApplyPowerUpEffect(PowerUpType type, Paddle paddles[PADDLE_ROWS][PADDLE_COLS], 
                       Bola bola[BOLA_ROWS][BOLA_COLS], Nyawa nyawa[NYAWA_BARIS][NYAWA_KOLOM], PowerUp* powerUp) {
    switch (type) {
        case POWERUP_WIDER_PADDLE:
            // Make paddle wider
            for (int i = 0; i < PADDLE_ROWS; i++) {
                for (int j = 0; j < PADDLE_COLS; j++) {
                    // Save original width if not saved yet
                    if (originalPaddleWidth == PADDLE_WIDTH) {
                        originalPaddleWidth = paddles[i][j].rect.width;
                    }
                    
                    // Make paddle 1.5x wider
                    float newWidth = originalPaddleWidth * 1.5f;
                    float centerX = paddles[i][j].rect.x + paddles[i][j].rect.width / 2.0f;
                    paddles[i][j].rect.width = newWidth;
                    paddles[i][j].rect.x = centerX - newWidth / 2.0f;
                    
                    // Make sure paddle stays within screen bounds
                    if (paddles[i][j].rect.x < 0) paddles[i][j].rect.x = 0;
                    if (paddles[i][j].rect.x + paddles[i][j].rect.width > SCREEN_WIDTH) {
                        paddles[i][j].rect.x = SCREEN_WIDTH - paddles[i][j].rect.width;
                    }
                }
            }
            break;
            
        case POWERUP_SLOW_BALL:
            // Slow down ball
            for (int i = 0; i < BOLA_ROWS; i++) {
                if (bola[i][0].active) {
                    // Save original speed
                    if (originalBallSpeed == 0.0f) {
                        originalBallSpeed = sqrtf(bola[i][0].speed.x * bola[i][0].speed.x + 
                                                 bola[i][0].speed.y * bola[i][0].speed.y);
                    }
                    
                    // Slow down ball by 40%
                    float speedMag = sqrtf(bola[i][0].speed.x * bola[i][0].speed.x + 
                                          bola[i][0].speed.y * bola[i][0].speed.y);
                    float slowFactor = 0.6f;  // 60% of original speed
                    
                    bola[i][0].speed.x *= (slowFactor * speedMag / originalBallSpeed);
                    bola[i][0].speed.y *= (slowFactor * speedMag / originalBallSpeed);
                    
                    // Change ball color to indicate effect
                    originalBallColor = bola[i][0].color;
                    bola[i][0].color = BLUE;
                }
            }
            break;
            
        case POWERUP_MULTI_BALL:
            // Add more balls (not fully implemented as it would require changes to BOLA structure)
            // This would need more complex handling in your game logic
            // For now, just change ball color to indicate effect
            for (int i = 0; i < BOLA_ROWS; i++) {
                if (bola[i][0].active) {
                    originalBallColor = bola[i][0].color;
                    bola[i][0].color = PURPLE;
                }
            }
            break;
            
        case POWERUP_EXTRA_LIFE:
            // Add extra life
            
            break;
            
        case POWERUP_STRONGER_BALL:
            // Make ball stronger
            for (int i = 0; i < BOLA_ROWS; i++) {
                if (bola[i][0].active) {
                    originalBallColor = bola[i][0].color;
                    bola[i][0].color = ORANGE;
                    isBallStrong = true;
                }
            }
            break;
            
        default:
            break;
    }
}

// Updates active power-up effects
void UpdatePowerUpEffects(PowerUp* powerUpList, Paddle paddles[PADDLE_ROWS][PADDLE_COLS], Bola bola[BOLA_ROWS][BOLA_COLS]) {
    PowerUp* current = powerUpList;
    
    while (current != NULL) {
        if (current->isEffectActive) {
            // Update power-up effect specific logic if needed
            switch (current->type) {
                case POWERUP_WIDER_PADDLE:
                    // Keep paddle within screen bounds
                    for (int i = 0; i < PADDLE_ROWS; i++) {
                        for (int j = 0; j < PADDLE_COLS; j++) {
                            if (paddles[i][j].rect.x < 0) paddles[i][j].rect.x = 0;
                            if (paddles[i][j].rect.x + paddles[i][j].rect.width > SCREEN_WIDTH) {
                                paddles[i][j].rect.x = SCREEN_WIDTH - paddles[i][j].rect.width;
                            }
                        }
                    }
                    break;
                    
                default:
                    break;
            }
        }
        
        current = current->next;
    }
}

// Reverts power-up effect when it ends
void RevertPowerUpEffect(PowerUpType type, Paddle paddles[PADDLE_ROWS][PADDLE_COLS], Bola bola[BOLA_ROWS][BOLA_COLS]) {
    switch (type) {
        case POWERUP_WIDER_PADDLE:
            // Restore original paddle width
            for (int i = 0; i < PADDLE_ROWS; i++) {
                for (int j = 0; j < PADDLE_COLS; j++) {
                    float centerX = paddles[i][j].rect.x + paddles[i][j].rect.width / 2.0f;
                    paddles[i][j].rect.width = originalPaddleWidth;
                    paddles[i][j].rect.x = centerX - originalPaddleWidth / 2.0f;
                    
                    // Make sure paddle stays within screen bounds
                    if (paddles[i][j].rect.x < 0) paddles[i][j].rect.x = 0;
                    if (paddles[i][j].rect.x + paddles[i][j].rect.width > SCREEN_WIDTH) {
                        paddles[i][j].rect.x = SCREEN_WIDTH - paddles[i][j].rect.width;
                    }
                }
            }
            break;
            
        case POWERUP_SLOW_BALL:
            // Restore original ball speed
            for (int i = 0; i < BOLA_ROWS; i++) {
                if (bola[i][0].active) {
                    float currentSpeed = sqrtf(bola[i][0].speed.x * bola[i][0].speed.x + 
                                              bola[i][0].speed.y * bola[i][0].speed.y);
                    float speedFactor = originalBallSpeed / currentSpeed;
                    
                    bola[i][0].speed.x *= speedFactor;
                    bola[i][0].speed.y *= speedFactor;
                    
                    // Restore original color
                    bola[i][0].color = originalBallColor;
                }
            }
            break;
            
        case POWERUP_MULTI_BALL:
            // Restore ball color for now
            for (int i = 0; i < BOLA_ROWS; i++) {
                if (bola[i][0].active) {
                    bola[i][0].color = originalBallColor;
                }
            }
            break;
            
        case POWERUP_STRONGER_BALL:
            // Restore ball to normal
            for (int i = 0; i < BOLA_ROWS; i++) {
                if (bola[i][0].active) {
                    bola[i][0].color = originalBallColor;
                    isBallStrong = false;
                }
            }
            break;
            
        default:
            break;
    }
}

// Function to check if the ball is currently strong (for use in BOLA.c)
bool IsBallStrong(void) {
    return isBallStrong;
}

// Global powerUpList pointer declarations should be in main.c
// This function gets the pointer to the global powerUpList
PowerUp** GetPowerUpListPtr(void) {
    extern PowerUp* powerUpList;
    return &powerUpList;
}