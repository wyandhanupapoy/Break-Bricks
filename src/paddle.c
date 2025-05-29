// Nama : Muhammad Raihan Abubakar
// Nama fitur : paddle
// Deskripsi : paddle berfungsi untuk memantulkan dan mengarahkan bola agar bisa menghancurkan block
// MODIFIED: Changed to a dynamic linked list of paddles.

#include <stdlib.h> // For malloc and free
#include "paddle.h"
#include "powerup.h" // For UpdateActivePowerUps function declaration

// Define screen dimensions for paddle constraints
// These were locally defined in the original paddle.c.
#define SCREEN_WI 830 // Game area width for paddle movement
#define SCREEN_HE 600 // Game area height

// Helper function to free active power-ups for a single paddle
static void FreePaddleActivePowerUps(PaddleNode *paddleNode) {
    ActivePowerUp *currentEffect = paddleNode->activePowerUps;
    while (currentEffect != NULL) {
        ActivePowerUp *nextEffect = currentEffect->next;
        free(currentEffect);
        currentEffect = nextEffect;
    }
    paddleNode->activePowerUps = NULL;
}

void InitPaddles(PaddleList *list) {
    if (!list) return;
    list->head = NULL; 
    
    AddPaddle(list,
              (Vector2){(SCREEN_WI - PADDLE_WIDTH) / 2.0f, SCREEN_HE - PADDLE_HEIGHT - 10.0f},
              PADDLE_WIDTH,
              (Color){0, 255, 255, 255}); // Default Cyan color
}

void AddPaddle(PaddleList *list, Vector2 position, float width, Color color) {
    if (!list) return;

    PaddleNode *newPaddle = (PaddleNode*)malloc(sizeof(PaddleNode));
    if (!newPaddle) {
        return;
    }

    newPaddle->rect = (Rectangle){position.x, position.y, width, PADDLE_HEIGHT};
    newPaddle->speed = (Vector2){PADDLE_SPEED, 0};
    newPaddle->color = color;
    newPaddle->activePowerUps = NULL; 
    newPaddle->next = list->head;     
    list->head = newPaddle;
}

void UpdatePaddles(PaddleList *list, float deltaTime) {
    if (!list) return;

    PaddleNode *current = list->head;
    while (current != NULL) {
        if (IsKeyDown(KEY_LEFT) && current->rect.x > 0) {
            current->rect.x -= current->speed.x;
        }
        if (IsKeyDown(KEY_RIGHT) && current->rect.x < SCREEN_WI - current->rect.width) {
            current->rect.x += current->speed.x;
        }

        if (current->rect.x < 0) {
            current->rect.x = 0;
        }
        if (current->rect.x + current->rect.width > SCREEN_WI) {
            current->rect.x = SCREEN_WI - current->rect.width;
        }
        
        // UpdateActivePowerUps is declared in powerup.h and takes PaddleNode* (as struct PaddleNode*)
        UpdateActivePowerUps(current, deltaTime);

        current = current->next;
    }
}

void DrawPaddles(PaddleList *list) {
    if (!list) return;

    PaddleNode *current = list->head;
    while (current != NULL) {
        Color paddleDrawColor = current->color; 

        ActivePowerUp *powerEffect = current->activePowerUps;
        while (powerEffect != NULL) {
            if (powerEffect->type == POWERUP_LONG_PADDLE) {
                paddleDrawColor = (Color){255, 165, 0, 255}; // Orange for long paddle
                break;
            }
            powerEffect = powerEffect->next;
        }
        
        DrawRectangleRec(current->rect, paddleDrawColor);
        current = current->next;
    }
}

void FreePaddles(PaddleList *list) {
    if (!list) return;

    PaddleNode *current = list->head;
    while (current != NULL) {
        PaddleNode *nextNode = current->next;
        FreePaddleActivePowerUps(current); 
        free(current);                     
        current = nextNode;
    }
    list->head = NULL; 
}