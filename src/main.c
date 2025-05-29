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
#include "LinkedList-level.h"
#include "layout.h"
#include "background.h"
#include "sound.h"
#include "powerup.h"

#include <stdio.h>
#include <math.h>

typedef struct
{
    float gradientOffset; // Untuk animasi gradien
    float effectOffset1;  // Untuk animasi efek khusus (garis di L2, partikel di L3)
    // Tambahkan float lain jika ada lebih banyak parameter animasi per level
} LevelBackgroundState;

// Array untuk menyimpan status masing-masing level (misalnya, untuk 3 level)
static LevelBackgroundState levelBgStates[3]; // Indeks 0 untuk Level 1, 1 untuk Level 2, dst.

// Timer untuk auto return ke menu
float gameEndTimer = 0.0f;
const float returnDelay = 3.0f; // 3 detik kembali ke menu
PowerUpList powerUpList;
LinkedList blockList;

// Fungsi untuk menggambar background unik setiap level
void DrawDynamicLevelBackground(int level, LevelBackgroundState *bgState)
{
    // Jika level tidak valid atau bgState tidak ada untuk level animasi, gambar default
    if (level <= 0 || level > 3)
    { // Asumsi hanya ada 3 level dengan background khusus
        // Gambar latar belakang default jika level tidak diketahui atau menu
        // Atau biarkan ClearBackground() yang menangani jika ini transparan
        DrawRectangle(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, (Color){5, 5, 20, 255}); // Biru sangat gelap
        return;
    }
    if (!bgState && (level == 2 || level == 3))
    {                                                                               // Level 2 & 3 memerlukan bgState
        DrawRectangle(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, (Color){10, 10, 30, 255}); // Biru gelap sebagai fallback
        return;
    }

    switch (level)
    {
    case 1:
        // Level 1: Gradient statis (tidak memerlukan bgState untuk animasi)
        for (int y = 0; y < SCREEN_HEIGHT; y++)
        {
            float gradient = (float)y / SCREEN_HEIGHT;
            Color color = (Color){
                (int)(10 + 5 * gradient),
                (int)(20 + 10 * gradient),
                (int)(30 + 15 * gradient),
                255};
            DrawLine(0, y, SCREEN_WIDTH, y, color);
        }
        break;
    case 2:
        // Level 2: Animasi gradient dan garis bergerak
        // Menggunakan bgState->gradientOffset dan bgState->effectOffset1
        for (int y = 0; y < SCREEN_HEIGHT; y++)
        {
            float gradient = (float)y / SCREEN_HEIGHT + sinf(bgState->gradientOffset * 0.01f) * 0.02f;
            Color color = (Color){
                (int)(20 + 10 * gradient),
                (int)(50 + 20 * gradient),
                (int)(30 + 10 * gradient),
                255};
            DrawLine(0, y, SCREEN_WIDTH, y, color);
        }

        for (int i = 0; i < SCREEN_WIDTH; i += 40)
        {
            int x = (int)(i + sinf(bgState->effectOffset1 + i * 0.1f) * 5);
            DrawLine(x, 0, x, SCREEN_HEIGHT, (Color){50, 100, 50, 60});
        }
        break;
    case 3:
        // Level 3: Animasi gradient dan efek "api"
        // Menggunakan bgState->gradientOffset dan bgState->effectOffset1
        for (int y = 0; y < SCREEN_HEIGHT; y++)
        {
            float gradient = (float)y / SCREEN_HEIGHT + sinf(bgState->gradientOffset * 0.005f + y * 0.005f) * 0.03f;
            Color color = (Color){
                (int)(100 + 50 * gradient),
                (int)(30 * gradient),
                0,
                255};
            DrawLine(0, y, SCREEN_WIDTH, y, color);
        }

        // Partikel api (posisi Y berosilasi dengan effectOffset1)
        // Perhatikan: GetRandomValue() di dalam loop ini akan membuat partikel muncul di posisi X dan Y dasar yang acak setiap frame.
        // Jika Anda ingin partikel yang lebih persisten, sistem partikel yang lebih kompleks diperlukan.
        for (int i = 0; i < 15; i++)
        {
            int particleX = GetRandomValue(0, SCREEN_WIDTH);
            int particleBaseY = GetRandomValue(SCREEN_HEIGHT / 2, SCREEN_HEIGHT);
            int particleSize = GetRandomValue(1, 3);
            // Menggunakan bgState->effectOffset1 untuk menggeser fase animasi partikel
            DrawCircle(particleX, particleBaseY + sinf(bgState->effectOffset1 + i * 0.5f) * 3, particleSize, (Color){255, GetRandomValue(50, 100), 0, 180}); // Alpha sedikit transparan
        }
        break;
    }
}

int main()
{
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "BREAK BRICKS");
    SetTargetFPS(60);

    // Muat gambar ikon dari file
    Image icon = LoadImage("assets/images/icon.png");

    SetWindowIcon(icon);

    LoadLifeTexture();
    InitBackground();
    InitSoundSystem();
    InitLeaderboard();

    PlayBackgroundMusic();

    // 🔹 Load leaderboard dari file
    LoadLeaderboard(LEADERBOARD_FILE);

    // Game State & Control
    GameState gameState = GAME_MENU;
    bool isPaused = false;
    bool isFullscreen = false;
    bool leaderboardUpdated = false;

    bool lifeLost = false;                  // Status apakah nyawa berkurang
    float lifeLostTimer = 0.0f;             // Timer untuk menampilkan teks "LIFE LOST!"
    const float lifeLostDisplayTime = 1.5f; // Durasi teks "LIFE LOST!" ditampilkan (1.5 detik)
    // Level
    int currentLevel = 0;

    // Reset semua status background level di awal atau saat kembali ke menu utama
    for (int i = 0; i < 3; i++)
    {
        levelBgStates[i].gradientOffset = 0.0f;
        levelBgStates[i].effectOffset1 = 0.0f;
    }

    // Game Data
    Paddle paddles[PADDLE_ROWS][PADDLE_COLS];
    BolaList bolaList;
    Stopwatch *stopwatchList;
    Skor skor[MAX_PLAYERS];

    // Initialize
    InitDynamicMainMenu();

    while (!WindowShouldClose())
    {
        UpdateBackground();
        SetLifeIconSize(8.0f);
        SetLivesDisplayPosition(NYAWA_X, NYAWA_Y);
        UpdateMusic();
        UpdateMainMenuMini(&gameState);

        // Update timer untuk teks "LIFE LOST!"
        if (lifeLost)
        {
            lifeLostTimer += GetFrameTime();
            if (lifeLostTimer >= lifeLostDisplayTime)
            {
                lifeLost = false; // Sembunyikan teks setelah waktu tertentu
            }
        }

        if (IsKeyPressed(KEY_M))
            ToggleMusic();
        if (IsKeyPressed(KEY_W))
            IncreaseVolume();
        if (IsKeyPressed(KEY_S))
            DecreaseVolume();

        // === MENU STATE ===
        if (gameState == GAME_MENU)
        {
            leaderboardUpdated = false; // Reset flag update leaderboard
            gameEndTimer = 0.0f;        // Reset end timer
            currentLevel = 0;           // Reset level
            isPaused = false;           // Reset pause

            // 🔥 Reset power-up
            FreePowerUp(&powerUpList); // Hapus semua power-up aktif
            InitPowerUp(&powerUpList); // Inisialisasi ulang

            LoadLeaderboard(LEADERBOARD_FILE); // ⬅️ **Memuat ulang leaderboard setiap masuk ke menu utama!**

            UpdateDynamicMainMenu();

            BeginDrawing();
            DrawDynamicMainMenu();
            EndDrawing();

            if (IsExitGame())
                break;

            if (IsStartGame())
            {
                int level = GetSelectedLevel();

                if (level > 0)
                {
                    InitPaddles(paddles);
                    InitBola(&bolaList);
                    SetLivesDisplayPosition(NYAWA_X, NYAWA_Y);
                    InitLivesSystem(3);
                    InitStopwatch(&stopwatchList, MAX_PLAYERS);
                    InitSkor(skor);
                    SetLevel(&blockList, level);
                    currentLevel = level;

                    // Reset status animasi untuk background level yang baru dimulai
                    if (currentLevel > 0 && currentLevel <= 3)
                    {
                        levelBgStates[currentLevel - 1].gradientOffset = 0.0f;
                        levelBgStates[currentLevel - 1].effectOffset1 = 0.0f;
                        // TraceLog(LOG_INFO, TextFormat("Background state for Level %d RESET.", currentLevel));
                    }

                    gameState = GAME_START;
                    SetStartGame(false);
                }
            }

            continue;
        }

        // Update status animasi background level jika game sedang berjalan dan tidak di-pause
        if ((gameState == GAME_PLAY || gameState == GAME_START) && !isPaused)
        {
            if (currentLevel > 0 && currentLevel <= 3)
            {
                LevelBackgroundState *currentState = &levelBgStates[currentLevel - 1];
                float frameTimeFactor = GetFrameTime() * 60.0f; // Faktor untuk konsistensi kecepatan berdasarkan frame rate

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
                    // Level 1 tidak memiliki animasi, jadi tidak perlu diupdate di sini
                }
            }
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
                // Bola nempel paddle sebelum diluncurkan
                if (bolaList.head != NULL)
                {
                    bolaList.head->position.x = paddles[0][0].rect.x + PADDLE_WIDTH / 2;
                    bolaList.head->position.y = paddles[0][0].rect.y - bolaList.head->radius - 1;
                }

                UpdatePaddles(paddles, GetFrameTime());

                if (IsKeyPressed(KEY_SPACE))
                {
                    lifeLost = false;
                    gameState = GAME_PLAY;
                }
                break;

            case GAME_PLAY:
                UpdatePaddles(paddles, GetFrameTime());
                UpdateBola(&bolaList, paddles, &blockList, &gameState, &skor[0], stopwatchList, &powerUpList);
                UpdatePowerUp(&powerUpList, &paddles[0][0], &bolaList, GetFrameTime());
                UpdateStopwatch(stopwatchList);

                if (SemuaBolaMati(&bolaList))
                { // Cek semua bola, bukan hanya head
                    DecreaseLife();
                    if (!HasLivesLeft())
                    {
                        gameState = GAME_OVER;
                    }
                    else
                    {
                        PlaySfx("lose_life");
                        ResetBola(&bolaList); // Reset semua bola
                        gameState = GAME_START;
                        lifeLost = true;
                        lifeLostTimer = 0.0f;
                    }
                }
                break;

            case GAME_OVER:
                PlaySfx("game_over");
                ChangeMusic("assets/sounds/background_music.mp3");
                UpdateMusic();
                gameEndTimer += GetFrameTime();

                if (!leaderboardUpdated)
                {
                    AddEntryToLeaderboard(GetPlayerName(), skor[0].score, stopwatchList->time, currentLevel, "GAME OVER");
                    SaveLeaderboard(LEADERBOARD_FILE);
                    leaderboardUpdated = true;
                }

                DrawGameOverScreen();

                // ⬅️ **Tambahkan ini agar leaderboard langsung terlihat**
                DrawLeaderboardInfo(50, 400, 5);

                if (gameEndTimer >= returnDelay || IsKeyPressed(KEY_R))
                {
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
                    AddEntryToLeaderboard(GetPlayerName(), skor[0].score, stopwatchList->time, currentLevel, "WIN");
                    SaveLeaderboard(LEADERBOARD_FILE);
                    leaderboardUpdated = true;
                }

                DrawWinScreen();

                // ⬅️ **Tambahkan ini agar leaderboard langsung terlihat**
                DrawLeaderboardInfo(50, 400, 5);

                if (gameEndTimer >= returnDelay || IsKeyPressed(KEY_R))
                {
                    gameState = GAME_MENU;
                    gameEndTimer = 0.0f;
                }
                break;
            }
        }

        // === DRAWING ===
        BeginDrawing();
        ClearBackground((Color){30, 0, 60, 255});
        if (gameState == GAME_MENU)
        {
            DrawDynamicMainMenu(); // Yang mungkin memanggil DrawBackground() dari background.c (starfield)
        }
        else // Untuk GAME_START, GAME_PLAY, GAME_OVER, GAME_WIN
        {
            // Gambar latar belakang level dinamis
            if (currentLevel > 0 && currentLevel <= 3)
            {
                DrawDynamicLevelBackground(currentLevel, &levelBgStates[currentLevel - 1]);
            }
            else
            {
                // Jika tidak ada level spesifik (misalnya currentLevel = 0),
                // gambar background default atau starfield dari background.c
                DrawBackground(); // Menggambar starfield dari background.c
                                  // atau DrawDynamicLevelBackground(0, NULL); jika ada case default di sana
            }

            // Gambar elemen game di atas latar belakang level
            if (gameState == GAME_PLAY || gameState == GAME_START || gameState == GAME_OVER || gameState == GAME_WIN)
            {
                DrawPaddles(paddles);
                DrawBlocks(&blockList);
                DrawPowerUp(&powerUpList);
                DrawBola(&bolaList);
                DrawLives();
                DrawSkor(skor, SCORE_X, SCORE_Y);
                DrawStopwatch(stopwatchList);
                DrawMainMenuMini(gameState); // Mini menu di atas segalanya
            }
            // Layout garis & panel bawah (jika masih relevan di atas background level)
            DrawLine(835, 0, 835, SCREEN_HEIGHT, WHITE);
            DrawControlInfo();
        }

        // Tampilkan teks "LIFE LOST!" jika nyawa berkurang
        if (lifeLost)
        {
            DrawText("LIFE LOST!", SCREEN_WIDTH / 2 - 230, SCREEN_HEIGHT / 2 - 50, 50, RED);
        }

        if (gameState == GAME_OVER || gameState == GAME_WIN)
        {
            DrawRectangle(250, 100, 400, 250, WHITE); // Background kotak leaderboard
            DrawLeaderboardInfo(50, 400, 5);
        }

        // === GAME STATE UI ===
        if (gameState == GAME_START)
        {
            DrawText("PRESS SPACE TO LAUNCH", 210, SCREEN_HEIGHT / 2, 30, WHITE);
        }
        else if (gameState == GAME_OVER)
        {
            DrawGameOverScreen();
            DrawLeaderboardInfo(50, 400, 5);
        }
        else if (gameState == GAME_WIN)
        {
            DrawWinScreen();
            DrawLeaderboardInfo(50, 400, 5);
        }
        else if (isPaused)
        {
            DrawPauseScreen();
        }

        EndDrawing();

        // === FULLSCREEN TOGGLE ===
        if (IsKeyPressed(KEY_F))
        {
            isFullscreen = !isFullscreen;
            ToggleFullscreen();
        }
    }

    SaveLeaderboard(LEADERBOARD_FILE);
    FreeLeaderboard();
    FreeDynamicMainMenu();
    UnloadLifeTexture();
    UnloadSoundSystem();
    FreePowerUp(&powerUpList);
    UnloadMedalTextures();
    UnloadImage(icon);
    CloseWindow();
    return 0;
}