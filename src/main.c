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
#include "block.h"
#include "BOLA.h"
#include "linkedlist_nyawa.h"
#include "skor.h"
#include "stopwatch.h"
#include "leaderboard.h"
#include "mainmenu.h"
#include "game_state.h"
#include "level.h"
#include "layout.h"
#include "background.h"
#include "sound.h"

#include <stdio.h>
#include <math.h>

// Timer untuk auto return ke menu
float gameEndTimer = 0.0f;
const float returnDelay = 3.0f;
LeaderboardEntry leaderboard[MAX_LEADERBOARD_ENTRIES];

// Fungsi untuk menggambar background unik setiap level
void DrawLevelBackground(int level)
{
    // [Isi fungsi DrawLevelBackground tetap sama...]
    // Tidak perlu diubah
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
    Block blocks[BLOCK_ROWS][BLOCK_COLS];
    Bola bola[BOLA_ROWS][BOLA_COLS];
    NodeNyawa *nyawaHead = NULL;
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

        if (IsKeyPressed(KEY_M))
            ToggleMusic();
        if (IsKeyPressed(KEY_W))
            IncreaseVolume();
        if (IsKeyPressed(KEY_S))
            DecreaseVolume();

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

            if (IsExitGame())
                break;

            if (IsStartGame())
            {
                int level = GetSelectedLevel();

                if (level > 0)
                {
                    InitPaddles(paddles);
                    InitBola(bola);
                    SetNyawaPosition(NYAWA_X, NYAWA_Y);
                    InitNyawaLinkedList(&nyawaHead, 3);
                    InitStopwatch(stopwatch);
                    InitSkor(skor);
                    SetLevel(blocks, level);
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
                UpdateBola(bola, paddles, blocks, &gameState, &skor[0], stopwatch);
                UpdateStopwatch(stopwatch);

                if (!bola[0][0].active)
                {
                    KurangiNyawaLinkedList(&nyawaHead);
                    if (!AnyLivesLeftLinkedList(nyawaHead))
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
                    break;
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
        ClearBackground((Color){30, 0, 60, 255});
        DrawLevelBackground(currentLevel);
        DrawLine(835, 0, 835, SCREEN_HEIGHT, WHITE);
        DrawControlInfo();

        DrawPaddles(paddles);
        DrawBlocks(blocks);
        DrawBola(bola);
        DrawNyawaLinkedList(nyawaHead);
        DrawSkor(skor, SCORE_X, SCORE_Y);
        DrawStopwatch(stopwatch);
        DrawMainMenuMini(gameState);

        if (lifeLost)
        {
            DrawText("LIFE LOST!", SCREEN_WIDTH / 2 - 230, SCREEN_HEIGHT / 2 - 50, 50, RED);
        }

        if (gameState == GAME_OVER || gameState == GAME_WIN)
        {
            DrawRectangle(250, 100, 400, 250, WHITE);
            DrawLeaderboard(leaderboard, 270, 120);
        }

        if (gameState == GAME_START)
        {
            DrawText("PRESS SPACE TO LAUNCH", 210, SCREEN_HEIGHT / 2, 30, WHITE);
        }
        else if (isPaused)
        {
            DrawPauseScreen();
        }

        EndDrawing();

        if (IsKeyPressed(KEY_F))
        {
            isFullscreen = !isFullscreen;
            ToggleFullscreen();
        }
    }

    SaveLeaderboard(leaderboard);
    UnloadNyawaTexture();
    UnloadSoundEffects();
    UnloadMedalTextures();
    UnloadImage(icon);
    FreeNyawaLinkedList(&nyawaHead);
    CloseWindow();

    return 0;
}