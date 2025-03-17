#include "mainmenu.h"
#include <raylib.h>
#include <stdio.h>

// Variabel internal buat state menu
static bool startGame = false;
static bool exitGame = false;

// Navigasi menu
static int selectedOption = 0; // 0 = Start Game, 1 = Exit Game

// Posisi dan ukuran menu item
Rectangle startRect = {350, 350, 300, 40};
Rectangle exitRect = {350, 400, 300, 40};

void InitMainMenu(void)
{
    startGame = false;
    exitGame = false;
    selectedOption = 0;
}

void UpdateMainMenu(void)
{
    // Navigasi pakai keyboard
    if (IsKeyPressed(KEY_DOWN))
    {
        selectedOption++;
        if (selectedOption > 1)
            selectedOption = 0;
    }
    if (IsKeyPressed(KEY_UP))
    {
        selectedOption--;
        if (selectedOption < 0)
            selectedOption = 1;
    }

    // Navigasi pakai mouse (hover)
    Vector2 mousePoint = GetMousePosition();

    if (CheckCollisionPointRec(mousePoint, startRect))
    {
        selectedOption = 0;
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
        {
            startGame = true;
        }
    }

    if (CheckCollisionPointRec(mousePoint, exitRect))
    {
        selectedOption = 1;
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
        {
            exitGame = true;
        }
    }

    // Enter buat pilih opsi yg lagi dipilih
    if (IsKeyPressed(KEY_ENTER))
    {
        if (selectedOption == 0)
        {
            startGame = true;
        }
        else if (selectedOption == 1)
        {
            exitGame = true;
        }
    }
}

void DrawMainMenu(void)
{
    ClearBackground(WHITE); // Background putih

    // Judul "BREAK BRICKS" warna-warni elegan
    int x = 300;
    int y = 150;
    int fontSize = 60;

    DrawTextEx(GetFontDefault(), "B", (Vector2){x, y}, fontSize, 2, (Color){231, 76, 60, 255});        // Red soft
    DrawTextEx(GetFontDefault(), "R", (Vector2){x + 35, y}, fontSize, 2, (Color){241, 196, 15, 255});  // Yellow soft
    DrawTextEx(GetFontDefault(), "E", (Vector2){x + 70, y}, fontSize, 2, (Color){46, 204, 113, 255});  // Green soft
    DrawTextEx(GetFontDefault(), "A", (Vector2){x + 105, y}, fontSize, 2, (Color){52, 152, 219, 255}); // Blue soft
    DrawTextEx(GetFontDefault(), "K", (Vector2){x + 140, y}, fontSize, 2, (Color){155, 89, 182, 255}); // Purple soft

    DrawTextEx(GetFontDefault(), " ", (Vector2){x + 175, y}, fontSize, 2, BLACK);

    DrawTextEx(GetFontDefault(), "B", (Vector2){x + 190, y}, fontSize, 2, (Color){231, 76, 60, 255});
    DrawTextEx(GetFontDefault(), "R", (Vector2){x + 225, y}, fontSize, 2, (Color){241, 196, 15, 255});
    DrawTextEx(GetFontDefault(), "I", (Vector2){x + 260, y}, fontSize, 2, (Color){46, 204, 113, 255});
    DrawTextEx(GetFontDefault(), "C", (Vector2){x + 295, y}, fontSize, 2, (Color){52, 152, 219, 255});
    DrawTextEx(GetFontDefault(), "K", (Vector2){x + 330, y}, fontSize, 2, (Color){155, 89, 182, 255});
    DrawTextEx(GetFontDefault(), "S", (Vector2){x + 365, y}, fontSize, 2, (Color){241, 196, 15, 255});

    // Menu Item: START GAME
    Color startColor = (selectedOption == 0) ? DARKGRAY : BLACK;
    DrawRectangleRec(startRect, (selectedOption == 0) ? Fade(LIGHTGRAY, 0.5f) : WHITE);
    DrawText("START GAME", startRect.x + 20, startRect.y + 8, 25, startColor);

    // Menu Item: EXIT GAME
    Color exitColor = (selectedOption == 1) ? DARKGRAY : BLACK;
    DrawRectangleRec(exitRect, (selectedOption == 1) ? Fade(LIGHTGRAY, 0.5f) : WHITE);
    DrawText("EXIT GAME", exitRect.x + 20, exitRect.y + 8, 25, exitColor);
}

void UnloadMainMenu(void)
{
    // Kosongin kalau ada asset khusus
}

bool IsStartGame(void)
{
    return startGame;
}

bool IsExitGame(void)
{
    return exitGame;
}
