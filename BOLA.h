#ifndef BOLA_H
#define BOLA_H

#include "raylib.h"

#define ROWS 1   // Jumlah bola dalam array 2D (bisa ditambah jika ingin lebih dari satu bola)
#define COLS 1   // Saat ini hanya satu bola, tapi bisa diperluas

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