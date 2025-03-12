#ifndef PADLE_H
#define PADLE_H

#include "raylib.h"

// Ukuran layar
#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600

// Konstanta untuk paddle
#define PADDLE_ROWS 1    // Jumlah baris paddle (bisa diubah jika ingin lebih dari 1)
#define PADDLE_COLS 2    // Jumlah paddle dalam satu baris
#define PADDLE_WIDTH 100
#define PADDLE_HEIGHT 20
#define PADDLE_SPEED 5

// Struktur Paddle
typedef struct {
    Rectangle rect;  // Posisi dan ukuran paddle
    Vector2 speed;   // Kecepatan paddle
} Paddle;

// Deklarasi fungsi
void InitPaddles(Paddle paddles[PADDLE_ROWS][PADDLE_COLS]);
void UpdatePaddles(Paddle paddles[PADDLE_ROWS][PADDLE_COLS]);
void DrawPaddles(Paddle paddles[PADDLE_ROWS][PADDLE_COLS]);

#endif
