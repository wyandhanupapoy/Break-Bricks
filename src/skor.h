//Nama Pembuat: Siti Soviyyah
//Nama Fitur: Header skor.h
//Deskripsi: File ini berguna untuk memanggil fungsi-fungsi yang ada pada file skor.c


#ifndef SKOR_H
#define SKOR_H

#include <raylib.h>
#include "leaderboard.h"
#include "game_state.h"

#define MAX_SCORE_PER_BLOCK 50
#define MIN_SCORE_PER_BLOCK 5
#define TIME_FACTOR 10.0f

typedef struct
{
    int score; // Skor pemain
} Skor;

void InitSkor(Skor skor[MAX_PLAYERS]);
void TambahSkorDenganWaktu(Skor *skor, float elapsedTime);
void DrawSkor(Skor skor[MAX_PLAYERS], int x, int y);

#endif // SKOR_H