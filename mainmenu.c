// Nama Pembuat: Muhammad Brata Hadinata
// Nama Fitur: mainmenu.c
// Deskripsi: Kode ini mengatur tampilan dan logika Main Menu dalam game "Break Bricks", termasuk menu utama,
//            pemilihan level, pengaturan, input nama pemain, leaderboard, dan info.
//            Kode juga menangani interaksi tombol dengan mouse/keyboard serta efek suara.

#include "mainmenu.h"
#include "sound.h"
#include "game_state.h"
#include "background.h"
#include "layout.h"
#include "raylib.h"
#include "leaderboard.h"

#include <string.h>
#include <stdio.h>

// =====================================================
// 🔹 Variabel Global
// =====================================================
static MenuState currentMenu = MENU_MAIN;
static bool exitGame = false;                       // Status untuk keluar dari game
static bool startGame = false;                      // Status mulai game
static bool soundOn = true;                         // Status sound aktif/tidak
static int selectedLevel = 0;                       // Level yang dipilih user
static char playerName[MAX_NAME_LENGTH] = "";       // Nama player
static int letterCount = 0;                         // Jumlah huruf yang diinput
static Rectangle textBox = {350, 300, 300, 50};     // Area input nama
static bool mouseOnText = false;                    // Status mouse di atas textbox
static int leaderboardScrollOffset = 0;             // Scroll leaderboard (jika ada)
static Rectangle miniMenuBtn = {850, 580, 140, 40}; // Tombol mini-menu di in-game

// =====================================================
// 🔹 Tombol utama (menu utama, setting, dsb.)
// =====================================================
static Rectangle buttons[] = {
    {350, 250, 320, 50},                   // 0 - Start Game
    {350, 320, 320, 50},                   // 1 - Leaderboard
    {350, 390, 320, 50},                   // 2 - Settings
    {350, 460, 320, 50},                   // 3 - Exit Game
    {SCREEN_WIDTH / 2 - 60, 300, 140, 40}, // 4 - Sound Toggle
    {SCREEN_WIDTH / 2 - 110, 300, 40, 40}, // 5 - Sound Volume Down
    {SCREEN_WIDTH / 2 + 90, 300, 40, 40},  // 6 - Sound Volume Up
    {470, 390, 70, 40},                    // 7 - Back to Main Menu (settings)
    {900, 590, 70, 40},                    // 8 - Info
};

// =====================================================
// 🔹 Tombol pemilihan level
// =====================================================
static Rectangle levelButtons[] = {
    {350, 250, 300, 50}, // 0 - Level Easy
    {350, 320, 300, 50}, // 1 - Level Medium
    {350, 390, 300, 50}, // 2 - Level Hard
    {20, 20, 100, 40},   // 3 - Back Button (dari level select/info)
};

// =====================================================
// 🔹 Tombol input nama
// =====================================================
static Rectangle inputName[] = {
    {20, 20, 170, 40}, // 0 - Back to Level Select
};

// =====================================================
// 🔹 Warna Pelangi buat efek teks
// =====================================================
static Color rainbowColors[] = {RED, ORANGE, YELLOW, GREEN, BLUE, PURPLE};
static int rainbowSize = sizeof(rainbowColors) / sizeof(rainbowColors[0]);

// =====================================================
// 🔹 Fungsi untuk gambar teks pelangi
// =====================================================
void DrawRainbowText(const char *text, int centerX, int posY, int fontSize)
{
    int letterCount = 0;
    float totalWidth = 0;
    float letterWidths[256] = {0};

    // Hitung panjang keseluruhan teks
    for (int i = 0; text[i] != '\0'; i++)
    {
        letterWidths[i] = MeasureTextEx(GetFontDefault(), TextFormat("%c", text[i]), fontSize, 2).x;
        totalWidth += letterWidths[i] + 3;
        letterCount++;
    }

    float startX = centerX - (totalWidth / 2);
    float xOffset = 0;

    // Gambar tiap huruf
    for (int i = 0; i < letterCount; i++)
    {
        Color letterColor = rainbowColors[i % rainbowSize];
        DrawTextEx(GetFontDefault(), TextFormat("%c", text[i]),
                   (Vector2){startX + xOffset, posY}, fontSize, 2, letterColor);
        xOffset += letterWidths[i] + 5;
    }
}

// =====================================================
// 🔹 Mini Menu Button saat game berjalan
// =====================================================
void UpdateMainMenuMini(GameState *state)
{
    Vector2 mouse = GetMousePosition();

    if ((*state == GAME_START || *state == GAME_PLAY) &&
        CheckCollisionPointRec(mouse, miniMenuBtn) &&
        IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
    {

        PlayButtonClick();
        *state = GAME_MENU;
        ChangeMusic("assets/sounds/background_music.mp3");
        UpdateMusic();
    }
}

void DrawMainMenuMini(GameState state)
{
    if (state != GAME_START && state != GAME_PLAY)
        return;

    Vector2 mouse = GetMousePosition();
    Color miniColor = CheckCollisionPointRec(mouse, miniMenuBtn) ? BLUE : YELLOW;
    DrawRectangleRec(miniMenuBtn, miniColor);
    DrawText("Main Menu", miniMenuBtn.x + 10, miniMenuBtn.y + 10, 20, BLACK);
}

// =====================================================
// 🔹 Judul game
// =====================================================
void DrawTitle()
{
    DrawRainbowText("BREAK BRICKS", SCREEN_WIDTH / 2, 150, 75);
}

// =====================================================
// 🔹 Inisialisasi menu
// =====================================================
void InitMainMenu()
{
    currentMenu = MENU_MAIN;
    exitGame = startGame = false;
    selectedLevel = 0;
    soundOn = true;
    letterCount = 0;
    strcpy(playerName, "");
}

// =====================================================
// 🔹 Update Menu (logic interaksi tombol & navigasi menu)
// =====================================================
void UpdateMainMenu()
{
    Vector2 mouse = GetMousePosition();

    // 🔸 Menu Utama
    if (currentMenu == MENU_MAIN)
    {
        if (CheckCollisionPointRec(mouse, buttons[0]) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
        {
            PlayButtonClick();
            currentMenu = MENU_LEVEL_SELECT;
        }
        if (CheckCollisionPointRec(mouse, buttons[1]) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
        {
            PlayButtonClick();
            currentMenu = MENU_LEADERBOARD;
        }
        if (CheckCollisionPointRec(mouse, buttons[2]) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
        {
            PlayButtonClick();
            currentMenu = MENU_SETTINGS;
        }
        if (CheckCollisionPointRec(mouse, buttons[8]) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
        {
            PlayButtonClick();
            currentMenu = MENU_INFO;
        }
        if (CheckCollisionPointRec(mouse, buttons[3]) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
        {
            PlayButtonClick();
            exitGame = true;
        }
    }
    // 🔸 Menu Pemilihan Level
    else if (currentMenu == MENU_LEVEL_SELECT)
    {
        for (int i = 0; i < 3; i++)
        {
            if (CheckCollisionPointRec(mouse, levelButtons[i]) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
            {
                PlayButtonClick();
                selectedLevel = i + 1;
                currentMenu = MENU_NAME_INPUT;
                letterCount = 0;
                strcpy(playerName, "");
            }
        }
        if (IsKeyPressed(KEY_BACKSPACE) || (CheckCollisionPointRec(mouse, levelButtons[3]) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)))
        {
            PlayButtonClick();
            currentMenu = MENU_MAIN;
        }
    }
    // 🔸 Menu Settings
    else if (currentMenu == MENU_SETTINGS)
    {
        if (CheckCollisionPointRec(mouse, buttons[4]) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
        {
            PlayButtonClick();
            ToggleSound();
        }
        if (CheckCollisionPointRec(mouse, buttons[5]) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
        {
            PlayButtonClick();
            DecreaseVolume();
        }
        if (CheckCollisionPointRec(mouse, buttons[6]) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
        {
            PlayButtonClick();
            IncreaseVolume();
        }
        if (CheckCollisionPointRec(mouse, buttons[7]) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
        {
            PlayButtonClick();
            currentMenu = MENU_MAIN;
        }
        if (IsKeyPressed(KEY_BACKSPACE))
        {
            currentMenu = MENU_MAIN;
        }
    }
    // 🔸 Menu Info
    else if (currentMenu == MENU_INFO)
    {
        if (IsKeyPressed(KEY_BACKSPACE) || (CheckCollisionPointRec(mouse, levelButtons[3]) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)))
        {
            PlayButtonClick();
            currentMenu = MENU_MAIN;
        }
    }
    // 🔸 Input Nama Pemain
    else if (currentMenu == MENU_NAME_INPUT)
    {
        mouseOnText = CheckCollisionPointRec(mouse, textBox);
        if (mouseOnText)
        {
            SetMouseCursor(MOUSE_CURSOR_IBEAM);
            int key = GetCharPressed();
            if (letterCount < 8)
            {
                if (((key >= 32) && (key <= 125)) && (key != '\\') && (key != '/') && (key != ':') &&
                    (key != '*') && (key != '?') && (key != '\"') && (key != '<') && (key != '>') && (key != '|'))
                {
                    playerName[letterCount] = (char)key;
                    playerName[++letterCount] = '\0';
                }
            }
            if (IsKeyPressed(KEY_BACKSPACE))
            {
                if (letterCount > 0)
                    playerName[--letterCount] = '\0';
            }
            if (IsKeyPressed(KEY_ENTER) && letterCount > 0)
            {
                PlayButtonClick();
                startGame = true;
                currentMenu = MENU_MAIN;
            }
        }
        else
        {
            SetMouseCursor(MOUSE_CURSOR_DEFAULT);
        }
        if (CheckCollisionPointRec(mouse, inputName[0]) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
        {
            PlayButtonClick();
            currentMenu = MENU_LEVEL_SELECT;
        }
    }
    // 🔸 Menu Leaderboard
    else if (currentMenu == MENU_LEADERBOARD)
    {
        if (IsKeyPressed(KEY_BACKSPACE))
        {
            currentMenu = MENU_MAIN;
        }
    }
}

// =====================================================
// 🔹 Gambar Menu (tampilan visual di layar)
// =====================================================
void DrawMainMenu()
{
    ClearBackground((Color){30, 0, 60, 255});
    DrawBackground();
    Vector2 mouse = GetMousePosition();

    if (currentMenu == MENU_MAIN)
    {
        DrawTitle();

        const char *buttonTexts[] = {"START GAME", "LEADERBOARD", "SETTINGS", "EXIT GAME"};

        for (int i = 0; i < 4; i++)
        {
            Color buttonColor = CheckCollisionPointRec(mouse, buttons[i]) ? ((i == 3) ? RED : GREEN) : LIGHTGRAY;
            DrawRectangleRec(buttons[i], buttonColor);
            int textWidth = MeasureText(buttonTexts[i], 30);
            DrawText(buttonTexts[i], buttons[i].x + (buttons[i].width - textWidth) / 2, buttons[i].y + 10, 30, BLACK);
        }

        Color infoColor = CheckCollisionPointRec(mouse, buttons[8]) ? SKYBLUE : YELLOW;
        DrawRectangleRec(buttons[8], infoColor);
        DrawText("INFO", buttons[8].x + 10, buttons[8].y + 10, 20, BLACK);
    }

    else if (currentMenu == MENU_SETTINGS)
    {
        DrawRainbowText("SETTINGS", SCREEN_WIDTH / 2, 150, 45);
        Color soundColor = CheckCollisionPointRec(mouse, buttons[4]) ? SKYBLUE : YELLOW;
        DrawRectangleRec(buttons[4], soundColor);
        DrawText(soundOn ? "SOUND ON" : "SOUND OFF", buttons[4].x + 10, buttons[4].y + 10, 20, BLACK);

        Color decreaseColor = CheckCollisionPointRec(mouse, buttons[5]) ? SKYBLUE : YELLOW;
        DrawRectangleRec(buttons[5], decreaseColor);
        DrawText("-", buttons[5].x + 10, buttons[5].y + 10, 20, BLACK);

        Color increaseColor = CheckCollisionPointRec(mouse, buttons[6]) ? SKYBLUE : YELLOW;
        DrawRectangleRec(buttons[6], increaseColor);
        DrawText("+", buttons[6].x + 10, buttons[6].y + 10, 20, BLACK);

        Color backColor = CheckCollisionPointRec(mouse, buttons[7]) ? RED : LIGHTGRAY;
        DrawRectangleRec(buttons[7], backColor);
        DrawText("BACK", buttons[7].x + 10, buttons[7].y + 10, 20, BLACK);
    }

    else if (currentMenu == MENU_INFO)
    {
        DrawRainbowText("INFO", SCREEN_WIDTH / 2, 100, 45);
        DrawText("Kelompok C6 Proyek 2 POLBAN:", SCREEN_WIDTH / 2 - 160, 200, 20, WHITE);
        DrawText("Ahmad Habib Mutaqqin (241511065)", SCREEN_WIDTH / 2 - 160, 250, 20, WHITE);
        DrawText("Muhammad Brata Hadinata (241511082)", SCREEN_WIDTH / 2 - 160, 300, 20, WHITE);
        DrawText("Dan anggota lainnya...", SCREEN_WIDTH / 2 - 160, 350, 20, WHITE);

        Color backColor = CheckCollisionPointRec(mouse, levelButtons[3]) ? RED : LIGHTGRAY;
        DrawRectangleRec(levelButtons[3], backColor);
        DrawText("BACK", levelButtons[3].x + 20, levelButtons[3].y + 10, 20, BLACK);
    }

    else if (currentMenu == MENU_LEVEL_SELECT)
    {
        DrawRainbowText("SELECT LEVEL", SCREEN_WIDTH / 2, 150, 45);
        const char *levels[] = {"EASY", "MEDIUM", "HARD"};
        Color levelColors[] = {GREEN, ORANGE, RED};

        for (int i = 0; i < 3; i++)
        {
            Color color = CheckCollisionPointRec(mouse, levelButtons[i]) ? levelColors[i] : LIGHTGRAY;
            DrawRectangleRec(levelButtons[i], color);
            int textWidth = MeasureText(levels[i], 30);
            DrawText(levels[i], levelButtons[i].x + (levelButtons[i].width - textWidth) / 2, levelButtons[i].y + 10, 30, BLACK);
        }

        Color backColor = CheckCollisionPointRec(mouse, levelButtons[3]) ? RED : LIGHTGRAY;
        DrawRectangleRec(levelButtons[3], backColor);
        DrawText("BACK", levelButtons[3].x + 10, levelButtons[3].y + 10, 20, BLACK);
    }

    else if (currentMenu == MENU_NAME_INPUT)
    {
        DrawRainbowText("INPUT NAME", SCREEN_WIDTH / 2, 150, 45);
        DrawRectangleRec(textBox, mouseOnText ? SKYBLUE : LIGHTGRAY);
        DrawText(playerName, textBox.x + 10, textBox.y + 10, 20, BLACK);

        Color backColor = CheckCollisionPointRec(mouse, inputName[0]) ? RED : LIGHTGRAY;
        DrawRectangleRec(inputName[0], backColor);
        DrawText("BACK", inputName[0].x + 10, inputName[0].y + 10, 20, BLACK);
    }
}
