/* BREAK BRICKS
    Game Breakout sederhana dengan beberapa level dan leaderboard.
    Oleh: Kelompok C6 Proyek 2 POLBAN
    - Wyandhanu Maulidan Nugraha (241511092)
    - Siti Soviyyah (241511090)
    - Nezya Zulfa Fauziah (241511085)
    - Muhammad Raihan Abubakar (241511084)
    - Muhammad Brata Hadinata (241511082)
    - Ahmad Habib Mutaqqin (241511065)
*/
#include <raylib.h>
#include <stdio.h>  // Untuk snprintf
#include <stdlib.h> // Untuk malloc, free, srand, rand
#include <math.h>   // For sinf, cosf, fabsf
#include <time.h>   // Untuk time() pada srand

// Game Modules
#include "game_state.h"
#include "paddle.h"
#include "LinkedList-Block.h"
#include "BOLA.h"
#include "nyawa.h"
#include "skor.h"
#include "stopwatch.h"
#include "leaderboard.h"
#include "mainmenu.h"
#include "LinkedList-level.h"
#include "layout.h"
#include "background.h"
#include "sound.h"
#include "powerup.h"

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
PowerUpList powerUpList;
LinkedList blockList;
PaddleList paddleList;
BolaList bolaList;
Stopwatch *stopwatchList = NULL;
Skor skor[MAX_PLAYERS];

// Fungsi untuk menggambar timer power-up aktif
void DrawActivePowerUpTimers(PaddleList *pList)
{ // Ubah nama parameter agar tidak bentrok
    if (!pList || !pList->head)
    {
        return;
    }

    PaddleNode *playerPaddle = pList->head;
    ActivePowerUp *effect = playerPaddle->activePowerUps;
    int currentY = POWERUP_TIMER_Y;
    char timerText[128];
    bool hasActiveTimersTitleDrawn = false;

    while (effect != NULL)
    {
        const char *effectName = NULL;
        bool displayThisTimer = false;

        switch (effect->type)
        {
        case POWERUP_TRIPLE_BALL:
            // Timer untuk Triple Ball mungkin tidak terlalu informatif karena efeknya instan
            // Jika ingin ditampilkan, beri nama "Triple Ball Active" atau semacamnya
            // effectName = "Triple Ball";
            // displayThisTimer = true;
            break;
        case POWERUP_LONG_PADDLE:
            effectName = "Long Paddle";
            displayThisTimer = true;
            break;
        }

        if (displayThisTimer && effectName && effect->remainingTime > 0)
        {
            if (!hasActiveTimersTitleDrawn)
            {
                DrawText("Active Effects:", POWERUP_TIMER_X, currentY, POWERUP_TIMER_FONT_SIZE - 2, YELLOW); // Font sedikit lebih kecil untuk judul
                currentY += POWERUP_TIMER_SPACING;
                hasActiveTimersTitleDrawn = true;
            }
            snprintf(timerText, sizeof(timerText), "- %s: %.1fs", effectName, effect->remainingTime);
            DrawText(timerText, POWERUP_TIMER_X, currentY, POWERUP_TIMER_FONT_SIZE, WHITE);
            currentY += POWERUP_TIMER_SPACING;
        }
        effect = effect->next;
    }
}

void DrawDynamicLevelBackground(int level, LevelBackgroundState *bgState)
{
    // Implementasi Anda sudah ada di sini, pastikan SCREEN_WIDTH dan SCREEN_HEIGHT dari game_state.h
    // ... (kode DrawDynamicLevelBackground Anda)
    if (level <= 0 || level > 3)
    {
        DrawRectangle(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, (Color){5, 5, 20, 255});
        return;
    }
    if (!bgState && (level == 2 || level == 3))
    { // Perlu pengecekan bgState != NULL
        DrawRectangle(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, (Color){10, 10, 30, 255});
        return;
    }

    // Jika bgState NULL untuk level 1, berikan default sederhana
    if (!bgState && level == 1)
    {
        DrawRectangle(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, (Color){10, 20, 30, 255});
        return;
    }

    switch (level)
    {
    case 1: // Latar belakang statis atau gradasi sederhana
        for (int y = 0; y < SCREEN_HEIGHT; y++)
        {
            float gradient = (float)y / SCREEN_HEIGHT;
            Color color = (Color){(int)(10 + 5 * gradient), (int)(20 + 10 * gradient), (int)(30 + 15 * gradient), 255};
            DrawLine(0, y, SCREEN_WIDTH, y, color);
        }
        break;
    case 2: // Latar belakang dengan sedikit animasi
        if (bgState)
        { // Pastikan bgState tidak NULL
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
        }
        break;
    case 3: // Latar belakang lebih dinamis
        if (bgState)
        { // Pastikan bgState tidak NULL
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
        }
        break;
    }
}

int main()
{
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "BREAK BRICKS");
    SetTargetFPS(60);
    // srand(time(NULL)); // Pindahkan srand ke sini agar dipanggil sekali saja

    Image icon = LoadImage("assets/images/icon.png");
    if (icon.data != NULL)
        SetWindowIcon(icon); // Hanya jika berhasil load
    else
        TraceLog(LOG_WARNING, "MAIN: Failed to load window icon.");

    LoadLifeTexture();
    SetLifeIconSize(6.0f);                     // Atur ukuran ikon nyawa sekali (atau saat diperlukan)
    SetLivesDisplayPosition(NYAWA_X, NYAWA_Y); // Atur posisi sekali (atau saat diperlukan)

    InitBackground();
    InitSoundSystem();
    InitLeaderboard();
    LoadLeaderboard(LEADERBOARD_FILE);
    PlayBackgroundMusic();

    GameState gameState = GAME_MENU;
    bool isPaused = false;
    // bool isFullscreen = false; // IsFullscreen() dari Raylib bisa digunakan jika perlu
    bool leaderboardUpdated = false;
    bool lifeLostThisFrame = false; // Ganti nama dari lifeLost agar lebih jelas peruntukannya
    float lifeLostDisplayTimer = 0.0f;
    const float lifeLostDisplayDuration = 1.5f;
    int currentLevel = 0;

    for (int i = 0; i < 3; i++)
    {
        levelBgStates[i].gradientOffset = 0.0f;
        levelBgStates[i].effectOffset1 = 0.0f;
    }

    InitPowerUp(&powerUpList);
    InitList(&blockList);
    // paddleList dan bolaList diinisialisasi saat game dimulai
    // stopwatchList dan skor juga

    InitDynamicMainMenu();

    while (!WindowShouldClose())
    {
        float deltaTime = GetFrameTime(); // Ambil deltaTime sekali per frame

        UpdateBackground();
        UpdateMusic(); // Harus dipanggil setiap frame untuk streaming musik

        if (lifeLostThisFrame)
        {
            lifeLostDisplayTimer += deltaTime;
            if (lifeLostDisplayTimer >= lifeLostDisplayDuration)
            {
                lifeLostThisFrame = false;
                lifeLostDisplayTimer = 0.0f;
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
            currentLevel = 0; // Reset level saat kembali ke menu
            isPaused = false; // Pastikan pause direset

            // Bersihkan state game sebelumnya
            FreePowerUp(&powerUpList); // Kosongkan list power-up yang jatuh
            InitPowerUp(&powerUpList); // Inisialisasi ulang
            FreePaddles(&paddleList);  // Kosongkan list paddle
            FreeBola(&bolaList);       // Kosongkan list bola
            ClearList(&blockList);     // Kosongkan list blok

            if (stopwatchList)
            { // Hapus stopwatch lama jika ada
                Stopwatch *tempSw = stopwatchList;
                while (tempSw)
                {
                    Stopwatch *nextSw = tempSw->next;
                    free(tempSw);
                    tempSw = nextSw;
                }
                stopwatchList = NULL;
            }
            // Skor akan di-InitSkor saat game baru dimulai

            UpdateDynamicMainMenu();
            BeginDrawing();
            DrawDynamicMainMenu();
            EndDrawing();

            if (IsExitGame())
                break;
            if (IsStartGame())
            {
                int level = GetSelectedLevel();
                if (level > 0 && level <= 3)
                { // Pastikan level valid
                    currentLevel = level;

                    InitPaddles(&paddleList);
                    InitBola(&bolaList);
                    InitLivesSystem(3);
                    InitStopwatch(&stopwatchList, 1);
                    InitSkor(skor); // Menggunakan MAX_PLAYERS dari game_state.h

                    ClearList(&blockList); // Pastikan bersih sebelum set level baru
                    SetLevel(&blockList, currentLevel);

                    // Reset animasi background untuk level baru
                    levelBgStates[currentLevel - 1].gradientOffset = 0.0f;
                    levelBgStates[currentLevel - 1].effectOffset1 = 0.0f;

                    gameState = GAME_START;
                    SetStartGame(false);                             // Reset flag di mainmenu
                    ChangeMusic("assets/sounds/gameplay_music.mp3"); // Pindah musik ke gameplay
                }
                else
                {
                    TraceLog(LOG_WARNING, "MAIN: Invalid level selected: %d", level);
                    SetStartGame(false); // Reset flag agar tidak stuck
                    // Kembali ke menu atau state default jika level tidak valid
                }
            }
            continue;
        }

        // Update animasi background untuk level saat ini (jika game berjalan)
        if ((gameState == GAME_PLAY || gameState == GAME_START) && !isPaused)
        {
            if (currentLevel > 0 && currentLevel <= 3)
            {
                LevelBackgroundState *currentState = &levelBgStates[currentLevel - 1];
                // float frameTimeFactor = deltaTime * 60.0f; // Tidak perlu jika speed sudah per detik
                switch (currentLevel)
                {
                case 2:
                    currentState->gradientOffset += 0.05f * deltaTime; // Sesuaikan speed dengan deltaTime
                    currentState->effectOffset1 += 0.03f * deltaTime;
                    break;
                case 3:
                    currentState->gradientOffset += 0.1f * deltaTime;
                    currentState->effectOffset1 += 0.05f * deltaTime;
                    break;
                }
            }
        }

        if (IsKeyPressed(KEY_P) && (gameState == GAME_PLAY || gameState == GAME_START))
        { // Pause bisa juga di GAME_START
            isPaused = !isPaused;
            if (isPaused)
                PauseMusic();
            else
                PauseMusic(); // Gunakan ResumeMusic agar melanjutkan, bukan toggle play/stop
        }

        UpdateMainMenuMini(&gameState); // Tombol kembali ke menu utama saat in-game

        if (!isPaused)
        {
            switch (gameState)
            {
            case GAME_START:
                UpdatePaddles(&paddleList, deltaTime);
                // Bola menempel di paddle, update posisi bola berdasarkan paddle
                if (paddleList.head != NULL && bolaList.head != NULL)
                {
                    bolaList.head->position.x = paddleList.head->rect.x + paddleList.head->rect.width / 2.0f - bolaList.head->radius / 2.0f; // Koreksi sedikit agar tengah bola pas
                    bolaList.head->position.y = paddleList.head->rect.y - bolaList.head->radius - 1.0f;
                    bolaList.head->speed = (Vector2){0, 0}; // Pastikan bola tidak bergerak sendiri
                }

                if (IsKeyPressed(KEY_SPACE))
                {
                    lifeLostThisFrame = false;
                    if (bolaList.head != NULL)
                    {
                        // Beri kecepatan awal saat diluncurkan
                        bolaList.head->speed.y = -MIN_BALL_SPEED; // Kecepatan awal Y
                        // Pengaruh horizontal dari mouse (opsional, atau buat tetap lurus)
                        // float mouseInfluence = (GetMouseX() - (paddleList.head->rect.x + paddleList.head->rect.width / 2.0f)) / (paddleList.head->rect.width / 2.0f);
                        // bolaList.head->speed.x = mouseInfluence * (MAX_BALL_SPEED * 0.5f);
                        bolaList.head->speed.x = (GetRandomValue(0, 1) == 0 ? -1 : 1) * MIN_BALL_SPEED * 0.5f; // Arah X acak kecil
                    }
                    gameState = GAME_PLAY;
                }
                break;
            case GAME_PLAY:
                UpdatePaddles(&paddleList, deltaTime);
                UpdateBola(&bolaList, &paddleList, &blockList, &gameState, &skor[0], stopwatchList, &powerUpList);
                UpdatePowerUp(&powerUpList, &paddleList, &bolaList, deltaTime); // Update item power-up yang jatuh
                if (stopwatchList)
                    UpdateStopwatch(stopwatchList);

                if (SemuaBolaMati(&bolaList))
                {
                    DecreaseLife();
                    if (!HasLivesLeft())
                    {
                        gameState = GAME_OVER;
                        PlaySfx("game_over");
                        ChangeMusic("assets/sounds/background_music.mp3");
                    }
                    else
                    {
                        PlaySfx("lose_life");
                        // Reset paddle ke kondisi default (termasuk lebar) dan hapus efek power-up aktif
                        if (paddleList.head)
                        {
                            paddleList.head->rect.width = PADDLE_WIDTH_DEFAULT; // Reset lebar
                            // Hapus semua ActivePowerUp dari paddle
                            ActivePowerUp *currentEffect = paddleList.head->activePowerUps;
                            while (currentEffect != NULL)
                            {
                                ActivePowerUp *temp = currentEffect;
                                currentEffect = currentEffect->next;
                                free(temp);
                            }
                            paddleList.head->activePowerUps = NULL;
                        }
                        FreePowerUp(&powerUpList); // Hapus item power-up yang jatuh
                        InitPowerUp(&powerUpList); // Inisialisasi ulang

                        ResetBola(&bolaList); // Reset bola, akan muncul bola baru di state GAME_START
                        gameState = GAME_START;
                        lifeLostThisFrame = true;
                        lifeLostDisplayTimer = 0.0f;
                    }
                }
                if (AllBlocksDestroyed(&blockList))
                { // Cek gameState agar tidak memicu ulang
                    gameState = GAME_WIN;
                    PlaySfx("game_win");
                    ChangeMusic("assets/sounds/background_music.mp3");
                }
                break;
            case GAME_OVER:
            case GAME_WIN:
                gameEndTimer += deltaTime;
                if (!leaderboardUpdated)
                {
                    const char *statusText = (gameState == GAME_WIN) ? "WIN" : "GAME OVER";
                    AddEntryToLeaderboard(GetPlayerName(), skor[0].score, stopwatchList ? stopwatchList->time : 0.0f, currentLevel, statusText);
                    SaveLeaderboard(LEADERBOARD_FILE);
                    leaderboardUpdated = true;
                }
                if (gameEndTimer >= returnDelay || IsKeyPressed(KEY_ENTER) || IsKeyPressed(KEY_R))
                {
                    gameState = GAME_MENU;
                }
                break;
            default:
                break;
            }
        }

        BeginDrawing();
        ClearBackground((Color){10, 0, 20, 255}); // Warna latar sedikit diubah

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
                DrawBackground(); // Fallback jika level tidak valid (atau saat transisi)
            }

            if (gameState == GAME_PLAY || gameState == GAME_START || gameState == GAME_OVER || gameState == GAME_WIN)
            {
                DrawPaddles(&paddleList);
                DrawBlocks(&blockList);
                DrawPowerUp(&powerUpList);
                DrawBola(&bolaList);

                // UI Panel Kanan
                DrawRectangle(GAME_PLAY_AREA_WIDTH, 0, SCREEN_WIDTH - GAME_PLAY_AREA_WIDTH, SCREEN_HEIGHT, Fade(BLACK, 0.5f));
                DrawLine(GAME_PLAY_AREA_WIDTH, 0, GAME_PLAY_AREA_WIDTH, SCREEN_HEIGHT, LIGHTGRAY);

                DrawLives();
                DrawSkor(skor, SCORE_X, SCORE_Y);
                if (stopwatchList)
                    DrawStopwatch(stopwatchList);

                if (gameState == GAME_PLAY || gameState == GAME_START)
                {
                    DrawActivePowerUpTimers(&paddleList);
                }
                DrawMainMenuMini(gameState);
            }
            DrawControlInfo();
        }

        if (lifeLostThisFrame && (gameState == GAME_START))
        { // Tampilkan hanya di state start setelah nyawa hilang
            DrawText("LIFE LOST!", SCREEN_WIDTH / 2 - MeasureText("LIFE LOST!", 50) / 2, SCREEN_HEIGHT / 2 - 50, 50, RED);
        }

        if (gameState == GAME_START && !lifeLostThisFrame)
        {
            DrawText("PRESS SPACE TO LAUNCH",
                     (int)(GAME_PLAY_AREA_WIDTH / 2.0f - MeasureText("PRESS SPACE TO LAUNCH", 30) / 2.0f), // Tengah area main
                     (int)(GAME_PLAY_AREA_HEIGHT / 2.0f), 30, WHITE);
        }
        else if (gameState == GAME_OVER)
        {
            DrawGameOverScreen();
            DrawLeaderboardInfo(SCREEN_WIDTH / 2 - 150, 400, 3);
        }
        else if (gameState == GAME_WIN)
        {
            DrawWinScreen();
            DrawLeaderboardInfo(SCREEN_WIDTH / 2 - 150, 400, 3);
        }

        if (isPaused)
        {
            DrawPauseScreen();
        }

        EndDrawing();

        if (IsKeyPressed(KEY_F))
        {
            // isFullscreen = !isFullscreen; // Variabel ini tidak digunakan Raylib secara internal
            ToggleFullscreen();
        }
    }

    // Cleanup
    FreePaddles(&paddleList);
    FreeBola(&bolaList);
    ClearList(&blockList);
    FreePowerUp(&powerUpList);
    if (stopwatchList)
    {
        Stopwatch *tempSw = stopwatchList;
        while (tempSw)
        {
            Stopwatch *nextSw = tempSw->next;
            free(tempSw);
            tempSw = nextSw;
        }
        stopwatchList = NULL;
    }
    SaveLeaderboard(LEADERBOARD_FILE); // Simpan sekali lagi sebelum keluar
    FreeLeaderboard();
    FreeDynamicMainMenu();
    UnloadLifeTexture();
    UnloadSoundSystem();
    UnloadMedalTextures();
    if (icon.data != NULL)
        UnloadImage(icon); // Hanya unload jika berhasil load
    CleanupBackground();
    CloseWindow();
    return 0;
}
