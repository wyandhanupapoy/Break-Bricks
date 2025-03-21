#include <raylib.h>

// Game Modules
#include "paddle.h"
#include "block.h"
#include "BOLA.h"
#include "nyawa.h"
#include "skor.h"
#include "stopwatch.h"
#include "leaderboard.h"
#include "mainmenu.h"
#include "game_state.h"
#include "level.h"
#include "layout.h" // Untuk SCORE_X, SCORE_Y
#include "background.h"

#include "sound.h"

#include <stdio.h>

// Timer buat auto return ke menu
float gameEndTimer = 0.0f;
const float returnDelay = 3.0f; // 3 detik balik ke menu
LeaderboardEntry leaderboard[MAX_LEADERBOARD_ENTRIES];


int main()
{
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "BREAK BRICKS");
    SetTargetFPS(60);
    LoadNyawaTexture();
    InitBackground();
    InitSoundEffects();
    PlayBackgroundMusic();
// Leaderboard
LeaderboardEntry leaderboard[MAX_LEADERBOARD_ENTRIES];
LoadLeaderboard(leaderboard);

    // Game State & Control
    GameState gameState = GAME_MENU;
    bool isPaused = false;
    bool isFullscreen = false;
    bool leaderboardUpdated = false;

    // Level
    int currentLevel = 0;

    // Game Data
    Paddle paddles[PADDLE_ROWS][PADDLE_COLS];
    Block blocks[BLOCK_ROWS][BLOCK_COLS];
    Bola bola[BOLA_ROWS][BOLA_COLS];
    Nyawa nyawa[NYAWA_BARIS][NYAWA_KOLOM];
    Stopwatch stopwatch[STOPWATCH_ROWS][STOPWATCH_COLS];
    Skor skor[MAX_PLAYERS];

    // Initialize
    InitLeaderboard(leaderboard);
    InitMainMenu();

    while (!WindowShouldClose())
    {
        UpdateBackground();
        SetNyawaSize(8);
        SetNyawaPosition(NYAWA_X, NYAWA_Y);
        UpdateMusic();
        UpdateMainMenuMini(&gameState);

        if (IsKeyPressed(KEY_M))
            ToggleMusic();
        if (IsKeyPressed(KEY_W))
            IncreaseVolume();
        if (IsKeyPressed(KEY_S))
            DecreaseVolume();

        // === MENU STATE ===
        if (gameState == GAME_MENU)
        {
            leaderboardUpdated = false; // Reset leaderboard
            gameEndTimer = 0.0f;        // Reset end timer
            currentLevel = 0;           // Reset level pilihannya
            isPaused = false;           // Reset pause

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
                        InitNyawa(nyawa, 3);
                        InitStopwatch(stopwatch);
                        InitSkor(skor);
                        SetLevel(blocks, level);
                        currentLevel = level; // Store the current level
                
                        gameState = GAME_START;
                        SetStartGame(false);
                    }
                }

            continue;
        }

        // === PAUSE CONTROL ===
        if (IsKeyPressed(KEY_P) && gameState == GAME_PLAY)
        {
            PauseMusic();
            isPaused = !isPaused;
        }

        // === GAME LOGIC ===
        if (!isPaused)
        {
            switch (gameState)
            {

            case GAME_START:
                ChangeMusic("assets/sounds/gameplay_music.mp3");
                UpdateMusic();
                // Bola nempel paddle
                bola[0][0].position.x = paddles[0][0].rect.x + PADDLE_WIDTH / 2;
                bola[0][0].position.y = paddles[0][0].rect.y - bola[0][0].radius - 1;

                UpdatePaddles(paddles); // Bisa gerakin paddle sebelum space

                if (IsKeyPressed(KEY_SPACE))
                {
                    gameState = GAME_PLAY;
                }
                break;

            case GAME_PLAY:
                UpdatePaddles(paddles);
                UpdateBola(bola, paddles, blocks, &gameState, &skor[0], stopwatch);
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
                    }
                }
                break;

            case GAME_OVER:
                PlayGameOver();
                ChangeMusic("assets/sounds/background_music.mp3");
                UpdateMusic();
                gameEndTimer += GetFrameTime();
                
                if (gameEndTimer >= returnDelay || IsKeyPressed(KEY_R))
                {
                    gameState = GAME_MENU;
                    gameEndTimer = 0.0f;
                }
                break;
            case GAME_WIN:
                ChangeMusic("assets/sounds/background_music.mp3");
                UpdateMusic();
                PlayGameWin();
                gameEndTimer += GetFrameTime();

                if (gameEndTimer >= returnDelay || IsKeyPressed(KEY_R))
                {
                    gameState = GAME_MENU;
                    gameEndTimer = 0.0f;
                }

                if (gameState == GAME_WIN && !leaderboardUpdated)
                {
                    AddToLeaderboard(leaderboard, GetPlayerName(), skor[0].score, stopwatch[0][0].time, currentLevel);
            leaderboardUpdated = true;
            SaveLeaderboard(leaderboard);
                }

                break;

            default:
                break;
            }
        }

        // === DRAWING ===
        BeginDrawing();
        ClearBackground((Color){30, 0, 60, 255});

        // Layout garis & panel bawah
        DrawLine(835, 0, 835, SCREEN_HEIGHT, WHITE);
        DrawRectangle(0, 600, 835, 50, WHITE);
        DrawText("<- -> Move   |   P - Pause   |   F - Fullscreen   |   Esc - Exit  |  M - Mute Music", 15, 610, 20, BLACK);

        // Draw game layout
        DrawPaddles(paddles);
        DrawBlocks(blocks);
        DrawBola(bola);
        DrawNyawa(nyawa);
        DrawSkor(skor, SCORE_X, SCORE_Y);
        DrawStopwatch(stopwatch);
        DrawMainMenuMini(gameState);

        // === GAME STATE UI ===
        switch (gameState)
        {

        case GAME_START:
            DrawText("PRESS SPACE TO LAUNCH", 210, SCREEN_HEIGHT / 2, 30, WHITE);
            break;

        case GAME_OVER:
            DrawRectangle(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, WHITE);
            DrawText("GAME OVER", 370, 300, 40, RED);
            DrawText("Returning to menu...", 400, 350, 20, DARKGRAY);
            break;

        case GAME_WIN:
            DrawRectangle(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, WHITE);
            DrawText("YOU WIN!", 370, 300, 40, GREEN);
            DrawText("Returning to menu...", 370, 350, 20, DARKGRAY);
            break;

        default:
            break;
        }

        // === PAUSE UI ===
        if (isPaused && gameState == GAME_PLAY)
        {
            DrawRectangle(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, Fade(WHITE, 0.7f));
            DrawText("GAME PAUSED", 370, 300, 40, BLACK);
            DrawText("PRESS P TO CONTINUE", 400, 350, 20, BLACK);
            DrawText("PRESS L TO VIEW LEADERBOARD", 345, 470, 20, BLACK);
            stopwatch[0][0].running = false;

            if (IsKeyDown(KEY_L))
            {
                DrawLeaderboard(leaderboard);
            }
        }
        else
        {
            stopwatch[0][0].running = true;
        }

        EndDrawing();

        // === FULLSCREEN TOGGLE ===
        if (IsKeyPressed(KEY_F))
        {
            isFullscreen = !isFullscreen;
            ToggleFullscreen();
        }
    }

    SaveLeaderboard(leaderboard);
    UnloadNyawaTexture();
    UnloadSoundEffects();
    CloseWindow();
    return 0;
}
