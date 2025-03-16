#include "skor.h"
#include <stdio.h>

#define SCREEN_WIDTH 800

void InitSkor(Skor skor[MAX_PLAYERS]) {
    for (int i = 0; i < MAX_PLAYERS; i++) {
        skor[i].score = 0;
    }
}

void TambahSkor(Skor *skor, int nilai) {
    skor->score += nilai;
}

void DrawSkor(Skor skor[MAX_PLAYERS]) {
    for (int i = 0; i < MAX_PLAYERS; i++) {
        char scoreText[20];
        sprintf(scoreText, "Score: %d", skor[i].score);
        
        int textWidth = MeasureText(scoreText, 20);
        int posX = SCREEN_WIDTH - textWidth - 20;
        int posY = 10; // Posisi Y diatur agar sejajar dengan nyawa

        DrawText(scoreText, posX, posY, 20, BLACK);
    }
}