/*
    BREAK BRICKS
    Game Breakout sederhana dengan beberapa level dan leaderboard.

    Oleh: Kelompok C6 Proyek 2 POLBAN
    - **Wyandhanu Maulidan Nugraha** (241511092)
    - **Siti Soviyyah** (241511090)
    - **Nezya Zulfa Fauziah** (241511085)
    - **Muhammad Raihan Abubakar** (241511084)
    - **Muhammad Brata Hadinata** (241511082)
    - **Ahmad Habib Mutaqqin** (241511065)
*/
#include <raylib.h>

// Game Modules
#include "paddle.h"
#include "LinkedList-Block.h"
#include "BOLA.h"
#include "nyawa.h"
#include "skor.h"
#include "stopwatch.h"
#include "leaderboard.h"
#include "mainmenu.h"
#include "game_state.h"
#include "LinkedList-Level.h"
#include "layout.h"
#include "background.h"
#include "sound.h"

#include <stdio.h>
#include <math.h>

LinkedList blockList;

// Timer untuk auto return ke menu
float gameEndTimer = 0.0f;
const float returnDelay = 3.0f; // 3 detik kembali ke menu
LeaderboardEntry leaderboard[MAX_LEADERBOARD_ENTRIES];

// Fungsi untuk menggambar background unik setiap level
void DrawLevelBackground(int level)
{
    switch (level)
    {
    case 1:
        for (int y = 0; y < SCREEN_HEIGHT; y++)
        {
            float gradient = (float)y / SCREEN_HEIGHT;
            Color color = (Color){
                (int)(10 + 5 * gradient),
                (int)(20 + 10 * gradient),
                (int)(30 + 15 * gradient),
                255
            };
            DrawLine(0, y, SCREEN_WIDTH, y, color);
        }
        break;
    case 2:
        static float offsetlv2 = 0.0f;
        offsetlv2 += 0.05f;

        for (int y = 0; y < SCREEN_HEIGHT; y++)
        {
            float gradient = (float)y / SCREEN_HEIGHT + sinf(offsetlv2 * 0.01f) * 0.02f;
            Color color = (Color){
                (int)(20 + 10 * gradient),
                (int)(50 + 20 * gradient),
                (int)(30 + 10 * gradient),
                255
            };
            DrawLine(0, y, SCREEN_WIDTH, y, color);
        }

        static float lineOffset = 0.0f;
        lineOffset += 0.03f;

        for (int i = 0; i < SCREEN_WIDTH; i += 40)
        {
            int x = (int)(i + sinf(lineOffset + i * 0.1f) * 5);
            DrawLine(x, 0, x, SCREEN_HEIGHT, (Color){50, 100, 50, 60});
        }
        break;
    case 3:
        static float offset = 0.0f;
        offset += 0.1f;

        for (int y = 0; y < SCREEN_HEIGHT; y++)
        {
            float gradient = (float)y / SCREEN_HEIGHT + sinf(offset * 0.005f + y * 0.005f) * 0.03f;
            Color color = (Color){
                (int)(100 + 50 * gradient),
                (int)(30 * gradient),
                0,
                255
            };
            DrawLine(0, y, SCREEN_WIDTH, y, color);
        }

        static float particleOffset = 0.0f;
        particleOffset += 0.05f;

        for (int i = 0; i < 15; i++)
        {
            int x = GetRandomValue(0, SCREEN_WIDTH);
            int y = GetRandomValue(SCREEN_HEIGHT / 2, SCREEN_HEIGHT);
            int size = GetRandomValue(1, 3);
            DrawCircle(x, y + sinf(particleOffset + i) * 2, size, (Color){255, GetRandomValue(50, 100), 0, 255});
        }
        break;
    }
}

int main()
{
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "BREAK BRICKS");
    SetTargetFPS(60);

    Image icon = LoadImage("assets/images/icon.png");
    SetWindowIcon(icon);

    LoadNyawaTexture();
    InitBackground();
    InitSoundEffects();
    PlayBackgroundMusic();

    LoadLeaderboard(leaderboard);

    GameState gameState = GAME_MENU;
    bool isPaused = false;
    bool isFullscreen = false;
    bool leaderboardUpdated = false;

    bool lifeLost = false;
    float lifeLostTimer = 0.0f;
    const float lifeLostDisplayTime = 1.5f;

    int currentLevel = 0;

    Paddle paddles[PADDLE_ROWS][PADDLE_COLS];
    Bola bola[BOLA_ROWS][BOLA_COLS];
    Nyawa nyawa[NYAWA_BARIS][NYAWA_KOLOM];
    Stopwatch stopwatch[STOPWATCH_ROWS][STOPWATCH_COLS];
    Skor skor[MAX_PLAYERS];

    InitMainMenu();

    while (!WindowShouldClose())
    {
        UpdateBackground();
        SetNyawaSize(8);
        SetNyawaPosition(NYAWA_X, NYAWA_Y);
        UpdateMusic();
        UpdateMainMenuMini(&gameState);

        if (lifeLost)
        {
            lifeLostTimer += GetFrameTime();
            if (lifeLostTimer >= lifeLostDisplayTime)
            {
                lifeLost = false;
            }
        }

        if (IsKeyPressed(KEY_M)) ToggleMusic();
        if (IsKeyPressed(KEY_W)) IncreaseVolume();
        if (IsKeyPressed(KEY_S)) DecreaseVolume();

        if (gameState == GAME_MENU)
        {
            leaderboardUpdated = false;
            gameEndTimer = 0.0f;
            currentLevel = 0;
            isPaused = false;

            LoadLeaderboard(leaderboard);

            UpdateMainMenu();

            BeginDrawing();
            DrawMainMenu();
            EndDrawing();

            if (IsExitGame()) break;

            if (IsStartGame())
            {
                int level = GetSelectedLevel();
                if (level > 0)
                {
                    InitPaddles(paddles);
                    InitBola(bola);
                    SetNyawaPosition(NYAWA_X, NYAWA_Y);
                    InitNyawa(nyawa, 3);
                    InitStopwatch(stopwatch);
                    InitSkor(skor);
                    SetLevel(&blockList, level);  // ✅ DIPERBAIKI UNTUK LINKED LIST
                    currentLevel = level;

                    gameState = GAME_START;
                    SetStartGame(false);
                }
            }
            continue;
        }

        if (IsKeyPressed(KEY_P) && gameState == GAME_PLAY)
        {
            PauseMusic();
            isPaused = !isPaused;
        }

        if (!isPaused)
        {
            switch (gameState)
            {
            case GAME_START:
                ChangeMusic("assets/sounds/gameplay_music.mp3");
                UpdateMusic();
                bola[0][0].position.x = paddles[0][0].rect.x + PADDLE_WIDTH / 2;
                bola[0][0].position.y = paddles[0][0].rect.y - bola[0][0].radius - 1;

                UpdatePaddles(paddles);

                if (IsKeyPressed(KEY_SPACE))
                {
                    lifeLost = false;
                    gameState = GAME_PLAY;
                }
                break;

            case GAME_PLAY:
                UpdatePaddles(paddles);
                UpdateBola(bola, paddles, &blockList, &gameState, &skor[0], stopwatch);
                UpdateStopwatch(stopwatch);

                if (!bola[0][0].active)
                {
                    KurangiNyawa(nyawa);
                    if (!AnyLivesLeft(nyawa))
                    {
                        gameState = GAME_OVER;
                    }
                    else
                    {
                        PlayLoseLife();
                        ResetBola(bola);
                        gameState = GAME_START;
                        lifeLost = true;
                        lifeLostTimer = 0.0f;
                    }
                }
                break;

            case GAME_OVER:
                PlayGameOver();
                ChangeMusic("assets/sounds/background_music.mp3");
                UpdateMusic();
                gameEndTimer += GetFrameTime();

                if (!leaderboardUpdated)
                {
                    AddToLeaderboard(leaderboard, GetPlayerName(), skor[0].score, stopwatch[0][0].time, currentLevel, "GAME OVER");
                    SaveLeaderboard(leaderboard);
                    LoadLeaderboard(leaderboard);
                    leaderboardUpdated = true;
                }

                DrawGameOverScreen();
                DrawLeaderboard(leaderboard, 50, 400);

                if (gameEndTimer >= returnDelay || IsKeyPressed(KEY_R))
                {
                    gameState = GAME_MENU;
                    gameEndTimer = 0.0f;
                }
                break;

            case GAME_WIN:
                PlayGameWin();
                ChangeMusic("assets/sounds/background_music.mp3");
                UpdateMusic();
                gameEndTimer += GetFrameTime();

                if (!leaderboardUpdated)
                {
                    AddToLeaderboard(leaderboard, GetPlayerName(), skor[0].score, stopwatch[0][0].time, currentLevel, "WIN");
                    SaveLeaderboard(leaderboard);
                    LoadLeaderboard(leaderboard);
                    leaderboardUpdated = true;
                }

                DrawWinScreen();
                DrawLeaderboard(leaderboard, 50, 400);

                if (gameEndTimer >= returnDelay || IsKeyPressed(KEY_R))
                {
                    gameState = GAME_MENU;
                    gameEndTimer = 0.0f;
                }
                break;
            }
        }

        BeginDrawing();
        ClearBackground(BLACK);
        DrawLevelBackground(currentLevel);
        DrawBlocks(&blockList);
        DrawPaddles(paddles);
        DrawBola(bola);
        DrawNyawa(nyawa);
        DrawStopwatch(stopwatch);
        DrawSkor(skor, SCORE_X, SCORE_Y);

        if (lifeLost)
        {
            DrawText("LIFE LOST!", SCREEN_WIDTH / 2 - 100, SCREEN_HEIGHT / 2, 30, RED);
        }

        if (isPaused)
        {
            DrawText("PAUSED", SCREEN_WIDTH / 2 - 70, SCREEN_HEIGHT / 2, 40, YELLOW);
        }

        EndDrawing();
    }

    CloseWindow();
    return 0;
}