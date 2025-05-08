// Nama : Muhammad Raihan Abubakar
// Nama fitur : paddle 
// Deskripsi : paddle berfungsi untuk memantulkan dan mengarahkan bola agar bisa menghancurkan block

#include "paddle.h"
#include "BOLA.h"

#define SCREEN_WI 830 // lebar layar
#define SCREEN_HE 600 // tinggi layar 

void InitPaddles(Paddle paddles[PADDLE_ROWS][PADDLE_COLS]) {
    for (int i = 0; i < PADDLE_ROWS; i++) { 
        for (int j = 0; j < PADDLE_COLS; j++) { // loop untuk setiap baris dan kolom paddle, untuk mengakses setiap elemen dalam array 
            paddles[i][j].rect = (Rectangle){(SCREEN_WI - PADDLE_WIDTH) / 2, SCREEN_HE - PADDLE_HEIGHT - 10, PADDLE_WIDTH, PADDLE_HEIGHT}; // untuk menentukan posisi x, y 
            paddles[i][j].speed = (Vector2){PADDLE_SPEED, 0}; // untuk menyimpan kecepatan paddle 
            paddles[i][j].powerUpTimer = 0.0f;    // Timer efek power-up
            paddles[i][j].activePowerUp = -1;     // Tidak ada power-up aktif
        }
    }
}

void UpdatePaddles(Paddle paddles[PADDLE_ROWS][PADDLE_COLS], float deltaTime) {
    for (int i = 0; i < PADDLE_ROWS; i++) {
        for (int j = 0; j < PADDLE_COLS; j++) {  // loop untuk mengupdate semua paddle
            if (IsKeyDown(KEY_LEFT) && paddles[i][j].rect.x > 0) { // jika tombol arah kiri dipencet dan posisi x lebih dari 0 (tidak di luar batas layar)
                paddles[i][j].rect.x -= paddles[i][j].speed.x; // posisi x paddle berkurang sesuai dengan kecepatan paddle
            }
            if (IsKeyDown(KEY_RIGHT) && paddles[i][j].rect.x < SCREEN_WI - PADDLE_WIDTH) { // jika tombol arah kanan dipencet dan posisi x paddle kurang dari batas kanan layar
                paddles[i][j].rect.x += paddles[i][j].speed.x; // posisi x paddle bertambah sesuai dengan kecepatan paddle 
            }
            // ⬇️ Tambahkan clamp posisi paddle ⬇️
            float rightEdge = paddles[i][j].rect.x + paddles[i][j].rect.width;
            if (rightEdge > SCREEN_WI) {
                paddles[i][j].rect.x = SCREEN_WI - paddles[i][j].rect.width;
            }
            if (paddles[i][j].rect.x < 0) {
                paddles[i][j].rect.x = 0;
            }
            // Update efek power-up
            if (paddles[i][j].powerUpTimer > 0) {
                paddles[i][j].powerUpTimer -= deltaTime;
                
                // Reset efek jika timer habis
                if (paddles[i][j].powerUpTimer <= 0) {
                    switch (paddles[i][j].activePowerUp) {
                        case POWERUP_LONG_PADDLE:
                            paddles[i][j].rect.width = PADDLE_WIDTH_DEFAULT;
                            break;
                    }
                    paddles[i][j].activePowerUp = -1;
                }
            }        
        }
    }
}

void DrawPaddles(Paddle paddles[PADDLE_ROWS][PADDLE_COLS]) {
    for (int i = 0; i < PADDLE_ROWS; i++) { 
        for (int j = 0; j < PADDLE_COLS; j++) { // loop untuk menggambar semua paddle 
            // Warna berbeda jika ada efek power-up
            Color color = (Color){0, 255, 255, 255};  // Default: biru terang
            if (paddles[i][j].activePowerUp == POWERUP_LONG_PADDLE) {
                color = (Color){255, 165, 0, 255};    // Oranye jika paddle panjang
            }
            DrawRectangleRec(paddles[i][j].rect, color); // menggambar paddle
        }
    }
}
