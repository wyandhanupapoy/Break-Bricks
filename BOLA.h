#ifndef BOLA_H
#define BOLA_H

#include "raylib.h"

// Renamed to avoid conflicts with other headers
#define BOLA_ROWS 2   // Jumlah bola dalam array 2D
#define BOLA_COLS 2   // Bisa ditambah sesuai kebutuhan
#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600

typedef struct {
    Vector2 position; // Posisi bola
    Vector2 speed;    // Kecepatan bola
    float radius;     // Radius bola
    Color color;      // Warna bola
} Bola;

void InitBola(Bola bola[BOLA_ROWS][BOLA_COLS]);
void UpdateBola(Bola bola[BOLA_ROWS][BOLA_COLS]);
void DrawBola(Bola bola[BOLA_ROWS][BOLA_COLS]);

#endif // BOLA_H