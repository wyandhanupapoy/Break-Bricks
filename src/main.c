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
    switch (level)
    {
    case 1:
        // Gradient statis dari biru sangat gelap (atas) ke hitam pekat (bawah)
        for (int y = 0; y < SCREEN_HEIGHT; y++)
        {
            float gradient = (float)y / SCREEN_HEIGHT; // Nilai gradient berdasarkan posisi Y
            Color color = (Color){
                (int)(10 + 5 * gradient),  // R (hampir tidak ada merah)
                (int)(20 + 10 * gradient), // G (sedikit biru kehijauan)
                (int)(30 + 15 * gradient), // B (biru sangat gelap)
                255                        // Alpha
            };
            DrawLine(0, y, SCREEN_WIDTH, y, color); // Garis horizontal untuk gradient
        }
        break;
    case 2:
        // Animasi gradient yang bergerak sangat lambat
        static float offsetlv2 = 0.0f; // Variabel untuk animasi
        offsetlv2 += 0.05f;            // Kecepatan animasi yang sangat lambat

        // Gradient dari hijau gelap ke hitam
        for (int y = 0; y < SCREEN_HEIGHT; y++)
        {
            float gradient = (float)y / SCREEN_HEIGHT + sinf(offsetlv2 * 0.01f) * 0.02f; // Perubahan sangat halus
            Color color = (Color){
                (int)(20 + 10 * gradient), // R (hampir tidak ada merah)
                (int)(50 + 20 * gradient), // G (hijau gelap)
                (int)(30 + 10 * gradient), // B (sedikit biru untuk variasi)
                255                        // Alpha
            };
            DrawLine(0, y, SCREEN_WIDTH, y, color); // Garis horizontal untuk gradient
        }

        // Garis-garis vertikal tipis yang bergerak perlahan
        static float lineOffset = 0.0f; // Variabel untuk animasi garis
        lineOffset += 0.03f;            // Kecepatan animasi garis yang sangat lambat

        for (int i = 0; i < SCREEN_WIDTH; i += 40) // Jarak antar garis
        {
            int x = (int)(i + sinf(lineOffset + i * 0.1f) * 5);         // Garis bergerak kiri kanan perlahan
            DrawLine(x, 0, x, SCREEN_HEIGHT, (Color){50, 100, 50, 60}); // Garis hijau transparan
        }
        break;
    case 3:
        // Animasi gradient yang bergerak sangat lambat
        static float offset = 0.0f; // Variabel untuk animasi
        offset += 0.1f;             // Kecepatan animasi yang sangat lambat

        for (int y = 0; y < SCREEN_HEIGHT; y++)
        {
            // Gradient dari merah tua ke hitam, dengan sedikit oranye gelap
            float gradient = (float)y / SCREEN_HEIGHT + sinf(offset * 0.005f + y * 0.005f) * 0.03f; // Perubahan lebih halus
            Color color = (Color){
                (int)(100 + 50 * gradient), // R (merah tua)
                (int)(30 * gradient),       // G (sedikit oranye/hijau)
                0,                          // B (tidak ada biru)
                255                         // Alpha
            };
            DrawLine(0, y, SCREEN_WIDTH, y, color); // Garis horizontal untuk gradient
        }

        // Efek "api" dengan partikel kecil, sedikit, dan bergerak lambat
        static float particleOffset = 0.0f; // Variabel untuk animasi partikel
        particleOffset += 0.05f;            // Kecepatan partikel yang sangat lambat

        for (int i = 0; i < 15; i++) // Jumlah partikel dikurangi lagi
        {
            int x = GetRandomValue(0, SCREEN_WIDTH);
            int y = GetRandomValue(SCREEN_HEIGHT / 2, SCREEN_HEIGHT);                                             // Partikel hanya di bagian bawah
            int size = GetRandomValue(1, 3);                                                                      // Ukuran partikel lebih kecil
            DrawCircle(x, y + sinf(particleOffset + i) * 2, size, (Color){255, GetRandomValue(50, 100), 0, 255}); // Partikel bergerak naik turun perlahan
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
    SetNyawaSize(32.0f);
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