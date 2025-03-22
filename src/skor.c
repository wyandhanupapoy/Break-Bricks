#include "skor.h"
#include "game_state.h"
#include <stdio.h>

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
    // 🔹 Hapus area lama agar skor tidak bertumpuk
    int fontSize = 20;
    char scoreText[20];
    sprintf(scoreText, "Score: %d", skor[0].score);
    
    Vector2 textSize = MeasureTextEx(GetFontDefault(), scoreText, fontSize, 2);
    DrawRectangle(x - 5, y - 5, textSize.x + 10, textSize.y + 10, BLACK);

    // 🔹 Gambar teks skor dengan warna kontras
    DrawTextEx(GetFontDefault(), scoreText, (Vector2){x, y}, fontSize, 2, WHITE);
}
