#include "layout.h"
#include "raylib.h"

void DrawGameLayout(Block blocks[BLOCK_ROWS][BLOCK_COLS], 
                    Paddle paddles[PADDLE_ROWS][PADDLE_COLS], 
                    Bola bola[BOLA_ROWS][BOLA_COLS], 
                    Stopwatch stopwatch[STOPWATCH_ROWS][STOPWATCH_COLS], 
                    Nyawa nyawa[NYAWA_BARIS][NYAWA_KOLOM],  
                    Skor skor[MAX_PLAYERS])
{
    // 🔹 Latar belakang panel bawah
    DrawRectangle(0, 600, 835, 50, WHITE);
    DrawText("<- -> Move  |  P - Pause  |  F - Fullscreen  |  Esc - Exit", 60, 610, 20, BLACK);

    // 🔹 Garis batas kanan
    DrawLine(835, 0, 835, SCREEN_HEIGHT, WHITE);

    // 🔹 Gambar elemen permainan
    DrawPaddles(paddles);
    DrawBlocks(blocks);
    DrawBola(bola);
    DrawNyawa(nyawa);
    DrawSkor(skor, SCORE_X, SCORE_Y);
    DrawStopwatch(stopwatch);
}
