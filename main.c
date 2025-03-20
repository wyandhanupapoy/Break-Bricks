#include "paddle.h"
#include "block.h"
#include "BOLA.h"
#include "nyawa.h"
#include "skor.h"
#include "stopwatch.h"
#include "leaderboard.h"
#include "mainmenu.h"
#include "game_state.h"
#include "main.h"

#include <stdio.h>
#include <raylib.h>

#define SCREEN_WIDTH 1000
#define SCREEN_HEIGHT 650

int main()
{
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "F - Fullscreen                                                        Break Bricks");
    SetTargetFPS(60);
    InitMainMenu();

    // Variabel fullscreen
    bool isFullscreen = false;

    // Inisialisasi game state
    GameState gameState = GAME_MENU;
    bool isPaused = false;

    // Variabel permainan
    Paddle paddles[PADDLE_ROWS][PADDLE_COLS];
    Block blocks[BLOCK_ROWS][BLOCK_COLS];
    Bola bola[BOLA_ROWS][BOLA_COLS];
    Nyawa nyawa[NYAWA_BARIS][NYAWA_KOLOM];
    Stopwatch stopwatch[STOPWATCH_ROWS][STOPWATCH_COLS];
    Skor skor[MAX_PLAYERS];
    LeaderboardEntry leaderboard[MAX_PLAYERS];

    // Loop utama
    while (!WindowShouldClose())
    {
        // **1. Tampilkan Menu Utama**
        if (gameState == GAME_MENU)
        {
            UpdateMainMenu();

            BeginDrawing();
            ClearBackground(BLACK);
            DrawMainMenu();
            EndDrawing();

            // Jika exit ditekan, keluar dari loop utama
            if (IsExitGame())
            {
                break;
            }

            // Jika menu level dipilih, mulai inisialisasi game
            if (GetMenuState() == MENU_LEVEL)
            {
                int level = GetSelectedLevel();
                if (level > 0)
                {
                    // **2. Inisialisasi game baru**
                    InitPaddles(paddles);
                    InitBlocks(blocks);
                    InitBola(bola);
                    InitNyawa(nyawa, 3);
                    InitStopwatch(stopwatch);
                    InitSkor(skor);
                    InitLeaderboard(leaderboard);
                    SetNyawaPosition(nyawa, 870, 10);

                    gameState = GAME_START; // Masuk ke tahap awal permainan
                }
            }
            continue; // Skip ke loop berikutnya, agar tidak menggambar game
        }

        // **3. Update input game**
        if (IsKeyPressed(KEY_P) && gameState == GAME_PLAY)
        {
            isPaused = !isPaused;
        }

        // **4. Jalankan logika permainan**
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
                                blocks[blockRow][blockCol].active = false;
                                TambahSkor(&skor[0], 50);
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

        // **5. Gambar permainan**
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

        // **Tampilkan status game**
        switch (gameState)
        {
        case GAME_START:
            DrawText("PRESS SPACE TO START", 220, SCREEN_HEIGHT / 2, 30, WHITE);
            break;
        case GAME_OVER:
            DrawRectangle(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, WHITE);
            DrawText("GAME OVER", 450, 300, 40, RED);
            DrawText("PRESS R TO RESTART", 420, 350, 20, DARKGRAY);
            DrawLeaderboard(leaderboard);
            break;
        case GAME_WIN:
            DrawRectangle(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, WHITE);
            DrawText("YOU WIN!", 450, 300, 40, GREEN);
            DrawText("PRESS R TO RESTART", 420, 350, 20, DARKGRAY);
            AddToLeaderboard(leaderboard, "Player", skor[0].score, stopwatch[0][0].time);
            DrawLeaderboard(leaderboard);
            break;
        }

        // **Tampilkan layar pause**
        if (isPaused)
        {
            DrawRectangle(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, Fade(WHITE, 0.7f));
            DrawText("GAME PAUSED", 450, 300, 40, BLACK);
            DrawText("PRESS P TO CONTINUE", 420, 350, 20, BLACK);
            stopwatch[0][0].running = false;
        }
        else
        {
            stopwatch[0][0].running = true;
        }

        EndDrawing();

        // **6. Toggle fullscreen**
        if (IsKeyPressed(KEY_F))
        {
            isFullscreen = !isFullscreen;
            ToggleFullscreen();
        }
    }

    CloseWindow();
    return 0;
}
