// Nama : Muhammad Raihan Abubakar
// Nama fitur : paddle 
// Deskripsi : paddle berfungsi untuk memantulkan dan mengarahkan bola agar bisa menghancurkan block

#include <stdlib.h>
#include "paddle.h"
#include "BOLA.h"
#include "powerup.h" // untuk fungsi UpdateActivePowerUps

#define SCREEN_WI 830 // lebar layar
#define SCREEN_HE 600 // tinggi layar 

void InitPaddles(Paddle paddles[PADDLE_ROWS][PADDLE_COLS]) {
    for (int i = 0; i < PADDLE_ROWS; i++) { 
        for (int j = 0; j < PADDLE_COLS; j++) {
            paddles[i][j].rect = (Rectangle){
                (SCREEN_WI - PADDLE_WIDTH) / 2, 
                SCREEN_HE - PADDLE_HEIGHT - 10, 
                PADDLE_WIDTH, 
                PADDLE_HEIGHT
            };
            paddles[i][j].speed = (Vector2){PADDLE_SPEED, 0};
            paddles[i][j].activePowerUps = NULL; // inisialisasi linked list kosong
        }
    }
}

void UpdatePaddles(Paddle paddles[PADDLE_ROWS][PADDLE_COLS], float deltaTime) {
    for (int i = 0; i < PADDLE_ROWS; i++) {
        for (int j = 0; j < PADDLE_COLS; j++) {
            // Gerakan paddle kiri dan kanan
            if (IsKeyDown(KEY_LEFT) && paddles[i][j].rect.x > 0) {
                paddles[i][j].rect.x -= paddles[i][j].speed.x;
            }
            if (IsKeyDown(KEY_RIGHT) && paddles[i][j].rect.x < SCREEN_WI - paddles[i][j].rect.width) {
                paddles[i][j].rect.x += paddles[i][j].speed.x;
            }

            // Clamp posisi paddle agar tidak keluar layar
            if (paddles[i][j].rect.x < 0) {
                paddles[i][j].rect.x = 0;
            }
            float rightEdge = paddles[i][j].rect.x + paddles[i][j].rect.width;
            if (rightEdge > SCREEN_WI) {
                paddles[i][j].rect.x = SCREEN_WI - paddles[i][j].rect.width;
            }

            // Perbarui efek power-up (pakai linked list)
            UpdateActivePowerUps(&paddles[i][j], deltaTime);
        }
    }
}

void DrawPaddles(Paddle paddles[PADDLE_ROWS][PADDLE_COLS]) {
    for (int i = 0; i < PADDLE_ROWS; i++) { 
        for (int j = 0; j < PADDLE_COLS; j++) {
            // Default warna paddle
            Color color = (Color){0, 255, 255, 255}; // Biru terang

            // Cek apakah ada efek paddle panjang
            ActivePowerUp *current = paddles[i][j].activePowerUps;
            while (current != NULL) {
                if (current->type == POWERUP_LONG_PADDLE) {
                    color = (Color){255, 165, 0, 255}; // Oranye
                    break;
                }
                current = current->next;
            }

            DrawRectangleRec(paddles[i][j].rect, color);
        }
    }
}
