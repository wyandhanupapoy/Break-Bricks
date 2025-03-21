#include "mainmenu.h"
#include "sound.h"
#include "game_state.h"
#include "background.h"
#include "raylib.h"

// 🔹 Variabel Global
static MenuState currentMenu = MENU_MAIN;
static bool exitGame = false, startGame = false, soundOn = true;
static int selectedLevel = 0;

// 🔹 Tombol utama
static Rectangle buttons[] = {
    {350, 300, 320, 50},  // Start Game
    {350, 370, 320, 50},  // Exit Game
    {850, 600, 140, 40},  // Sound Toggle
};

// 🔹 Tombol level select
static Rectangle levelButtons[] = {
    {350, 250, 300, 50}, // Level Easy
    {350, 320, 300, 50}, // Level Medium
    {350, 390, 300, 50}, // Level Hard
    {20, 20, 100, 40},   // Back Button
};

// 🔹 Warna Pelangi
static Color rainbowColors[] = { RED, ORANGE, YELLOW, GREEN, BLUE, PURPLE };
static int rainbowSize = sizeof(rainbowColors) / sizeof(rainbowColors[0]);

// 🔹 Gambar Teks Pelangi dengan Spacing yang Lebih Presisi
void DrawRainbowText(const char *text, int centerX, int posY, int fontSize)
{
    int letterCount = 0;
    float totalWidth = 0;
    float letterWidths[256] = {0}; // Simpan ukuran tiap huruf

    // 🔹 Hitung total panjang teks & simpan lebar tiap huruf
    for (int i = 0; text[i] != '\0'; i++) {
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

// 🔹 Gambar Title "BREAK BRICKS"
void DrawTitle() {
    DrawRainbowText("BREAK BRICKS", SCREEN_WIDTH / 2, 150, 75);
}

// 🔹 Inisialisasi Menu
void InitMainMenu() {
    currentMenu = MENU_MAIN;
    exitGame = startGame = false;
    selectedLevel = 0;
    soundOn = true;
}

// 🔹 Update Menu
void UpdateMainMenu() {
    Vector2 mouse = GetMousePosition();

    if (currentMenu == MENU_MAIN) {
        if (CheckCollisionPointRec(mouse, buttons[0]) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
            PlayButtonClick();
            currentMenu = MENU_LEVEL_SELECT;
        }
        if (CheckCollisionPointRec(mouse, buttons[1]) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
            exitGame = true;
        }
        if (CheckCollisionPointRec(mouse, buttons[2]) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
            ToggleSound();
        }
    } else if (currentMenu == MENU_LEVEL_SELECT) {
        for (int i = 0; i < 3; i++) {
            if (CheckCollisionPointRec(mouse, levelButtons[i]) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
                selectedLevel = i + 1;
                startGame = true;
            }
        }
        if (CheckCollisionPointRec(mouse, levelButtons[3]) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
            currentMenu = MENU_MAIN;
        }
        if (IsKeyPressed(KEY_BACKSPACE)) {
            currentMenu = MENU_MAIN;
        }
    }
}

// 🔹 Gambar Menu
void DrawMainMenu() {
    ClearBackground((Color){30, 0, 60, 255});
    DrawBackground();
    Vector2 mouse = GetMousePosition();

    if (currentMenu == MENU_MAIN) {
        DrawTitle();
        
        Color startColor = CheckCollisionPointRec(mouse, buttons[0]) ? GREEN : LIGHTGRAY;
        DrawRectangleRec(buttons[0], startColor);
        DrawText("START GAME", buttons[0].x + 60, buttons[0].y + 10, 30, BLACK);

        Color exitColor = CheckCollisionPointRec(mouse, buttons[1]) ? (Color){198, 60, 60, 255} : LIGHTGRAY;
        DrawRectangleRec(buttons[1], exitColor);
        DrawText("EXIT GAME", buttons[1].x + 80, buttons[1].y + 10, 30, BLACK);

        Color soundColor = CheckCollisionPointRec(mouse, buttons[2]) ? (Color){100, 220, 255, 255} : YELLOW;
        DrawRectangleRec(buttons[2], soundColor);
        DrawText(soundOn ? "SOUND ON" : "SOUND OFF", buttons[2].x + 10, buttons[2].y + 10, 20, BLACK);

    } else if (currentMenu == MENU_LEVEL_SELECT) {
        DrawRainbowText("SELECT LEVEL", SCREEN_WIDTH / 2, 150, 45);

        // 🔹 Pemilihan Level: EASY, MEDIUM, HARD
        const char *levelText[] = { "EASY", "MEDIUM", "HARD" };
        Color levelColors[] = { GREEN, ORANGE, RED };

        for (int i = 0; i < 3; i++) {
            Color color = CheckCollisionPointRec(mouse, levelButtons[i]) ? levelColors[i] : LIGHTGRAY;
            DrawRectangleRec(levelButtons[i], color);
            
            // **Menghitung posisi teks agar tepat di tengah tombol**
            int textWidth = MeasureText(levelText[i], 30);
            int textX = levelButtons[i].x + (levelButtons[i].width / 2) - (textWidth / 2);
            int textY = levelButtons[i].y + (levelButtons[i].height / 2) - 15; // 15 untuk menyesuaikan posisi vertikal
            
            DrawText(levelText[i], textX, textY, 30, BLACK);
        }

        Color backColor = CheckCollisionPointRec(mouse, levelButtons[3]) ? RED : LIGHTGRAY;
        DrawRectangleRec(levelButtons[3], backColor);
        DrawText("BACK", levelButtons[3].x + 20, levelButtons[3].y + 10, 20, BLACK);
    }
}

// 🔹 Getter dan Setter
bool IsExitGame() { return exitGame; }
bool IsStartGame() { return startGame; }
int GetSelectedLevel() { return selectedLevel; }
void SetStartGame(bool value) { startGame = value; }
void ToggleSound() { soundOn = !soundOn; ToggleMusic(); }
bool IsSoundOn() { return soundOn; }
