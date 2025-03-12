#ifndef PADLE_H
#define PADLE_H

#include <raylib.h>

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600
#define PADDLE_WIDTH 100
#define PADDLE_HEIGHT 20
#define PADDLE_SPEED 5

// Struktur Paddle
typedef struct {
    Rectangle rect;  // Posisi dan ukuran paddle
    Vector2 speed;   // Kecepatan paddle
} Paddle;

// Deklarasi fungsi
void InitPaddle(Paddle *paddle);
void UpdatePaddle(Paddle *paddle);
void DrawPaddle(Paddle *paddle);

#endif
