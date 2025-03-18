#include "mainmenu.h"
#include "raylib.h"

int main()
{
    InitWindow(1000, 650, "Break Bricks - Main Menu");
    InitMainMenu();

    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(WHITE);

        UpdateMainMenu(); // Logic menu jalan terus
        DrawMainMenu();   // Gambar menu

        EndDrawing();

        // Contoh ngecek menu state
        if (GetMenuState() == MENU_LEVEL_SELECT)
        {
            int level = GetSelectedLevel();
            if (level > 0)
            {
                // Mulai game di level yang dipilih
                // Misalnya: StartGame(level);
                CloseWindow(); // Buat contoh, window ditutup dulu
            }
        }
    }

    CloseWindow();
    return 0;
}
