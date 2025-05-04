// Nama : Muhammad Raihan Abubakar
// Nama fitur : paddle 
// Deskripsi : paddle berfungsi untuk memantulkan dan mengarahkan bola agar bisa menghancurkan block

#include "paddle.h"

#define SCREEN_WIDTH 830 // lebar layar
#define SCREEN_HEIGHT 600 // tinggi layar 

void InitPaddles(Paddle paddles[PADDLE_ROWS][PADDLE_COLS]) {
    for (int i = 0; i < PADDLE_ROWS; i++) { 
        for (int j = 0; j < PADDLE_COLS; j++) { // loop untuk setiap baris dan kolom paddle, untuk mengakses setiap elemen dalam array 
            paddles[i][j].rect = (Rectangle){(SCREEN_WIDTH - PADDLE_WIDTH) / 2, SCREEN_HEIGHT - PADDLE_HEIGHT - 10, PADDLE_WIDTH, PADDLE_HEIGHT}; // untuk menentukan posisi x, y 
            paddles[i][j].speed = (Vector2){PADDLE_SPEED, 0}; // untuk menyimpan kecepatan paddle 
        }
    }
}

void UpdatePaddles(Paddle paddles[PADDLE_ROWS][PADDLE_COLS]) {
    for (int i = 0; i < PADDLE_ROWS; i++) {
        for (int j = 0; j < PADDLE_COLS; j++) {  // loop untuk mengupdate semua paddle
            if (IsKeyDown(KEY_LEFT) && paddles[i][j].rect.x > 0) { // jika tombol arah kiri dipencet dan posisi x lebih dari 0 (tidak di luar batas layar)
                paddles[i][j].rect.x -= paddles[i][j].speed.x; // posisi x paddle berkurang sesuai dengan kecepatan paddle
            }
            if (IsKeyDown(KEY_RIGHT) && paddles[i][j].rect.x < SCREEN_WIDTH - PADDLE_WIDTH) { // jika tombol arah kanan dipencet dan posisi x paddle kurang dari batas kanan layar
                paddles[i][j].rect.x += paddles[i][j].speed.x; // posisi x paddle bertambah sesuai dengan kecepatan paddle 
            }
        }
    }
}

void DrawPaddles(Paddle paddles[PADDLE_ROWS][PADDLE_COLS]) {
    for (int i = 0; i < PADDLE_ROWS; i++) { 
        for (int j = 0; j < PADDLE_COLS; j++) { // loop untuk menggambar semua paddle 
            DrawRectangleRec(paddles[i][j].rect, (Color){0, 255, 255, 255}); // menggambar paddle dengan warna biru terang 
        }
    }
}
