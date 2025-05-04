/*
Nama Pembuat:   Wyandhanu Maulidan Nugraha
Nama Fitur:     Background
Deskripsi:      Fitur background untuk menampilkan efek latar belakang
*/

#include "background.h"
#include <math.h>

static Star stars[MAX_STARS];
static Color gradientTop = {10, 10, 50, 255};  // Warna atas (gelap)
static Color gradientBottom = {30, 30, 100, 255}; // Warna bawah (lebih terang)
static float gradientOffset = 0; // Perubahan warna untuk animasi

// 🔹 Inisialisasi efek background
void InitBackground() {
    for (int i = 0; i < MAX_STARS; i++) {
        stars[i].position = (Vector2){GetRandomValue(0, 1000), GetRandomValue(0, 650)};
        stars[i].speed = GetRandomValue(1, 3);
    }
}

// 🔹 Update animasi background (gradasi + bintang jatuh)
void UpdateBackground() {
    // Gradasi warna bergerak
    gradientOffset += 0.005f;
    gradientTop.r = (int)(20 + sin(gradientOffset) * 20);
    gradientTop.g = (int)(20 + cos(gradientOffset) * 20);
    gradientBottom.b = (int)(100 + sin(gradientOffset) * 30);

    // Gerakan bintang jatuh
    for (int i = 0; i < MAX_STARS; i++) {
        stars[i].position.y += stars[i].speed;
        if (stars[i].position.y > 650) {
            stars[i].position.y = 0;
            stars[i].position.x = GetRandomValue(0, 1000);
        }
    }
}

// 🔹 Gambar animasi background
void DrawBackground() {
    // Gradasi background
    DrawRectangleGradientV(0, 0, 1000, 650, gradientTop, gradientBottom);

    // Efek bintang jatuh
    for (int i = 0; i < MAX_STARS; i++) {
        DrawCircleV(stars[i].position, 2, WHITE);
    }
}
