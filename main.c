#include "raylib.h"
#include "padle.h"

int main()
{
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Breakout - Paddle");
    SetTargetFPS(60);

    Paddle paddles[PADDLE_ROWS][PADDLE_COLS]; // Deklarasi array paddle
    InitPaddles(paddles);                     // Inisialisasi paddle

    while (!WindowShouldClose())
    {
        // Update logika paddle
        UpdatePaddles(paddles);

        BeginDrawing();
        ClearBackground(RAYWHITE);

        DrawText("Breakout Game!", 300, 20, 20, BLACK);

        // Gambar semua paddle
        DrawPaddles(paddles);

        EndDrawing();
    }

    CloseWindow();
    return 0;
}