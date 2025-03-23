/*
Nama Pembuat:   Wyandhanu Maulidan Nugraha
Nama Fitur:     Background
Deskripsi:      Fitur background untuk menampilkan efek latar belakang
*/

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
