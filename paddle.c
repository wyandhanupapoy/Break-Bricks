#include "paddle.h"

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600

void InitPaddles(Paddle paddles[PADDLE_ROWS][PADDLE_COLS]) {
    for (int i = 0; i < PADDLE_ROWS; i++) {
        for (int j = 0; j < PADDLE_COLS; j++) {
            paddles[i][j].rect.x = (SCREEN_WIDTH / 2) - (PADDLE_WIDTH / 2);
            paddles[i][j].rect.y = SCREEN_HEIGHT - 50;
            paddles[i][j].rect.width = PADDLE_WIDTH;
            paddles[i][j].rect.height = PADDLE_HEIGHT;
            paddles[i][j].speed.x = PADDLE_SPEED;
        }
    }
}
