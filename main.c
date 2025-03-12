#include "raylib.h"
#include "padle.h"

int main()
{
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Breakout - Paddle");
    SetTargetFPS(60);

    Paddle paddle;
    InitPaddle(&paddle);

    while (!WindowShouldClose())
    {
        // Update logika paddle
        UpdatePaddle(&paddle);

        BeginDrawing();
        ClearBackground(RAYWHITE);

        DrawText("Breakout Game!", 300, 20, 20, BLACK);

        // Gambar paddle
        DrawPaddle(&paddle);

        EndDrawing();
    }

    CloseWindow();
    return 0;
}