#include "layout.h"
#include <stdio.h>

#define SCREEN_WIDTH 1000
#define SCREEN_HEIGHT 650

void DrawGameLayout(Block blocks[BLOCK_ROWS][BLOCK_COLS], Paddle paddles[PADDLE_ROWS][PADDLE_COLS], Bola bola[BOLA_ROWS][BOLA_COLS], Stopwatch stopwatch[STOPWATCH_ROWS][STOPWATCH_COLS], Nyawa nyawa[NYAWA_BARIS][NYAWA_KOLOM], Skor skor[MAX_PLAYERS]) {
    // Menggambar background
    ClearBackground(BLACK); // Menggunakan warna latar belakang yang sesuai

    // Menggambar garis pembatas
    DrawLine(835, 0, 835, SCREEN_HEIGHT, WHITE);

    // Menggambar TataCaraPembatas
    DrawRectangle(0, 600, 835, 50, WHITE);
    DrawText("<- -> Bergerak       P - Pause       Esc - Exit", 150, 610, 20, BLACK);

    // Menggambar blok
    DrawBlocks(blocks);

    // Menggambar paddle
    DrawPaddles(paddles);

    // Menggambar bola
    DrawBola(bola);

    // Menggambar nyawa
    SetNyawaPosition(nyawa, NYAWA_X, NYAWA_Y);
    DrawNyawa(nyawa);

    // Menggambar skor
    DrawSkor(skor, SCORE_X, SCORE_Y); // Modifikasi DrawSkor untuk menerima posisi

    // Menggambar stopwatch
    DrawStopwatch(stopwatch, STOPWATCH_X, STOPWATCH_Y); // Modifikasi DrawStopwatch untuk menerima posisi
}
