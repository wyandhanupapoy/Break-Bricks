// mainmenu.h
#ifndef MAINMENU_H
#define MAINMENU_H

#include "raylib.h"

#define SCROLL_SPEED 10
#define SILVER (Color){192, 192, 192, 255}  // Define silver color
#define BRONZE (Color){205, 127, 50, 255}   // Define bronze color

typedef enum {
    MENU_MAIN,
    MENU_LEVEL_SELECT,
    MENU_NAME_INPUT,
    MENU_LEADERBOARD
} MenuState;

// 🔹 Fungsi utama menu
void InitMainMenu();
void UpdateMainMenu();
void DrawMainMenu();
void DrawMainMenuMini();
void UpdateMainMenuMini();

// 🔹 Kontrol game
bool IsExitGame();
bool IsStartGame();
int GetSelectedLevel();
void SetStartGame(bool value);
const char* GetPlayerName();

// 🔹 Kontrol suara
void ToggleSound();
bool IsSoundOn();

#endif