#include "raylib.h"
#include "padle.h"
#include "block.h"
#include "BOLA.h"
#include "skor.h"
#include "stopwatch.h"
#include "nyawa.h"

// Global define for screen dimensions to ensure consistency
#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600

int main()
{
    // Only initialize the window once
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Breakout Game");
    SetTargetFPS(60);

    // Initialize game components
    Paddle paddles[PADDLE_ROWS][PADDLE_COLS];
    InitPaddles(paddles);

    Block blocks[BLOCK_ROWS][BLOCK_COLS];
    InitBlocks(blocks);

    Bola bola[BOLA_ROWS][BOLA_COLS];
    InitBola(bola);

    Skor skor[MAX_PLAYERS];
    InitSkor(skor);

    Stopwatch sw[STOPWATCH_ROWS][STOPWATCH_COLS];
    InitStopwatch(sw);

    // Inisialisasi nyawa
    Nyawa nyawa[NYAWA_BARIS][NYAWA_KOLOM];
    int totalNyawa = 3; // Contoh total nyawa
    InitNyawa(nyawa, totalNyawa);

    // Main game loop
    while (!WindowShouldClose())
    {
        // Update game logic
        UpdatePaddles(paddles);
        UpdateBola(bola);
        UpdateStopwatch(sw);

        // Check collisions between ball and blocks
        for (int ballRow = 0; ballRow < BOLA_ROWS; ballRow++)
        {
            for (int ballCol = 0; ballCol < BOLA_COLS; ballCol++)
            {
                // Check ball-paddle collision
                for (int padRow = 0; padRow < PADDLE_ROWS; padRow++)
                {
                    for (int padCol = 0; padCol < PADDLE_COLS; padCol++)
                    {
                        if (CheckCollisionCircleRec(
                                bola[ballRow][ballCol].position,
                                bola[ballRow][ballCol].radius,
                                paddles[padRow][padCol].rect))
                        {
                            // Reverse ball direction on y-axis when hitting paddle
                            bola[ballRow][ballCol].speed.y *= -1;

                            // Slightly adjust x direction based on where ball hit paddle
                            float paddleCenter = paddles[padRow][padCol].rect.x + paddles[padRow][padCol].rect.width / 2;
                            float ballDistFromCenter = bola[ballRow][ballCol].position.x - paddleCenter;
                            bola[ballRow][ballCol].speed.x = ballDistFromCenter * 0.05f;
                        }
                    }
                }

                // Check ball-block collision
                for (int blockRow = 0; blockRow < BLOCK_ROWS; blockRow++)
                {
                    for (int blockCol = 0; blockCol < BLOCK_COLS; blockCol++)
                    {
                        if (blocks[blockRow][blockCol].active &&
                            CheckCollisionCircleRec(
                                bola[ballRow][ballCol].position,
                                bola[ballRow][ballCol].radius,
                                blocks[blockRow][blockCol].rect))
                        {
                            blocks[blockRow][blockCol].active = false; // Deactivate the block
                            bola[ballRow][ballCol].speed.y *= -1;      // Reverse ball direction

                            // Add score when block is destroyed
                            TambahSkor(&skor[0], 10);
                        }
                    }
                }

                //  Check if ball is below screen (nyawa berkurang)
                if (bola[ballRow][ballCol].position.y + bola[ballRow][ballCol].radius > SCREEN_HEIGHT)
                {
                    // Kurangi nyawa karena bola jatuh
                    KurangiNyawa(nyawa);

                    // Reset ball position ke tengah dan reset kecepatan
                    bola[ballRow][ballCol].position = (Vector2){400, 300};
                    bola[ballRow][ballCol].speed = (Vector2){4, -4};
                }
            }
        }

        // Drawing
        BeginDrawing();
        ClearBackground(RAYWHITE); // Use consistent background

        DrawText("Breakout Game!", 300, 20, 20, BLACK);

        // Draw game elements
        DrawPaddles(paddles);
        DrawBlocks(blocks);
        DrawBola(bola);
        DrawSkor(skor);
        DrawStopwatch(sw);
        DrawNyawa(nyawa); // Tambahkan gambar nyawa di atas
        EndDrawing();
    }

    CloseWindow();
    return 0;
}
