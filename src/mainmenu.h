// mainmenu.h
#ifndef MAINMENU_H
#define MAINMENU_H

#include "raylib.h"

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