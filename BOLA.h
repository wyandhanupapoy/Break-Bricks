#ifndef BALL_H
#define BALL_H

#include "raylib.h"

#define BALL_ROWS 2 // Contoh ukuran array 2 dimensi untuk beberapa bola
#define BALL_COLS 2

typedef struct {
    Vector2 position;
    Vector2 speed;
    float radius;
    Color color;
} Ball;

void InitBalls(Ball balls[BALL_ROWS][BALL_COLS], float startX, float startY, float radius, float speedX, float speedY);
void UpdateBalls(Ball balls[BALL_ROWS][BALL_COLS], float screenWidth, float screenHeight);
void DrawBalls(Ball balls[BALL_ROWS][BALL_COLS]);

#endif