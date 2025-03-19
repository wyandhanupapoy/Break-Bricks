#ifndef SKOR_H
#define SKOR_H

#include <raylib.h>

typedef struct {
    int score; // Skor pemain
} Skor;

void InitSkor(Skor *skor);
void TambahSkor(Skor *skor, int nilai);
void DrawSkor(const Skor *skor);

#endif // SKOR_H
