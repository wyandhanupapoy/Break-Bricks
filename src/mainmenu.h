// Nama Pembuat: Muhammad Brata Hadinata
// Nama Fitur: mainmenu.h
// Deskripsi: Header file untuk mengatur Main Menu game "Break Bricks".
//            Berisi deklarasi tipe MenuScreenType, struktur MenuItem dan MenuScreen,
//            fungsi-fungsi navigasi menu, kontrol mulai/keluar game,
//            input nama pemain, pemilihan level, serta pengaturan suara.
//            Modifikasi: Menggunakan linked list dinamis untuk menu.

#ifndef MAINMENU_H
#define MAINMENU_H

#include "raylib.h"
#include "game_state.h" // Tambahkan include untuk GameState

#define MAX_NAME_LENGTH_INPUT 8 // Maksimal karakter nama yang bisa diinput

// Enum untuk mengidentifikasi tipe layar menu, berguna untuk logika khusus
typedef enum {
    MENU_TYPE_MAIN,
    MENU_TYPE_LEVEL_SELECT,
    MENU_TYPE_NAME_INPUT,
    MENU_TYPE_LEADERBOARD,
    MENU_TYPE_SETTINGS,
    MENU_TYPE_INFO,
    MENU_TYPE_NONE // Untuk kasus di mana tidak ada tipe spesifik atau untuk error handling
} MenuScreenType;

// Forward declaration
typedef struct MenuItem MenuItem;
typedef struct MenuScreen MenuScreen;

// Tipe fungsi pointer untuk aksi item menu
typedef void (*MenuItemAction)(void);

// Struktur untuk item dalam menu (misalnya tombol)
struct MenuItem {
    char text[64];
    Rectangle rect;
    Color baseColor;
    Color hoverColor;
    Color textColor;
    MenuItemAction action;     // Fungsi yang akan dipanggil saat item diklik
    MenuScreen* targetScreen;  // Layar tujuan jika item ini adalah navigasi (opsional, bisa dihandle action)
    MenuItem* next;            // Pointer ke item berikutnya dalam linked list
};

// Struktur untuk sebuah layar menu
struct MenuScreen {
    char title[64];
    MenuScreenType type;        // Tipe layar menu
    MenuItem* itemsHead;        // Kepala linked list dari item-item menu di layar ini
    void (*drawScreenCustom)(Vector2 mousePos);   // Fungsi custom untuk menggambar konten khusus layar ini
    void (*updateScreenCustom)(Vector2 mousePos); // Fungsi custom untuk update logika khusus layar ini
    MenuScreen* parentScreen;   // Pointer ke layar menu induk (untuk navigasi "Back")
};

// 🔹 Fungsi utama menu (versi dinamis)
void InitDynamicMainMenu(void);
void UpdateDynamicMainMenu(void);
void DrawDynamicMainMenu(void);
void FreeDynamicMainMenu(void); // Untuk membersihkan memori

// Fungsi mini menu (tetap sama)
void DrawMainMenuMini(GameState state);
void UpdateMainMenuMini(GameState *state);

// 🔹 Kontrol game (tetap sama)
bool IsExitGame(void);
bool IsStartGame(void);
int GetSelectedLevel(void);
void SetStartGame(bool value);
const char *GetPlayerName(void);
MenuScreenType GetCurrentMenuScreenType(void); // Untuk mendapatkan tipe layar menu saat ini jika diperlukan

// 🔹 Kontrol suara (tetap sama)
void ToggleSound(void); // Implementasi ada di mainmenu.c atau sound.c, header di sini jika dipanggil dari mainmenu
bool IsSoundOn(void);   // Getter untuk status suara

#endif // MAINMENU_H