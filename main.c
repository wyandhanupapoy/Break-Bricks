#include "raylib.h"
#include "padle.h"
#include "block.h"

int main()
{
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Breakout - Paddle");
    InitWindow(800, 600, "Breakout - Blocks");
    SetTargetFPS(60);

    Paddle paddles[PADDLE_ROWS][PADDLE_COLS]; // Deklarasi array paddle
    InitPaddles(paddles);                     // Inisialisasi paddle

    Block blocks[ROWS][COLS];
    InitBlocks(blocks);

    while (!WindowShouldClose())
    {
        // Update logika paddle
        UpdatePaddles(paddles);

        BeginDrawing();
        ClearBackground(RAYWHITE);

        DrawText("Breakout Game!", 300, 20, 20, BLACK);

        // Gambar semua paddle
        DrawPaddles(paddles);
        DrawBlocks(blocks);

        EndDrawing();
    }

    CloseWindow();
    return 0;
}
