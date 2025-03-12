#include "padle.h"

// Inisialisasi array paddle dalam bentuk 2D
void InitPaddles(Paddle paddles[PADDLE_ROWS][PADDLE_COLS]) {
    for (int i = 0; i < PADDLE_ROWS; i++) {
        for (int j = 0; j < PADDLE_COLS; j++) {
            paddles[i][j].rect.x = (SCREEN_WIDTH / (PADDLE_COLS + 1)) * (j + 1) - (PADDLE_WIDTH / 2);
            paddles[i][j].rect.y = SCREEN_HEIGHT - (50 + i * 30); // Menempatkan paddle di bagian bawah layar
            paddles[i][j].rect.width = PADDLE_WIDTH;
            paddles[i][j].rect.height = PADDLE_HEIGHT;
            paddles[i][j].speed.x = PADDLE_SPEED;
        }
    }
}

// Update posisi semua paddle berdasarkan input
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

// Menggambar semua paddle di layar
void DrawPaddles(Paddle paddles[PADDLE_ROWS][PADDLE_COLS]) {
    for (int i = 0; i < PADDLE_ROWS; i++) {
        for (int j = 0; j < PADDLE_COLS; j++) {
            DrawRectangleRec(paddles[i][j].rect, BLACK);
        }
    }
}
