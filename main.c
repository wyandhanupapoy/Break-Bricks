#include "paddle.h"
#include "block.h"
#include "BOLA.h"
#include "nyawa.h"
#include "skor.h"
#include "stopwatch.h"
#include "leaderboard.h"
#include "level.h"

#include <stdio.h>
#include <raylib.h>

#define SCREEN_WIDTH 1000
#define SCREEN_HEIGHT 650

int main()
{
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "F - Fullscreen                                                        Break Bricks");
    SetTargetFPS(60);

    bool isFullscreen = false;

    Paddle paddles[PADDLE_ROWS][PADDLE_COLS];
    InitPaddles(paddles);

    Block blocks[BLOCK_ROWS][BLOCK_COLS];
    int currentLevel = 1;
    InitGameLevel(currentLevel);
    SetLevel(blocks, currentLevel);

    Bola bola[BOLA_ROWS][BOLA_COLS];
    InitBola(bola);

    Nyawa nyawa[NYAWA_BARIS][NYAWA_KOLOM];
    InitNyawa(nyawa, 3);
    SetNyawaPosition(nyawa, 870, 10);

    Stopwatch stopwatch[STOPWATCH_ROWS][STOPWATCH_COLS];
    Skor skor[MAX_PLAYERS];
    InitStopwatch(stopwatch);
    InitSkor(skor);

    LeaderboardEntry leaderboard[MAX_PLAYERS];
    InitLeaderboard(leaderboard);

    GameState gameState = GAME_START;
    bool isPaused = false;

    while (!WindowShouldClose())
    {
        if (IsKeyPressed(KEY_F))
        {
            isFullscreen = !isFullscreen;
            ToggleFullscreen();
        }

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
                }
                break;

            case GAME_PLAY:
                UpdatePaddles(paddles);
                UpdateBola(bola, paddles, blocks, &gameState, &skor[0], stopwatch);
                UpdateStopwatch(stopwatch);

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
                                HandleBlockCollision(&blocks[blockRow][blockCol]);
                                bola[ballRow][0].speed.y *= -1;

                                int timeElapsed = (int)stopwatch[0][0].time;
                                int scoreToAdd = 50 - timeElapsed;
                                if (scoreToAdd < 5) scoreToAdd = 5;
                                if (scoreToAdd > 50) scoreToAdd = 50;
                                TambahSkor(&skor[0], scoreToAdd);

                                if (AllBlocksDestroyed(blocks))
                                {
                                    if (currentLevel < 3)
                                    {
                                        currentLevel++;
                                        SetLevel(blocks, currentLevel);
                                        gameState = GAME_START;
                                    }
                                    else
                                    {
                                        gameState = GAME_WIN;
                                    }
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
                    currentLevel = 1;
                    SetLevel(blocks, currentLevel);
                    InitNyawa(nyawa, 3);
                    InitBola(bola);
                    InitSkor(skor);
                    InitStopwatch(stopwatch);
                    gameState = GAME_START;
                }
                break;

            case GAME_WIN:
                if (IsKeyPressed(KEY_R))
                {
                    currentLevel = 1;
                    SetLevel(blocks, currentLevel);
                    InitNyawa(nyawa, 3);
                    InitBola(bola);
                    InitSkor(skor);
                    InitStopwatch(stopwatch);
                    gameState = GAME_START;
                }
                break;
            }
        }

        BeginDrawing();
        ClearBackground(BLACK);

        DrawLine(835, 0, 835, SCREEN_HEIGHT, WHITE);
        DrawRectangle(0, 600, 835, 50, WHITE);
        DrawText("<- -> Bergerak       P - Pause       Esc - Exit", 150, 610, 20, BLACK);
        DrawPaddles(paddles);
        DrawBlocks(blocks);
        DrawBola(bola);
        DrawNyawa(nyawa);
        DrawSkor(skor);
        DrawStopwatch(stopwatch);

        switch (gameState)
        {
        case GAME_START:
            DrawText("PRESS SPACE TO START", 220, SCREEN_HEIGHT / 2, 30, WHITE);
            break;
        case GAME_OVER:
            DrawRectangle(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, WHITE);
            DrawText("GAME OVER", SCREEN_WIDTH / 2 - MeasureText("GAME OVER", 40) / 2, SCREEN_HEIGHT / 2 - 40, 40, RED);
            break;
        case GAME_WIN:
            DrawRectangle(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, WHITE);
            DrawText("YOU WIN!", SCREEN_WIDTH / 2 - MeasureText("YOU WIN!", 40) / 2, SCREEN_HEIGHT / 2 - 40, 40, GREEN);
            break;
        }

        EndDrawing();
    }

    CloseWindow();
    return 0;
}
