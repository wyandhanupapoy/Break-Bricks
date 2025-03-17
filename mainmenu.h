#ifndef MAINMENU_H
#define MAINMENU_H

#include <raylib.h>

// Enum buat atur state menu
typedef enum {
    MENU_MAIN,
    MENU_LEVEL_SELECT
} MenuState;

// Fungsi-fungsi yang bisa diakses dari luar file ini
void InitMainMenu();                    // Inisialisasi menu utama
void UpdateMainMenu();                  // Update state & logic menu
void DrawMainMenu();                    // Gambar menu utama
MenuState GetMenuState();               // Cek kita di menu apa sekarang
int GetSelectedLevel();                 // Ambil level yang dipilih (kalau di menu level)

// Kalau perlu, tambahin fungsi lain di sini

#endif