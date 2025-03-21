#ifndef MAINMENU_H
#define MAINMENU_H

#include <stdbool.h>

// Menu state enum
typedef enum
{
    MENU_MAIN,
    MENU_LEVEL_SELECT
} MenuState;

// Fungsi-fungsi utama menu
void InitMainMenu();
void UpdateMainMenu();
void DrawMainMenu();

bool IsExitGame();
bool IsStartGame();
int GetSelectedLevel();
void ToggleSound();
bool IsSoundOn();
void SetStartGame(bool value); // Tambahan jika pakai SetStartGame()

#endif
