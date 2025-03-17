#ifndef MAINMENU_H
#define MAINMENU_H

#include <raylib.h>

// Fungsi init menu (opsional)
void InitMainMenu(void);

// Fungsi update dan logic menu
void UpdateMainMenu(void);

// Fungsi gambar menu
void DrawMainMenu(void);

// Fungsi buat bersihin resource (opsional)
void UnloadMainMenu(void);

// Fungsi buat ngecek kondisi: apakah start game atau exit
bool IsStartGame(void);
bool IsExitGame(void);

#endif
