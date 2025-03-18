#include "mainmenu.h"
#include <stdbool.h>

int main()
{
    InitWindow(1000, 650, "Break Bricks - Main Menu");
    InitMainMenu();

    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(BLACK);

        UpdateMainMenu(); // Logic menu berjalan terus
        DrawMainMenu();   // Gambar menu

        EndDrawing();

        // Periksa jika exitGame sudah diaktifkan
        if (IsExitGame())
        {
            CloseWindow();
            break; // Keluar dari loop utama
        }

        if (GetMenuState() == MENU_LEVEL)
        {
            int level = GetSelectedLevel();
            if (level > 0)
            {
                // Mulai game di level yang dipilih
                CloseWindow(); // Buat contoh, window ditutup dulu
            }
        }
    }

    CloseWindow();
    return 0;
}