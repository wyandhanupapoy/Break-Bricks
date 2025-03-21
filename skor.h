#ifndef SKOR_H
#define SKOR_H

#include <raylib.h>
#include "leaderboard.h"
#include "game_state.h"

typedef struct
{
    int score; // Skor pemain
} Skor;

void InitSkor(Skor skor[MAX_PLAYERS]);
void TambahSkor(Skor *skor, int nilai);
void DrawSkor(Skor skor[MAX_PLAYERS], int x, int y);

#endif // SKOR_H