// src/paddle.h
#ifndef PADDLE_H
#define PADDLE_H

#include <raylib.h>
#include "powerup.h" // <-- TAMBAHKAN INI untuk definisi PowerUpType

// typedef enum PowerUpType PowerUpType; // <-- HAPUS BARIS INI

// Default properties for a new paddle
#define PADDLE_WIDTH 100.0f
#define PADDLE_HEIGHT 20.0f
#define PADDLE_SPEED 8.0f
#define PADDLE_WIDTH_DEFAULT PADDLE_WIDTH

#define PADDLE_GAME_AREA_WIDTH 830.0f
#define MAX_PADDLE_WIDTH (PADDLE_GAME_AREA_WIDTH * 0.9f)

typedef struct ActivePowerUp {
    PowerUpType type; // Sekarang PowerUpType seharusnya sudah terdefinisi
    float remainingTime;
    struct ActivePowerUp *next;
} ActivePowerUp;

// ... (sisa kode paddle.h tetap sama) ...
typedef struct PaddleNode {
    Rectangle rect;
    Vector2 speed;
    ActivePowerUp *activePowerUps;
    Color color;
    struct PaddleNode *next;
} PaddleNode;

typedef struct PaddleList {
    PaddleNode *head;
} PaddleList;

void InitPaddles(PaddleList *list);
void AddPaddle(PaddleList *list, Vector2 position, float width, Color color);
void UpdatePaddles(PaddleList *list, float deltaTime);
void DrawPaddles(PaddleList *list);
void FreePaddles(PaddleList *list);

#endif // PADDLE_H