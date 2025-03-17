#include "mainmenu.h"
#include <raylib.h>

#define SCREEN_WIDTH 1000
#define SCREEN_HEIGHT 650

int main(void)
{
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "BREAK BRICKS - Main Menu");
    SetTargetFPS(60);

    InitMainMenu(); // Init state awal menu

    while (!WindowShouldClose())
    {
        // Update menu logic
        UpdateMainMenu();

        // Cek apakah user milih mulai game / keluar
        if (IsStartGame())
        {
            // Kalo udah ada logic ke game, disini kamu redirect
            // Misal, panggil GameLoop(); atau pindah ke scene lain
            // Sekarang cuma keluar window dulu buat contoh
            CloseWindow();
            // Bisa return nilai khusus buat ke game, nanti diatur
            return 1;
        }

        if (IsExitGame())
        {
            CloseWindow();
            return 0;
        }

        // Draw main menu
        BeginDrawing();
        DrawMainMenu();
        EndDrawing();
    }

    UnloadMainMenu(); // Clean up resource menu
    CloseWindow();

    return 0;
}