#include "skor.h"
#include <stdio.h>

#define SCREEN_WIDTH 1000

// Inisialisasi skor untuk semua pemain
void InitSkor(Skor skor[MAX_PLAYERS]) {
    for (int i = 0; i < MAX_PLAYERS; i++) {
        skor[i].score = 0;
    }
}

// Tambah skor untuk satu pemain
void TambahSkor(Skor *skor, int nilai) {
    skor->score += nilai;
}

// Tampilkan skor di layar
void DrawSkor(Skor skor[MAX_PLAYERS]) {
    for (int i = 0; i < MAX_PLAYERS; i++) {
        char scoreText[20];
        sprintf(scoreText, "Score: %d", skor[i].score);
        
        // Hitung posisi x agar teks berada di pojok kanan atas
        int posX = 870;    // Posisi pojok kanan atas
        int posY = 50;     // Jarak vertikal antar pemain
        
        DrawText(scoreText, posX, posY, 20, WHITE);
    }
}
