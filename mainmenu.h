#ifndef MAINMENU_H
#define MAINMENU_H

#include "raylib.h"
#include <stdbool.h>

typedef enum {
    MENU_MAIN,
    MENU_LEVEL
} MenuState;

// Deklarasi fungsi
void InitMainMenu(void);
void UpdateMainMenu(void);
void DrawMainMenu(void);
void UpdateLevelMenu(void);
void DrawLevelMenu(void);

#endif // MAINMENU_H
