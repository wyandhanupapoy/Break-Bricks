#ifndef BOLA_H
#define BOLA_H

#include "raylib.h"

#define ROWS 2   // Jumlah bola dalam array 2D
#define COLS 2   // Bisa ditambah sesuai kebutuhan
#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600

typedef struct {
    Vector2 position; // Posisi bola
    Vector2 speed;    // Kecepatan bola
    float radius;     // Radius bola
    Color color;      // Warna bola
} Bola;

void InitBola(Bola bola[ROWS][COLS]);
void UpdateBola(Bola bola[ROWS][COLS]);
void DrawBola(Bola bola[ROWS][COLS]);

#endif // BOLA_H