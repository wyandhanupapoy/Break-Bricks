#include "raylib.h"
#include "padle.h"
#include "block.h"
#include "BOLA.h"
#include "skor.h"

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600

int main()
{
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Breakout - Paddle");
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Break Bricks - Skor");
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Breakout - Blocks");
    SetTargetFPS(60);

    Paddle paddles[PADDLE_ROWS][PADDLE_COLS]; // Deklarasi array paddle
    InitPaddles(paddles);                     // Inisialisasi paddle

    Block blocks[ROWS][COLS];
    InitBlocks(blocks);

    Bola bola[ROWS][COLS];
    InitBola(bola);

    Skor skor[MAX_PLAYERS];
    InitSkor(skor);

    while (!WindowShouldClose())
    {
        // Update logika paddle
        UpdatePaddles(paddles);
        UpdateBola(bola);

        BeginDrawing();
        ClearBackground(RAYWHITE);
        ClearBackground(BLACK);

        DrawText("Breakout Game!", 300, 20, 20, BLACK);

        // Gambar semua paddle
        DrawPaddles(paddles);
        DrawBlocks(blocks);
        DrawBola(bola);
        DrawSkor(skor);

        EndDrawing();
    }

    CloseWindow();
    return 0;
}
