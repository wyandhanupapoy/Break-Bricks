#include "skor.h"
#include "game_state.h"
#include <stdio.h>

#define SCREEN_WIDTH 1000

void InitSkor(Skor skor[MAX_PLAYERS])
{
    for (int i = 0; i < MAX_PLAYERS; i++)
    {
        skor[i].score = 0;
    }
}

void TambahSkor(Skor *skor, int nilai)
{
    skor->score += nilai;
}

void DrawSkor(Skor skor[MAX_PLAYERS], int x, int y)
{
    for (int i = 0; i < MAX_PLAYERS; i++)
    {
        char scoreText[20];
        sprintf(scoreText, "Score: %d", skor[i].score);
        DrawText(scoreText, x, y, 20, WHITE);
    }
}