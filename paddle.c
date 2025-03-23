#include "paddle.h"

#define SCREEN_WIDTH 830
#define SCREEN_HEIGHT 600

void InitPaddles(Paddle paddles[PADDLE_ROWS][PADDLE_COLS]) {
    for (int i = 0; i < PADDLE_ROWS; i++) {
        for (int j = 0; j < PADDLE_COLS; j++) {
            paddles[i][j].rect = (Rectangle){(SCREEN_WIDTH - PADDLE_WIDTH) / 2, SCREEN_HEIGHT - PADDLE_HEIGHT - 10, PADDLE_WIDTH, PADDLE_HEIGHT};
            paddles[i][j].speed = (Vector2){PADDLE_SPEED, 0};
        }
    }
}

void UpdatePaddles(Paddle paddles[PADDLE_ROWS][PADDLE_COLS]) {
    for (int i = 0; i < PADDLE_ROWS; i++) {
        for (int j = 0; j < PADDLE_COLS; j++) {
            if (IsKeyDown(KEY_LEFT) && paddles[i][j].rect.x > 0) {
                paddles[i][j].rect.x -= paddles[i][j].speed.x;
            }
            if (IsKeyDown(KEY_RIGHT) && paddles[i][j].rect.x < SCREEN_WIDTH - PADDLE_WIDTH) {
                paddles[i][j].rect.x += paddles[i][j].speed.x;
            }
        }
    }
}

void DrawPaddles(Paddle paddles[PADDLE_ROWS][PADDLE_COLS]) {
    for (int i = 0; i < PADDLE_ROWS; i++) {
        for (int j = 0; j < PADDLE_COLS; j++) {
            DrawRectangleRec(paddles[i][j].rect, (Color){0, 255, 255, 255});
        }
    }
}
