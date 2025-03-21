#ifndef MAINMENU_H
#define MAINMENU_H

#include "raylib.h"

typedef enum {
    MENU_MAIN,
    MENU_LEVEL_SELECT
} MenuState;

// 🔹 Fungsi utama menu
void InitMainMenu();
void UpdateMainMenu();
void DrawMainMenu();

// 🔹 Kontrol game
bool IsExitGame();
bool IsStartGame();
int GetSelectedLevel();
void SetStartGame(bool value);

// 🔹 Kontrol suara
void ToggleSound();
bool IsSoundOn();

#endif
