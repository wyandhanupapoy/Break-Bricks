// mainmenu.c
#include "mainmenu.h"
#include "sound.h"
#include "game_state.h"
#include "background.h"
#include "raylib.h"
#include "leaderboard.h"
#include "game_state.h"

#include <string.h>
#include <stdio.h>

// 🔹 Variabel Global
static MenuState currentMenu = MENU_MAIN;
static bool exitGame = false, startGame = false, soundOn = true;
static int selectedLevel = 0;
static char playerName[MAX_NAME_LENGTH] = "";
static int letterCount = 0;
static Rectangle textBox = {350, 300, 300, 50};
static bool mouseOnText = false;
static int leaderboardScrollOffset = 0;

static Rectangle miniMenuBtn = {850, 580, 140, 40};

// 🔹 Tombol utama
static Rectangle buttons[] = {
    {350, 250, 320, 50}, // Start Game
    {350, 320, 320, 50}, // Leaderboard
    {350, 390, 320, 50}, // Exit Game
    {10, 600, 140, 40},  // Sound Toggle
};

// 🔹 Tombol level select
// 🔹 Tombol level select
static Rectangle levelButtons[] = {
    {350, 250, 300, 50}, // Level Easy
    {350, 320, 300, 50}, // Level Medium
    {350, 390, 300, 50}, // Level Hard
    {20, 20, 100, 40},   // Back Button
};

static Rectangle inputName[] = {
    {20, 20, 170, 40}, // Back to Main Menu Button
};

// 🔹 Warna Pelangi
static Color rainbowColors[] = {RED, ORANGE, YELLOW, GREEN, BLUE, PURPLE};
static int rainbowSize = sizeof(rainbowColors) / sizeof(rainbowColors[0]);

// 🔹 Gambar Teks Pelangi dengan Spacing yang Lebih Presisi
void DrawRainbowText(const char *text, int centerX, int posY, int fontSize)
{
    int letterCount = 0;
    float totalWidth = 0;
    float letterWidths[256] = {0}; // Simpan ukuran tiap huruf

    // 🔹 Hitung total panjang teks & simpan lebar tiap huruf
    for (int i = 0; text[i] != '\0'; i++)
    {
        letterWidths[i] = MeasureTextEx(GetFontDefault(), TextFormat("%c", text[i]), fontSize, 2).x;
        totalWidth += letterWidths[i] + 3;
        letterCount++;
    }

    // 🔹 Pastikan teks tetap di tengah
    float startX = centerX - (totalWidth / 2);
    float xOffset = 0;

    // 🔹 Gambar huruf satu per satu dengan spacing yang stabil
    for (int i = 0; i < letterCount; i++)
    {
        Color letterColor = rainbowColors[i % rainbowSize]; // Warna bergantian
        DrawTextEx(GetFontDefault(), TextFormat("%c", text[i]),
                   (Vector2){startX + xOffset, posY}, fontSize, 2, letterColor);
        xOffset += letterWidths[i] + 5; // Spacing antar huruf
    }
}

// 🔹 Update Mini Menu (Hanya saat game berjalan)
void UpdateMainMenuMini(GameState *state)
{
    Vector2 mouse = GetMousePosition();

    if ((*state == GAME_START || *state == GAME_PLAY) && CheckCollisionPointRec(mouse, miniMenuBtn) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
    {
        PlayButtonClick();
        *state = GAME_MENU; // Kembali ke Main Menu
        ChangeMusic("assets/sounds/background_music.mp3");
        UpdateMusic();
    }
}

// 🔹 Gambar Mini Menu (Hanya saat game berjalan)
void DrawMainMenuMini(GameState state)
{
    if (state != GAME_START && state != GAME_PLAY)
        return; // Tampilkan hanya jika sedang bermain

    Vector2 mouse = GetMousePosition();

    Color miniColor = CheckCollisionPointRec(mouse, miniMenuBtn) ? BLUE : YELLOW;
    DrawRectangleRec(miniMenuBtn, miniColor);

    // **Pastikan teks berada di tengah tombol**
    int textWidth = MeasureText("Main Menu", 20);
    int textX = 870;
    int textY = 590;

    DrawText("Main Menu", textX, textY, 20, BLACK);
}

// 🔹 Gambar Title "BREAK BRICKS"
void DrawTitle()
{
    DrawRainbowText("BREAK BRICKS", SCREEN_WIDTH / 2, 150, 75);
}

// 🔹 Inisialisasi Menu
void InitMainMenu()
{
    currentMenu = MENU_MAIN;
    exitGame = startGame = false;
    selectedLevel = 0;
    soundOn = true;
    letterCount = 0;
    strcpy(playerName, "");
}

// 🔹 Update Menu
void UpdateMainMenu()
{
    Vector2 mouse = GetMousePosition();

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
            exitGame = true;
        }
        if (CheckCollisionPointRec(mouse, buttons[3]) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
        {
            ToggleSound();
        }
    }
    else if (currentMenu == MENU_LEVEL_SELECT)
    {
        for (int i = 0; i < 3; i++)
        {
            if (CheckCollisionPointRec(mouse, levelButtons[i]) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
            {
                PlayButtonClick();
                selectedLevel = i + 1;
                letterCount = 0;
                strcpy(playerName, "");
                currentMenu = MENU_NAME_INPUT;
            }
        }

        // Penanganan tombol BACKSPACE
        if (IsKeyPressed(KEY_BACKSPACE))
        {
            currentMenu = MENU_MAIN;
        }
    }
    else if (currentMenu == MENU_NAME_INPUT)
    {
        mouseOnText = CheckCollisionPointRec(mouse, textBox);

        if (mouseOnText)
        {
            SetMouseCursor(MOUSE_CURSOR_IBEAM);

            // Get char pressed (unicode character) on the queue
            int key = GetCharPressed();

            // Check if more characters can be added (maximum 8 characters)
            if (letterCount < 8)
            {
                // Add characters (Only allow alphabetical and numbers)
                if (((key >= 32) && (key <= 125)) && (key != '\\') && (key != '/') && (key != ':') && (key != '*') && (key != '?') && (key != '\"') && (key != '<') && (key != '>') && (key != '|'))
                {
                    playerName[letterCount] = (char)key;
                    playerName[letterCount + 1] = '\0'; // Add null terminator
                    letterCount++;
                }
            }

            // Delete button (backspace)
            if (IsKeyPressed(KEY_BACKSPACE))
            {
                if (letterCount > 0)
                {
                    letterCount--;
                    playerName[letterCount] = '\0';
                }
            }

            // Submit button (enter)
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

        if (mouseOnText && IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
        {
            PlayButtonClick();
        }
    }

    if (CheckCollisionPointRec(mouse, inputName[0]) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
    {
        printf("Tombol BACK TO MENU diklik!\n"); // Debugging
        PlayButtonClick();
        currentMenu = MENU_LEVEL_SELECT; // Kembali ke menu level
    }
    if (CheckCollisionPointRec(mouse, levelButtons[3]) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
    {
        printf("Tombol BACK TO MENU diklik!\n"); // Debugging
        PlayButtonClick();
        currentMenu = MENU_MAIN; // Kembali ke menu level
    }


    else if (currentMenu == MENU_LEADERBOARD)
    {
        if (IsKeyPressed(KEY_BACKSPACE))
        {
            currentMenu = MENU_MAIN;
        }
    }
}

// 🔹 Gambar Menu
void DrawMainMenu()
{
    ClearBackground((Color){30, 0, 60, 255});
    DrawBackground();
    Vector2 mouse = GetMousePosition();

    if (currentMenu == MENU_MAIN)
    {
        DrawTitle();

        const char *buttonTexts[] = {"START GAME", "LEADERBOARD", "EXIT GAME"};

        for (int i = 0; i < 3; i++)
        {
            Color buttonColor;
            if (i == 0)
                buttonColor = CheckCollisionPointRec(mouse, buttons[i]) ? GREEN : LIGHTGRAY;
            else if (i == 1)
                buttonColor = CheckCollisionPointRec(mouse, buttons[i]) ? BLUE : LIGHTGRAY;
            else
                buttonColor = CheckCollisionPointRec(mouse, buttons[i]) ? (Color){198, 60, 60, 255} : LIGHTGRAY;

            DrawRectangleRec(buttons[i], buttonColor);

            // Center text in button
            int textWidth = MeasureText(buttonTexts[i], 30);
            int textX = buttons[i].x + (buttons[i].width - textWidth) / 2;
            int textY = buttons[i].y + (buttons[i].height - 30) / 2;

            DrawText(buttonTexts[i], textX, textY, 30, BLACK);
        }

        Color soundColor = CheckCollisionPointRec(mouse, buttons[3]) ? (Color){100, 220, 255, 255} : YELLOW;
        DrawRectangleRec(buttons[3], soundColor);
        DrawText(soundOn ? "SOUND ON" : "SOUND OFF", buttons[3].x + 10, buttons[3].y + 10, 20, BLACK);
    }
    else if (currentMenu == MENU_LEVEL_SELECT)
    {
        DrawRainbowText("SELECT LEVEL", SCREEN_WIDTH / 2, 150, 45);

        // 🔹 Pemilihan Level: EASY, MEDIUM, HARD
        const char *levelText[] = {"EASY", "MEDIUM", "HARD"};
        Color levelColors[] = {GREEN, ORANGE, RED};

        for (int i = 0; i < 3; i++)
        {
            Color color = CheckCollisionPointRec(mouse, levelButtons[i]) ? levelColors[i] : LIGHTGRAY;
            DrawRectangleRec(levelButtons[i], color);

            // **Menghitung posisi teks agar tepat di tengah tombol**
            int textWidth = MeasureText(levelText[i], 30);
            int textX = levelButtons[i].x + (levelButtons[i].width / 2) - (textWidth / 2);
            int textY = levelButtons[i].y + (levelButtons[i].height / 2) - 15; // 15 untuk menyesuaikan posisi vertikal

            DrawText(levelText[i], textX, textY, 30, BLACK);
        }

        // Gambar tombol "BACK"
        Color backColor = CheckCollisionPointRec(mouse, levelButtons[3]) ? RED : LIGHTGRAY;
        DrawRectangleRec(levelButtons[3], backColor);
        DrawText("BACK", levelButtons[3].x + 20, levelButtons[3].y + 10, 20, BLACK);
    }
    else if (currentMenu == MENU_NAME_INPUT)
    {
        DrawRainbowText("ENTER YOUR NAME", SCREEN_WIDTH / 2, 150, 45);

        // Draw text box
        DrawRectangleRec(textBox, LIGHTGRAY);
        DrawRectangleLines(textBox.x, textBox.y, textBox.width, textBox.height,
                           mouseOnText ? RED : DARKGRAY);

        DrawText(playerName, textBox.x + 10, textBox.y + 15, 30, BLACK);

        // Draw blinking cursor
        if (mouseOnText)
        {
            if (letterCount < MAX_NAME_LENGTH)
            {
                // Draw cursor at the end of the text
                if (((int)(GetTime() * 2) % 2) == 0)
                {
                    DrawText("_", textBox.x + 10 + MeasureText(playerName, 30), textBox.y + 15, 30, BLACK);
                }
            }
        }

        DrawText("Press ENTER to confirm", textBox.x + 5, textBox.y + 60, 20, WHITE);
        DrawText("Press BACKSPACE to ERASE", textBox.x + 5, textBox.y + 90, 20, WHITE);

        // Draw back to main menu button
        Color backToMainColor = CheckCollisionPointRec(mouse, inputName[0]) ? RED : LIGHTGRAY;
        DrawRectangleRec(inputName[0], backToMainColor);
        DrawText("BACK TO MENU", inputName[0].x + 5, inputName[0].y + 10, 20, BLACK);
    }
    else if (currentMenu == MENU_LEADERBOARD)
    {
        static LeaderboardEntry leaderboard[MAX_PLAYERS];
        static bool leaderboardLoaded = false;

        if (!leaderboardLoaded)
        {
            LoadLeaderboard(leaderboard);
            leaderboardLoaded = true;
        }

        // Handle scrolling with mouse wheel
        leaderboardScrollOffset -= (GetMouseWheelMove() * SCROLL_SPEED);

        // Limit scrolling
        int maxScroll = (MAX_LEADERBOARD_ENTRIES * 30) - 380; // Calculate based on entries and visible area
        if (leaderboardScrollOffset < 0)
            leaderboardScrollOffset = 0;
        if (maxScroll > 0 && leaderboardScrollOffset > maxScroll)
            leaderboardScrollOffset = maxScroll;

        // Check for refresh button click
        Vector2 mousePos = GetMousePosition();
        Rectangle refreshButton = {750, 60, 120, 30};
        if (CheckCollisionPointRec(mousePos, refreshButton) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
        {
            LoadLeaderboard(leaderboard); // Reload leaderboard data
            PlayButtonClick();            // Add sound feedback
        }

        DrawLeaderboardMenu(leaderboard, MAX_LEADERBOARD_ENTRIES, leaderboardScrollOffset);
    }
}

// 🔹 Getter dan Setter
bool IsExitGame() { return exitGame; }
bool IsStartGame() { return startGame; }
int GetSelectedLevel() { return selectedLevel; }
const char *GetPlayerName() { return playerName; }
void SetStartGame(bool value) { startGame = value; }
void ToggleSound()
{
    soundOn = !soundOn;
    ToggleMusic();
}
bool IsSoundOn() { return soundOn; }