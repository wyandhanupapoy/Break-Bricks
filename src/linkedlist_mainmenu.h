#ifndef MAIN_H
#define MAIN_H

#include "raylib.h"

// Menyimpan status menu
typedef enum
{
    MENU_MAIN,
    MENU_LEVEL_SELECT,
    MENU_LEADERBOARD,
    MENU_SETTINGS,
    MENU_INFO
} MenuState;

// Struktur untuk tombol menu
typedef struct MenuButton
{
    Rectangle rect;
    char label[50];
    struct MenuButton *next;
} MenuButton;

// Deklarasi fungsi-fungsi
void InitMainMenu();
void DrawMainMenu();
void DrawLevelMenu();
void UpdateMainMenu();
bool ShouldExitGame();
MenuState GetCurrentMenu();
const char *GetPlayerName();
void SetPlayerName(const char *name);

#endif // MAIN_H
