#include "paddle.h"
#include "block.h"
#include "BOLA.h"
#include "nyawa.h"
#include "skor.h"
#include "stopwatch.h"
#include "leaderboard.h" // Include the leaderboard header

#include <stdio.h>
#include <raylib.h>

#define SCREEN_WIDTH 830
#define SCREEN_HEIGHT 600

int main()
{
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Breakout Game");
    SetTargetFPS(60);

    Paddle paddles[PADDLE_ROWS][PADDLE_COLS];
    InitPaddles(paddles);

    Block blocks[BLOCK_ROWS][BLOCK_COLS];
    InitBlocks(blocks);

    Bola bola[BOLA_ROWS][BOLA_COLS];
    InitBola(bola);

    Nyawa nyawa[NYAWA_BARIS][NYAWA_KOLOM];
    InitNyawa(nyawa, 3); // Start with 3 lives

    Stopwatch stopwatch[STOPWATCH_ROWS][STOPWATCH_COLS];
    Skor skor[MAX_PLAYERS];
    InitStopwatch(stopwatch);
    InitSkor(skor);

    LeaderboardEntry leaderboard[MAX_PLAYERS];
    InitLeaderboard(leaderboard); // Initialize the leaderboard

    GameState gameState = GAME_START;
    bool isPaused = false;

    while (!WindowShouldClose())
    {
        if (IsKeyPressed(KEY_P))
            isPaused = !isPaused;

        if (!isPaused)
        {
            switch (gameState)
            {
            case GAME_START:
                UpdatePaddles(paddles);
                UpdateBola(bola, paddles, blocks, &gameState, &skor[0], stopwatch);

                if (IsKeyPressed(KEY_SPACE))
                {
                    gameState = GAME_PLAY;
                    // Set ball speed when the game starts
                    bola[0][0].speed = (Vector2){5, -5}; // Set initial ball speed
                }
                break;

            case GAME_PLAY:
                UpdatePaddles(paddles);
                UpdateBola(bola, paddles, blocks, &gameState, &skor[0], stopwatch);
                UpdateStopwatch(stopwatch); // Update stopwatch

                for (int ballRow = 0; ballRow < BOLA_ROWS; ballRow++)
                {
                    for (int blockRow = 0; blockRow < BLOCK_ROWS; blockRow++)
                    {
                        for (int blockCol = 0; blockCol < BLOCK_COLS; blockCol++)
                        {
                            if (blocks[blockRow][blockCol].active &&
                                CheckBallBlockCollision(
                                    bola[ballRow][0].position,
                                    bola[ballRow][0].radius,
                                    blocks[blockRow][blockCol].rect))
                            {
                                blocks[blockRow][blockCol].active = false;

                                // Calculate score based on time
                                int timeElapsed = (int)stopwatch[0][0].time; // Get elapsed time
                                int scoreToAdd = 50 - timeElapsed;           // Score decreases over time
                                if (scoreToAdd < 5)
                                    scoreToAdd = 5; // Ensure score is not less than 5
                                if (scoreToAdd > 50)
                                    scoreToAdd = 50; // Ensure score is not more than 50
                                TambahSkor(&skor[0], scoreToAdd);

                                bola[ballRow][0].speed.y *= -1;

                                if (AllBlocksDestroyed(blocks))
                                {
                                    gameState = GAME_WIN;
                                }
                                break;
                            }
                        }
                    }

                    if (bola[ballRow][0].position.y + bola[ballRow][0].radius > SCREEN_HEIGHT)
                    {
                        KurangiNyawa(nyawa);
                        if (!AnyLivesLeft(nyawa))
                        {
                            gameState = GAME_OVER;
                        }
                        else
                        {
                            ResetBola(bola);
                            gameState = GAME_START;
                        }
                    }
                }
                break;

            case GAME_OVER:
                if (IsKeyPressed(KEY_R))
                {
                    InitBlocks(blocks);
                    InitNyawa(nyawa, 3);
                    InitBola(bola);
                    gameState = GAME_START;
                }
                break;

            case GAME_WIN:
                if (IsKeyPressed(KEY_R))
                {
                    InitBlocks(blocks);
                    InitNyawa(nyawa, 3);
                    InitBola(bola);
                    InitSkor(skor);
                    gameState = GAME_START;
                }
                break;
            }
        }

        BeginDrawing();
        ClearBackground(RAYWHITE);

        DrawPaddles(paddles);
        DrawBlocks(blocks);
        DrawBola(bola);
        DrawNyawa(nyawa);
        DrawSkor(skor);           // Display score
        DrawStopwatch(stopwatch); // Display stopwatch

        switch (gameState)
        {
        case GAME_START:
            DrawText("PRESS SPACE TO START", SCREEN_WIDTH / 2 - MeasureText("PRESS SPACE TO START", 30) / 2, SCREEN_HEIGHT / 2, 30, GRAY);
            break;
        case GAME_OVER:
            DrawRectangle(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, WHITE);
            DrawText("GAME OVER", SCREEN_WIDTH / 2 - MeasureText("GAME OVER", 40) / 2, SCREEN_HEIGHT / 2 - 40, 40, RED);
            DrawText("PRESS R TO RESTART", SCREEN_WIDTH / 2 - MeasureText("PRESS R TO RESTART", 20) / 2, SCREEN_HEIGHT / 2 + 20, 20, DARKGRAY);
            // Display the leaderboard
            DrawText("LEADERBOARD", SCREEN_WIDTH / 2 - MeasureText("LEADERBOARD", 30) / 2, SCREEN_HEIGHT / 2 + 60, 30, BLACK);
            DrawLeaderboard(leaderboard); // Draw the leaderboard
            break;
        case GAME_WIN:
            DrawRectangle(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, WHITE);
            DrawText("YOU WIN!", SCREEN_WIDTH / 2 - MeasureText("YOU WIN!", 40) / 2, SCREEN_HEIGHT / 2 - 40, 40, GREEN);
            DrawText("PRESS R TO RESTART", SCREEN_WIDTH / 2 - MeasureText("PRESS R TO RESTART", 20) / 2, SCREEN_HEIGHT / 2 + 20, 20, DARKGRAY);
            // Add to leaderboard on win
            AddToLeaderboard(leaderboard, "Player", skor[0].score, stopwatch[0][0].time);
            // Display the leaderboard
            DrawText("LEADERBOARD", SCREEN_WIDTH / 2 - MeasureText("LEADERBOARD", 30) / 2, SCREEN_HEIGHT / 2 + 60, 30, BLACK);
            DrawLeaderboard(leaderboard); // Draw the leaderboard
            break;
        }

        if (isPaused)
        {
            DrawRectangle(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, Fade(BLACK, 0.7f));
            DrawText("GAME PAUSED", SCREEN_WIDTH / 2 - MeasureText("GAME PAUSED", 40) / 2, SCREEN_HEIGHT / 2 - 40, 40, WHITE);
            DrawText("PRESS P TO CONTINUE", SCREEN_WIDTH / 2 - MeasureText("PRESS P TO CONTINUE", 20) / 2, SCREEN_HEIGHT / 2 + 20, 20, WHITE);
            stopwatch[0][0].running = false; // Hentikan stopwatch saat dijeda
        }
        else{
            stopwatch[0][0].running = true; // Jalankan stopwatch saat tidak dijeda
        }

        EndDrawing();
    }

    CloseWindow();
    return 0;
}