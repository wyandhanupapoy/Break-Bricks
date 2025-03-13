<<<<<<< HEAD
<<<<<<< HEAD
=======
>>>>>>> 588526b9be4263d9e33322941397818ad2e2afc5
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
<<<<<<< HEAD
}
<<<<<<< HEAD
=======
>>>>>>> origin/blok
=======
>>>>>>> 588526b9be4263d9e33322941397818ad2e2afc5
=======
}
>>>>>>> da05ab08fa69721fe451b19f47521dfc858c505c
