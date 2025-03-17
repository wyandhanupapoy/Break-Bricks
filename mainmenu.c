#include "mainmenu.h"
#include <raylib.h>
#include <stdio.h>

// Variabel internal buat state menu
static bool startGame = false;
static bool exitGame = false;

void InitMainMenu(void)
{
    startGame = false;
    exitGame = false;
}

void UpdateMainMenu(void)
{
    // Navigasi tombol di menu
    if (IsKeyPressed(KEY_ENTER))
    {
        startGame = true; // Enter = mulai game
    }

    if (IsKeyPressed(KEY_ESCAPE))
    {
        exitGame = true; // Escape = keluar dari game
    }
}

void DrawMainMenu(void)
{
    ClearBackground(WHITE); // Background putih

    // Judul "BREAK BRICKS" warna-warni (elegan)
    int x = 300;
    int y = 150;
    int fontSize = 60;

    DrawTextEx(GetFontDefault(), "B", (Vector2){x, y}, fontSize, 2, (Color){231, 76, 60, 255});        // Red soft
    DrawTextEx(GetFontDefault(), "R", (Vector2){x + 35, y}, fontSize, 2, (Color){241, 196, 15, 255});  // Yellow soft
    DrawTextEx(GetFontDefault(), "E", (Vector2){x + 70, y}, fontSize, 2, (Color){46, 204, 113, 255});  // Green soft
    DrawTextEx(GetFontDefault(), "A", (Vector2){x + 105, y}, fontSize, 2, (Color){52, 152, 219, 255}); // Blue soft
    DrawTextEx(GetFontDefault(), "K", (Vector2){x + 140, y}, fontSize, 2, (Color){155, 89, 182, 255}); // Purple soft

    DrawTextEx(GetFontDefault(), " ", (Vector2){x + 175, y}, fontSize, 2, BLACK); // Space separator

    DrawTextEx(GetFontDefault(), "B", (Vector2){x + 190, y}, fontSize, 2, (Color){231, 76, 60, 255});
    DrawTextEx(GetFontDefault(), "R", (Vector2){x + 225, y}, fontSize, 2, (Color){241, 196, 15, 255});
    DrawTextEx(GetFontDefault(), "I", (Vector2){x + 260, y}, fontSize, 2, (Color){46, 204, 113, 255});
    DrawTextEx(GetFontDefault(), "C", (Vector2){x + 295, y}, fontSize, 2, (Color){52, 152, 219, 255});
    DrawTextEx(GetFontDefault(), "K", (Vector2){x + 330, y}, fontSize, 2, (Color){155, 89, 182, 255});
    DrawTextEx(GetFontDefault(), "S", (Vector2){x + 365, y}, fontSize, 2, (Color){241, 196, 15, 255});

    // Teks navigasi (Hitam)
    DrawText("Press ENTER to Start", 350, 350, 25, BLACK);
    DrawText("Press ESC to Exit", 350, 400, 25, DARKGRAY);
}

void UnloadMainMenu(void)
{
    // Bersihin resource kalau ada (misal texture, font, dll)
}

bool IsStartGame(void)
{
    return startGame;
}

bool IsExitGame(void)
{
    return exitGame;
}
