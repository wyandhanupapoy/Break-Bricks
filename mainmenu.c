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
    ClearBackground(DARKBLUE);

    DrawText("BREAK BRICKS", 320, 150, 50, RAYWHITE);
    DrawText("Press ENTER to Start", 350, 300, 25, RAYWHITE);
    DrawText("Press ESC to Exit", 350, 350, 25, GRAY);
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
