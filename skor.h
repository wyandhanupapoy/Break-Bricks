#ifndef SKOR_H
#define SKOR_H

#include <raylib.h>

#define MAX_PLAYERS 1 // Jumlah pemain maksimal

typedef struct {
    int score; // Skor pemain
} Skor;

void InitSkor(Skor skor[MAX_PLAYERS]);
void TambahSkor(Skor *skor, int nilai);
void DrawSkor(Skor skor[MAX_PLAYERS]);
void ResetSkor(Skor *skor);

#endif // SKOR_H