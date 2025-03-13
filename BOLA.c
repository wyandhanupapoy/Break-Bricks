#include "BOLA.h"

// Inisialisasi bola pada array 2D
void InitBola(Bola bola[BOLA_ROWS][BOLA_COLS]) {
    for (int i = 0; i < BOLA_ROWS; i++) {
        for (int j = 0; j < BOLA_COLS; j++) {
            bola[i][j].position = (Vector2){400 + j * 50, 300 + i * 50}; // Posisi awal
            bola[i][j].speed = (Vector2){4, -4}; // Kecepatan awal bola
            bola[i][j].radius = 10;
            bola[i][j].color = RED;
        }
    }
}

// Update posisi bola
void UpdateBola(Bola bola[BOLA_ROWS][BOLA_COLS]) {
    for (int i = 0; i < BOLA_ROWS; i++) {
        for (int j = 0; j < BOLA_COLS; j++) {
            bola[i][j].position.x += bola[i][j].speed.x;
            bola[i][j].position.y += bola[i][j].speed.y;
            
            // Pantulan dinding kiri & kanan
            if (bola[i][j].position.x - bola[i][j].radius <= 0 || bola[i][j].position.x + bola[i][j].radius >= SCREEN_WIDTH) {
                bola[i][j].speed.x *= -1;
            }
            
            // Pantulan dinding atas
            if (bola[i][j].position.y - bola[i][j].radius <= 0) {
                bola[i][j].speed.y *= -1;
            }
        }
    }
}

// Gambar bola pada layar
void DrawBola(Bola bola[BOLA_ROWS][BOLA_COLS]) {
    for (int i = 0; i < BOLA_ROWS; i++) {
        for (int j = 0; j < BOLA_COLS; j++) {
            DrawCircleV(bola[i][j].position, bola[i][j].radius, bola[i][j].color);
        }
    }
}