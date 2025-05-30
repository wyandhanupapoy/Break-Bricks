/* BREAK BRICKS    Game Breakout sederhana dengan beberapa level dan leaderboard.    Oleh: Kelompok C6 Proyek 2 POLBAN    - **Wyandhanu Maulidan Nugraha** (241511092)    - **Siti Soviyyah** (241511090)    - **Nezya Zulfa Fauziah** (241511085)    - **Muhammad Raihan Abubakar** (241511084)    - **Muhammad Brata Hadinata** (241511082)    - **Ahmad Habib Mutaqqin** (241511065)*/
#include <raylib.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h> // For sinf, cosf

// Game Modules
#include "paddle.h" // Uses PaddleList
#include "LinkedList-Block.h"
#include "BOLA.h" // Uses PaddleList
#include "nyawa.h"
#include "skor.h"
#include "stopwatch.h"
#include "leaderboard.h"
#include "mainmenu.h"
#include "game_state.h"
#include "LinkedList-level.h"
#include "layout.h"
#include "background.h"
#include "sound.h"
#include "powerup.h" // Uses PaddleList and PaddleNode

// Structure for level-specific background animation states
typedef struct
{
    float gradientOffset;
    float effectOffset1;
} LevelBackgroundState;

static LevelBackgroundState levelBgStates[3]; // For 3 levels

// Timer for auto return to menu
float gameEndTimer = 0.0f;
const float returnDelay = 3.0f; // 3 seconds

// Global game data structures
PowerUpList powerUpList;         // List of falling power-ups
LinkedList blockList;            // List of blocks
PaddleList paddleList;           // List of paddles (now dynamic)
BolaList bolaList;               // List of balls
Stopwatch *stopwatchList = NULL; // Pointer for stopwatch list
Skor skor[MAX_PLAYERS];          // Array of scores

// Function for drawing unique level backgrounds
void DrawDynamicLevelBackground(int level, LevelBackgroundState *bgState)
{
    if (level <= 0 || level > 3)
    {
        DrawRectangle(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, (Color){5, 5, 20, 255});
        return;
    }
    if (!bgState && (level == 2 || level == 3))
    {
        DrawRectangle(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, (Color){10, 10, 30, 255});
        return;
    }

    switch (level)
    {
    case 1:
        for (int y = 0; y < SCREEN_HEIGHT; y++)
        {
            float gradient = (float)y / SCREEN_HEIGHT;
            Color color = (Color){(int)(10 + 5 * gradient), (int)(20 + 10 * gradient), (int)(30 + 15 * gradient), 255};
            DrawLine(0, y, SCREEN_WIDTH, y, color);
        }
        break;
    case 2:
        for (int y = 0; y < SCREEN_HEIGHT; y++)
        {
            float gradient = (float)y / SCREEN_HEIGHT + sinf(bgState->gradientOffset * 0.01f) * 0.02f;
            Color color = (Color){(int)(20 + 10 * gradient), (int)(50 + 20 * gradient), (int)(30 + 10 * gradient), 255};
            DrawLine(0, y, SCREEN_WIDTH, y, color);
        }
        for (int i = 0; i < SCREEN_WIDTH; i += 40)
        {
            int xPos = (int)(i + sinf(bgState->effectOffset1 + i * 0.1f) * 5);
            DrawLine(xPos, 0, xPos, SCREEN_HEIGHT, (Color){50, 100, 50, 60});
        }
        break;
    case 3:
        for (int y = 0; y < SCREEN_HEIGHT; y++)
        {
            float gradient = (float)y / SCREEN_HEIGHT + sinf(bgState->gradientOffset * 0.005f + y * 0.005f) * 0.03f;
            Color color = (Color){(int)(100 + 50 * gradient), (int)(30 * gradient), 0, 255};
            DrawLine(0, y, SCREEN_WIDTH, y, color);
        }
        for (int i = 0; i < 15; i++)
        {
            int particleX = GetRandomValue(0, SCREEN_WIDTH);
            int particleBaseY = GetRandomValue(SCREEN_HEIGHT / 2, SCREEN_HEIGHT);
            int particleSize = GetRandomValue(1, 3);
            DrawCircle(particleX, particleBaseY + sinf(bgState->effectOffset1 + i * 0.5f) * 3, particleSize, (Color){255, GetRandomValue(50, 100), 0, 180});
        }
        break;
    }
}

void DrawActivePowerUpTimers(PaddleList *paddleList)
{
    if (!paddleList || !paddleList->head)
    {
        return; // Tidak ada paddle, tidak ada timer untuk digambar
    }

    PaddleNode *playerPaddle = paddleList->head; // Asumsi single player
    ActivePowerUp *effect = playerPaddle->activePowerUps;
    int currentY = POWERUP_TIMER_Y;
    char timerText[128];

    bool hasActiveTimers = false; // Flag untuk mengecek apakah ada timer yang perlu digambar

    while (effect != NULL)
    {
        const char *effectName = NULL;
        bool displayThisTimer = false;

        switch (effect->type)
        {
        case POWERUP_TRIPLE_BALL:
            // Efek Triple Ball instan, biasanya tidak perlu timer visual berkelanjutan
            // Jika ingin, bisa beri nama "Triple Ball Mode" atau semacamnya
            // Untuk saat ini, kita lewati saja agar tidak membingungkan
            break;
        case POWERUP_LONG_PADDLE:
            effectName = "Long Paddle";
            displayThisTimer = true;
            break;
            // Tambahkan case untuk power-up lain yang memiliki timer di sini
        }

        if (displayThisTimer && effectName && effect->remainingTime > 0)
        {
            if (!hasActiveTimers)
            { // Tampilkan judul "Active Effects:" hanya sekali
                DrawText("Active Effects:", POWERUP_TIMER_X, currentY, POWERUP_TIMER_FONT_SIZE, YELLOW);
                currentY += POWERUP_TIMER_SPACING;
                hasActiveTimers = true;
            }
            snprintf(timerText, sizeof(timerText), "- %s: %.1fs", effectName, effect->remainingTime);
            DrawText(timerText, POWERUP_TIMER_X, currentY, POWERUP_TIMER_FONT_SIZE, WHITE);
            currentY += POWERUP_TIMER_SPACING;
        }
        effect = effect->next;
    }
}

int main()
{
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "BREAK BRICKS");
    SetTargetFPS(60);

    Image icon = LoadImage("assets/images/icon.png");
    SetWindowIcon(icon);

    LoadLifeTexture();
    InitBackground();
    InitSoundSystem();
    InitLeaderboard();
    LoadLeaderboard(LEADERBOARD_FILE); // Load leaderboard from file

    PlayBackgroundMusic();

    GameState gameState = GAME_MENU;
    bool isPaused = false;
    bool isFullscreen = false;
    bool leaderboardUpdated = false;
    bool lifeLost = false;
    float lifeLostTimer = 0.0f;
    const float lifeLostDisplayTime = 1.5f;
    int currentLevel = 0;

    for (int i = 0; i < 3; i++)
    {
        levelBgStates[i].gradientOffset = 0.0f;
        levelBgStates[i].effectOffset1 = 0.0f;
    }

    InitPowerUp(&powerUpList); // Initialize power-up list once
    InitList(&blockList);      // Initialize block list once
    // paddleList and bolaList will be initialized when game starts
    // stopwatchList and skor initialized when game starts

    InitDynamicMainMenu();

    while (!WindowShouldClose())
    {
        UpdateBackground();
        SetLifeIconSize(8.0f);                     // Example size
        SetLivesDisplayPosition(NYAWA_X, NYAWA_Y); // From layout.h
        UpdateMusic();
        UpdateMainMenuMini(&gameState); // For in-game mini menu to return to main menu

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
            IncreaseVolume(); // Assuming W for volume up
        if (IsKeyPressed(KEY_S))
            DecreaseVolume(); // Assuming S for volume down

        if (gameState == GAME_MENU)
        {
            leaderboardUpdated = false;
            gameEndTimer = 0.0f;
            currentLevel = 0;
            isPaused = false;

            FreePowerUp(&powerUpList); // Clear any existing falling power-ups
            InitPowerUp(&powerUpList); // Re-initialize for a new game session

            FreePaddles(&paddleList); // Free paddles if any from previous game
            FreeBola(&bolaList);      // Free balls if any

            // LoadLeaderboard(LEADERBOARD_FILE); // Already loaded at Init, might refresh here if needed
            UpdateDynamicMainMenu();

            BeginDrawing();
            DrawDynamicMainMenu(); // This internally calls DrawBackground for starfield
            EndDrawing();

            if (IsExitGame())
                break;
            if (IsStartGame())
            {
                int level = GetSelectedLevel();
                if (level > 0)
                {
                    InitPaddles(&paddleList); // Initialize dynamic paddle list
                    InitBola(&bolaList);
                    InitLivesSystem(3);
                    if (stopwatchList)
                    { /* Free old if any, though unlikely here */
                    }
                    InitStopwatch(&stopwatchList, 1); // Assuming 1 stopwatch for the player
                    InitSkor(skor);                   // Assuming skor[0] is used

                    ClearList(&blockList); // Clear previous blocks before setting new level
                    SetLevel(&blockList, level);
                    currentLevel = level;

                    if (currentLevel > 0 && currentLevel <= 3)
                    {
                        levelBgStates[currentLevel - 1].gradientOffset = 0.0f;
                        levelBgStates[currentLevel - 1].effectOffset1 = 0.0f;
                    }
                    gameState = GAME_START;
                    SetStartGame(false); // Reset start game flag in mainmenu
                }
            }
            continue;
        }

        // Update background animation state for current level
        if ((gameState == GAME_PLAY || gameState == GAME_START) && !isPaused)
        {
            if (currentLevel > 0 && currentLevel <= 3)
            {
                LevelBackgroundState *currentState = &levelBgStates[currentLevel - 1];
                float frameTimeFactor = GetFrameTime() * 60.0f;
                switch (currentLevel)
                {
                case 2:
                    currentState->gradientOffset += 0.05f * frameTimeFactor;
                    currentState->effectOffset1 += 0.03f * frameTimeFactor;
                    break;
                case 3:
                    currentState->gradientOffset += 0.1f * frameTimeFactor;
                    currentState->effectOffset1 += 0.05f * frameTimeFactor;
                    break;
                }
            }
        }

        if (IsKeyPressed(KEY_P) && gameState == GAME_PLAY)
        {
            isPaused = !isPaused;
            if (isPaused)
                PauseMusic();
            else
                PauseMusic(); // Assuming backgroundMusic is the stream
        }

        if (!isPaused)
        {
            switch (gameState)
            {
            case GAME_START:
                ChangeMusic("assets/sounds/gameplay_music.mp3"); // Change to gameplay music
                UpdateMusic();                                   // Ensure it plays

                // Position ball on the first paddle (if paddles and ball exist)
                if (paddleList.head != NULL && bolaList.head != NULL)
                {
                    bolaList.head->position.x = paddleList.head->rect.x + paddleList.head->rect.width / 2;
                    bolaList.head->position.y = paddleList.head->rect.y - bolaList.head->radius - 1;
                }
                UpdatePaddles(&paddleList, GetFrameTime()); // Allow paddle movement
                if (IsKeyPressed(KEY_SPACE))
                {                     // Launch ball
                    lifeLost = false; // Reset life lost visual
                    if (bolaList.head != NULL)
                    { // Ensure ball exists before launching
                        // Initial speed might be set in InitBola or here upon launch
                        // If ball speed y is 0, set it to launch upwards
                        if (bolaList.head->speed.y == 0)
                            bolaList.head->speed.y = -6.0f;
                        if (bolaList.head->speed.x == 0 && paddleList.head != NULL)
                        { // Launch with some horizontal influence from paddle
                            float paddleSpeedInfluence = (GetMousePosition().x - (paddleList.head->rect.x + paddleList.head->rect.width / 2)) / (paddleList.head->rect.width / 2);
                            bolaList.head->speed.x = paddleSpeedInfluence * 5.0f;
                        }
                    }
                    gameState = GAME_PLAY;
                }
                break;

            case GAME_PLAY:
                UpdatePaddles(&paddleList, GetFrameTime());
                UpdateBola(&bolaList, &paddleList, &blockList, &gameState, &skor[0], stopwatchList, &powerUpList);
                UpdatePowerUp(&powerUpList, &paddleList, &bolaList, GetFrameTime());
                UpdateStopwatch(stopwatchList);

                if (SemuaBolaMati(&bolaList))
                {
                    DecreaseLife();
                    if (!HasLivesLeft())
                    {
                        gameState = GAME_OVER;
                    }
                    else
                    {
                        PlaySfx("lose_life");
                        ResetBola(&bolaList); // Reset all balls, one new ball appears
                        // Reset Powerups on paddle
                        if (paddleList.head)
                        {
                            ActivePowerUp *currEffect = paddleList.head->activePowerUps;
                            while (currEffect)
                            {
                                if (currEffect->type == POWERUP_LONG_PADDLE)
                                    paddleList.head->rect.width = PADDLE_WIDTH_DEFAULT; // Reset lebar
                                ActivePowerUp *temp = currEffect;
                                currEffect = currEffect->next;
                                free(temp);
                            }
                            paddleList.head->activePowerUps = NULL; // Kosongkan list efek aktif
                        }
                        FreePowerUp(&powerUpList); // Hapus item power-up yang jatuh
                        InitPowerUp(&powerUpList); // Inisialisasi ulang list item jatuh

                        gameState = GAME_START; // Go back to ball-on-paddle state
                        lifeLost = true;
                        lifeLostTimer = 0.0f;
                    }
                }
                break;

            case GAME_OVER:
                PlaySfx("game_over");
                ChangeMusic("assets/sounds/background_music.mp3"); // Back to menu music
                UpdateMusic();
                gameEndTimer += GetFrameTime();
                if (!leaderboardUpdated)
                {
                    AddEntryToLeaderboard(GetPlayerName(), skor[0].score, stopwatchList ? stopwatchList->time : 0.0f, currentLevel, "GAME OVER");
                    SaveLeaderboard(LEADERBOARD_FILE);
                    leaderboardUpdated = true;
                }
                if (gameEndTimer >= returnDelay || IsKeyPressed(KEY_R))
                { // R to return to menu
                    gameState = GAME_MENU;
                    gameEndTimer = 0.0f;
                }
                break;

            case GAME_WIN:
                PlaySfx("game_win");
                ChangeMusic("assets/sounds/background_music.mp3");
                UpdateMusic();
                gameEndTimer += GetFrameTime();
                if (!leaderboardUpdated)
                {
                    AddEntryToLeaderboard(GetPlayerName(), skor[0].score, stopwatchList ? stopwatchList->time : 0.0f, currentLevel, "WIN");
                    SaveLeaderboard(LEADERBOARD_FILE);
                    leaderboardUpdated = true;
                }
                if (gameEndTimer >= returnDelay || IsKeyPressed(KEY_R))
                {
                    gameState = GAME_MENU;
                    gameEndTimer = 0.0f;
                }
                break;
            default:
                break;
            }
        }

        BeginDrawing();
        ClearBackground((Color){30, 0, 60, 255}); // Default dark purple

        if (gameState == GAME_MENU)
        {
            DrawDynamicMainMenu();
        }
        else
        {
            if (currentLevel > 0 && currentLevel <= 3)
            {
                DrawDynamicLevelBackground(currentLevel, &levelBgStates[currentLevel - 1]);
            }
            else
            {
                DrawBackground(); // Starfield from background.c if no specific level background
            }

            if (gameState == GAME_PLAY || gameState == GAME_START || gameState == GAME_OVER || gameState == GAME_WIN)
            {
                DrawPaddles(&paddleList);
                DrawBlocks(&blockList);
                DrawPowerUp(&powerUpList); // Draw falling power-ups
                DrawBola(&bolaList);
                DrawLives();
                DrawSkor(skor, SCORE_X, SCORE_Y); // From layout.h for positions
                if (stopwatchList)
                    DrawStopwatch(stopwatchList); // Check if stopwatchList is initialized

                // Gambar Timer Power-up Aktif pada paddle
                if (gameState == GAME_PLAY || gameState == GAME_START)
                {
                    DrawActivePowerUpTimers(&paddleList);
                }

                DrawMainMenuMini(gameState); // Draw mini menu button
            }

            DrawLine(835, 0, 835, SCREEN_HEIGHT, WHITE); // UI Panel Separator
            DrawControlInfo();                           // Player controls info at bottom
        }

        if (lifeLost && (gameState == GAME_START || gameState == GAME_PLAY))
        { // Show only during gameplay/start after life lost
            DrawText("LIFE LOST!", SCREEN_WIDTH / 2 - MeasureText("LIFE LOST!", 50) / 2, SCREEN_HEIGHT / 2 - 50, 50, RED);
        }

        // Game state specific screens on top
        if (gameState == GAME_START && !lifeLost)
        { // Don't show if "LIFE LOST!" is showing
            DrawText("PRESS SPACE TO LAUNCH", SCREEN_WIDTH / 2 - MeasureText("PRESS SPACE TO LAUNCH", 30) / 2, SCREEN_HEIGHT / 2, 30, WHITE);
        }
        else if (gameState == GAME_OVER)
        {
            DrawGameOverScreen();                                // From layout.c
            DrawLeaderboardInfo(SCREEN_WIDTH / 2 - 150, 400, 3); // Show a few entries
        }
        else if (gameState == GAME_WIN)
        {
            DrawWinScreen(); // From layout.c
            DrawLeaderboardInfo(SCREEN_WIDTH / 2 - 150, 400, 3);
        }
        else if (isPaused)
        {
            DrawPauseScreen(); // From layout.c
        }
        EndDrawing();

        if (IsKeyPressed(KEY_F))
        {
            isFullscreen = !isFullscreen;
            ToggleFullscreen();
        }
    }

    // Cleanup
    FreePaddles(&paddleList);
    FreeBola(&bolaList);
    ClearList(&blockList);     // Free blocks
    FreePowerUp(&powerUpList); // Free any remaining falling power-ups
    if (stopwatchList)
    { // Assuming stopwatchList is a single allocated struct or head of a list needing freeing.
        Stopwatch *tempSw = stopwatchList;
        while (tempSw)
        {
            Stopwatch *nextSw = tempSw->next;
            free(tempSw);
            tempSw = nextSw;
        }
        stopwatchList = NULL;
    }

    SaveLeaderboard(LEADERBOARD_FILE);
    FreeLeaderboard();
    FreeDynamicMainMenu();
    UnloadLifeTexture();
    UnloadSoundSystem();
    UnloadMedalTextures(); // From leaderboard.c
    UnloadImage(icon);
    CleanupBackground(); // Free background stars
    CloseWindow();

    return 0;
}