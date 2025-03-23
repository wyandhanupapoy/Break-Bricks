#ifndef BACKGROUND_H
#define BACKGROUND_H

#include <raylib.h>

#define MAX_STARS 100 // Jumlah bintang untuk efek luar angkasa

typedef struct {
    Vector2 position;
    float speed;
} Star;

// Fungsi inisialisasi dan update background
void InitBackground();
void UpdateBackground();
void DrawBackground();

#endif // BACKGROUND_H
