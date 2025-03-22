#ifndef PADDLE_H
#define PADDLE_H

#include <raylib.h>

#define PADDLE_ROWS 1
#define PADDLE_COLS 1
#define PADDLE_WIDTH 100
#define PADDLE_HEIGHT 20
#define PADDLE_SPEED 8

typedef struct {
    Rectangle rect;
    Vector2 speed;
} Paddle;

void InitPaddles(Paddle paddles[PADDLE_ROWS][PADDLE_COLS]);
void UpdatePaddles(Paddle paddles[PADDLE_ROWS][PADDLE_COLS]);
void DrawPaddles(Paddle paddles[PADDLE_ROWS][PADDLE_COLS]);

#endif // PADDLE_H