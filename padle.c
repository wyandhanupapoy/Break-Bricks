#include "padle.h"

// Inisialisasi paddle
void InitPaddle(Paddle *paddle) {
    paddle->rect.x = (SCREEN_WIDTH - PADDLE_WIDTH) / 2;
    paddle->rect.y = SCREEN_HEIGHT - 50;
    paddle->rect.width = PADDLE_WIDTH;
    paddle->rect.height = PADDLE_HEIGHT;
    paddle->speed.x = PADDLE_SPEED;
}

// Update posisi paddle berdasarkan input
void UpdatePaddle(Paddle *paddle) {
    if (IsKeyDown(KEY_LEFT) && paddle->rect.x > 0) {
        paddle->rect.x -= paddle->speed.x;
    }
    if (IsKeyDown(KEY_RIGHT) && paddle->rect.x < SCREEN_WIDTH - PADDLE_WIDTH) {
        paddle->rect.x += paddle->speed.x;
    }
}

// Gambar paddle di layar
void DrawPaddle(Paddle *paddle) {
    DrawRectangleRec(paddle->rect, BLACK);
}
