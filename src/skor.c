#include "skor.h"
#include "game_state.h"
#include <stdio.h>
#include <math.h>

void InitSkor(Skor skor[MAX_PLAYERS])
{
    for (int i = 0; i < MAX_PLAYERS; i++)
    {
        skor[i].score = 0;
    }
}

void TambahSkorDenganWaktu(Skor *skor, float elapsedTime)
{
    // 🔹 Hitung pengurang skor berdasarkan waktu
    float drop = (elapsedTime / TIME_FACTOR) * (MAX_SCORE_PER_BLOCK - MIN_SCORE_PER_BLOCK);
    int skorTambahan = MAX_SCORE_PER_BLOCK - (int)drop;

    // 🔹 Clamp skor antara minimal dan maksimal
    if (skorTambahan < MIN_SCORE_PER_BLOCK) skorTambahan = MIN_SCORE_PER_BLOCK;
    if (skorTambahan > MAX_SCORE_PER_BLOCK) skorTambahan = MAX_SCORE_PER_BLOCK;

    skor->score += skorTambahan;
}

void DrawSkor(Skor skor[MAX_PLAYERS], int x, int y)
{
    int fontSize = 20;
    char scoreText[30];
    sprintf(scoreText, "Score: %d", skor[0].score);

    Vector2 textSize = MeasureTextEx(GetFontDefault(), scoreText, fontSize, 2);
    DrawRectangle(x - 5, y - 5, textSize.x + 10, textSize.y + 10, BLACK);
    DrawTextEx(GetFontDefault(), scoreText, (Vector2){x, y}, fontSize, 2, WHITE);
}