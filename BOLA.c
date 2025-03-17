#include "bola.h"

// Inisialisasi bola
void InitBola(Bola *bola, Vector2 startPosition, Vector2 startSpeed, float radius) {
    bola->position = startPosition;
    bola->speed = startSpeed;
    bola->radius = radius;
    bola->active = true;
}

// Update pergerakan bola
void UpdateBola(Bola *bola, int screenWidth, int screenHeight) {
    if (!bola->active) return;

    // Update posisi bola
    bola->position.x += bola->speed.x;
    bola->position.y += bola->speed.y;

    // Pantulan dari dinding kiri & kanan
    if (bola->position.x - bola->radius <= 0 || bola->position.x + bola->radius >= screenWidth) {
        bola->speed.x *= -1;
    }

    // Pantulan dari atas
    if (bola->position.y - bola->radius <= 0) {
        bola->speed.y *= -1;
    }

    // Game over jika bola jatuh ke bawah
    if (bola->position.y + bola->radius >= screenHeight) {
        bola->active = false;
    }
}

// Menggambar bola
void DrawBola(Bola *bola) {
    if (bola->active) {
        DrawCircleV(bola->position, bola->radius, RED);
    }
}
