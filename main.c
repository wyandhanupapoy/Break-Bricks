#include "raylib.h"
#include "padle.h"
#include "block.h"
#include "BOLA.h"
#include "skor.h"
#include "stopwatch.h"

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600

int main()
{
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Breakout - Paddle");
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Break Bricks - Skor");
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Breakout - Blocks");
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Stopwatch in Raylib");

    SetTargetFPS(60);

    Paddle paddles[PADDLE_ROWS][PADDLE_COLS]; // Deklarasi array paddle
    InitPaddles(paddles);                     // Inisialisasi paddle

    Block blocks[ROWS][COLS];
    InitBlocks(blocks);

    Bola bola[ROWS][COLS];
    InitBola(bola);

    Skor skor[MAX_PLAYERS];
    InitSkor(skor);

    Stopwatch sw[ROWS][COLS]; // Deklarasi stopwatch sebagai array 2D
    InitStopwatch(sw);        // Inisialisasi stopwatch

    while (!WindowShouldClose())
    {
        // Update logika paddle
        UpdatePaddles(paddles);
        UpdateBola(bola);
        UpdateStopwatch(sw); // Update stopwatch setiap frame

        BeginDrawing();
        ClearBackground(RAYWHITE);
        ClearBackground(BLACK);

        DrawText("Breakout Game!", 300, 20, 20, BLACK);
        DrawText("Stopwatch Example", 280, 20, 20, BLACK);

        // Gambar semua paddle
        DrawPaddles(paddles);
        DrawBlocks(blocks);
        DrawBola(bola);
        DrawSkor(skor);
        DrawStopwatch(sw); // Gambar stopwatch di tengah layar

        EndDrawing();
    }

    CloseWindow();
    return 0;
}
