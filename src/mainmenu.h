// Nama Pembuat: Muhammad Brata Hadinata
// Nama Fitur: mainmenu.h
// Deskripsi: Header file untuk mengatur Main Menu game "Break Bricks".
//            Berisi deklarasi tipe MenuState, fungsi-fungsi navigasi menu,
//            kontrol mulai/keluar game, input nama pemain, pemilihan level, serta pengaturan suara.
#ifndef MAINMENU_H
#define MAINMENU_H

#include "raylib.h"
#include "game_state.h" // Tambahkan include untuk GameState

typedef enum
{
    MENU_MAIN,
    MENU_LEVEL_SELECT,
    MENU_NAME_INPUT,
    MENU_LEADERBOARD,
    MENU_SETTINGS,
    MENU_INFO
} MenuState;

// 🔹 Fungsi utama menu
void InitMainMenu();
void UpdateMainMenu();
void DrawMainMenu();
void DrawMainMenuMini(GameState state);
void UpdateMainMenuMini(GameState *state);

// 🔹 Kontrol game
bool IsExitGame();
bool IsStartGame();
int GetSelectedLevel();
void SetStartGame(bool value);
const char *GetPlayerName();

// 🔹 Kontrol suara
void ToggleSound();
bool IsSoundOn();

#endif