// Nama : Muhammad Raihan Abubakar
// Nama fitur : paddle
// Deskripsi : paddle berfungsi untuk memantulkan dan mengarahkan bola agar bisa menghancurkan block
// MODIFIED: Changed to a dynamic linked list of paddles.

#ifndef PADDLE_H
#define PADDLE_H

#include <raylib.h>
#include "powerup.h" // For PowerUpType

// Default properties for a new paddle
#define PADDLE_WIDTH 100       // Default initial width of the paddle
#define PADDLE_HEIGHT 20       // Height of the paddle
#define PADDLE_SPEED 8         // Movement speed of the paddle
#define PADDLE_WIDTH_DEFAULT PADDLE_WIDTH // Default width for resetting power-ups

// Structure for active power-up effects on a paddle
typedef struct ActivePowerUp {
    PowerUpType type;
    float remainingTime;
    struct ActivePowerUp *next;
} ActivePowerUp;

// Node for an individual paddle in the linked list
typedef struct PaddleNode {
    Rectangle rect;             // Position and dimensions of the paddle
    Vector2 speed;              // Movement speed of the paddle
    ActivePowerUp *activePowerUps; // Linked list of active power-up effects on this paddle
    Color color;                // Base color of the paddle
    struct PaddleNode *next;    // Pointer to the next paddle in the list
} PaddleNode;

// Linked list structure to manage all paddles
typedef struct PaddleList {
    PaddleNode *head;           // Pointer to the first paddle in the list
} PaddleList;

// Functions for paddle management
void InitPaddles(PaddleList *list);                                    // Initializes the paddle list (e.g., adds one default paddle)
void AddPaddle(PaddleList *list, Vector2 position, float width, Color color); // Adds a new paddle to the list
void UpdatePaddles(PaddleList *list, float deltaTime);                 // Updates all paddles in the list
void DrawPaddles(PaddleList *list);                                    // Draws all paddles in the list
void FreePaddles(PaddleList *list);                                    // Frees all memory allocated for paddles

#endif // PADDLE_H