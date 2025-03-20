#include "paddle.h"
#include "block.h"
#include "BOLA.h"
#include "nyawa.h"
#include "skor.h"
#include "stopwatch.h"
#include "leaderboard.h"
#include "soundeffect.h"

#include <stdio.h>
#include <raylib.h>

#define SCREEN_WIDTH 1000
#define SCREEN_HEIGHT 650

int main()
{
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "F - Fullscreen                                                        Break Bricks");
    InitAudioDevice();  // 🔹 Inisialisasi audio untuk efek suara
    LoadSoundEffects(); // 🔹 Load semua efek suara sebelum game mulai
    SetTargetFPS(60);

    // Variabel untuk menyimpan status fullscreen
    bool isFullscreen = false;

    Paddle paddles[PADDLE_ROWS][PADDLE_COLS];
    InitPaddles(paddles);

    Block blocks[BLOCK_ROWS][BLOCK_COLS];
    InitBlocks(blocks);

    Bola bola[BOLA_ROWS][BOLA_COLS];
    InitBola(bola);

    Nyawa nyawa[NYAWA_BARIS][NYAWA_KOLOM];
    InitNyawa(nyawa, 3); // Start with 3 lives
    SetNyawaPosition(nyawa, 870, 10);

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
        if (IsKeyPressed(KEY_F))
        {
            isFullscreen = !isFullscreen;
            ToggleFullscreen();
        }

        if (IsKeyPressed(KEY_P) && gameState == GAME_PLAY)
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
                    PlaySoundEffect(0, 0); // 🔹 Menu Click Sound
                    gameState = GAME_PLAY;
                }
                break;

            case GAME_PLAY:
                UpdatePaddles(paddles);
                UpdateBola(bola, paddles, blocks, &gameState, &skor[0], stopwatch);
                UpdateStopwatch(stopwatch);

                // 🔹 Deteksi bola mengenai paddle/dinding
                for (int ballRow = 0; ballRow < BOLA_ROWS; ballRow++)
                {
                    if (CheckBallPaddleCollision(bola[ballRow][0].position, bola[ballRow][0].radius, paddles))
                    {
                        PlaySoundEffect(0, 2); // 🔹 Ball Bounce Sound
                    }

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

                                PlaySoundEffect(1, 0); // 🔹 Block Break Sound

                                int timeElapsed = (int)stopwatch[0][0].time;
                                int scoreToAdd = 50 - timeElapsed;
                                if (scoreToAdd < 5)
                                    scoreToAdd = 5;
                                if (scoreToAdd > 50)
                                    scoreToAdd = 50;
                                TambahSkor(&skor[0], scoreToAdd);

                                bola[ballRow][0].speed.y *= -1;

                                if (AllBlocksDestroyed(blocks))
                                {
                                    PlaySoundEffect(1, 1); // 🔹 Win Sound
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
                            PlaySoundEffect(1, 2); // 🔹 Lose Sound
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
                    InitSkor(skor);
                    InitStopwatch(stopwatch);
                    SetNyawaPosition(nyawa, 870, 10);
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
                    InitStopwatch(stopwatch);
                    SetNyawaPosition(nyawa, 870, 10);
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
            if (AnyLivesLeft(nyawa) && nyawa[0][0].aktif == false)
            {
                DrawText("NYAWA BERKURANG!!!", 290, 380, 25, RED);
            }
            DrawText("PRESS SPACE TO START", 220, SCREEN_HEIGHT / 2, 30, WHITE);
            break;
        case GAME_OVER:
            DrawRectangle(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, WHITE);
            DrawText("GAME OVER", SCREEN_WIDTH / 2 - MeasureText("GAME OVER", 40) / 2, SCREEN_HEIGHT / 2 - 40, 40, RED);
            DrawText("PRESS R TO RESTART", SCREEN_WIDTH / 2 - MeasureText("PRESS R TO RESTART", 20) / 2, SCREEN_HEIGHT / 2 + 20, 20, DARKGRAY);
            break;
        case GAME_WIN:
            DrawRectangle(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, WHITE);
            DrawText("YOU WIN!", SCREEN_WIDTH / 2 - MeasureText("YOU WIN!", 40) / 2, SCREEN_HEIGHT / 2 - 40, 40, GREEN);
            DrawText("PRESS R TO RESTART", SCREEN_WIDTH / 2 - MeasureText("PRESS R TO RESTART", 20) / 2, SCREEN_HEIGHT / 2 + 20, 20, DARKGRAY);
            break;
        }

        if (isPaused)
        {
            DrawRectangle(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, Fade(WHITE, 0.7f));
            DrawText("GAME PAUSED", SCREEN_WIDTH / 2 - MeasureText("GAME PAUSED", 40) / 2, SCREEN_HEIGHT / 2 - 40, 40, BLACK);
        }

        EndDrawing();
    }

    UnloadSoundEffects(); // 🔹 Bebaskan memori suara sebelum keluar
    CloseWindow();
    return 0;
}