#include "skor.h"
#include "raylib.h"  // Tambahkan ini agar bisa menggunakan DrawText
#include <stdio.h>

#define SCREEN_WIDTH 1000

void InitSkor(Skor *skor) {
    if (skor != NULL) {
        skor->score = 0;
    }
}

void TambahSkor(Skor *skor, int nilai) {
    if (skor != NULL) {
        skor->score += nilai;
    }
}

void DrawSkor(const Skor *skor) {
    if (skor != NULL) {
        char scoreText[20];
        sprintf(scoreText, "Score: %d", skor->score);
        
        int posX = SCREEN_WIDTH - 130; // Pindahkan ke pojok kanan atas
        int posY = 50; // Sejajar dengan nyawa

        DrawText(scoreText, posX, posY, 20, WHITE);
    }
}
