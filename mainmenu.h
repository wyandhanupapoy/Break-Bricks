// Nama Pembuat: Muhammad Brata Hadinata
// Nama Fitur   : mainmenu.h
// Deskripsi    : Header file untuk mengatur Main Menu game "Break Bricks".
//                File ini berisi deklarasi tipe data dan fungsi-fungsi yang berkaitan
//                dengan tampilan dan navigasi menu utama, termasuk pengaturan game,
//                input nama pemain, pemilihan level permainan, leaderboard, dan pengaturan suara.

#ifndef MAINMENU_H // Mencegah agar file ini tidak di-include lebih dari sekali saat kompilasi
#define MAINMENU_H

#include "raylib.h" // Library grafis dan input yang digunakan dalam game, termasuk untuk menggambar menu, mendeteksi input, dan memutar suara

// ==================================================
// ENUM UNTUK MENYIMPAN STATE/PILIHAN MENU
// ==================================================

// Enum ini berfungsi untuk mendefinisikan berbagai state (keadaan) menu yang ada di game.
// Digunakan untuk menentukan tampilan menu mana yang sedang aktif pada saat tertentu.
typedef enum
{
    MENU_MAIN,         // State untuk menu utama, yang menampilkan pilihan seperti "Start Game", "Leaderboard", "Settings", "Info", dan "Exit"
    MENU_LEVEL_SELECT, // State untuk menu pemilihan level game, misalnya: Level 1, Level 2, Level 3
    MENU_NAME_INPUT,   // State untuk menu input nama pemain sebelum memulai permainan
    MENU_LEADERBOARD,  // State untuk menu leaderboard, menampilkan daftar skor tertinggi dari para pemain
    MENU_SETTINGS,     // State untuk menu pengaturan game, misalnya: mengatur suara, menghapus skor, dan pengaturan lainnya
    MENU_INFO          // State untuk menu informasi tentang game, seperti penjelasan game, nama pembuat, atau cara bermain
} MenuState;

// ==================================================
// DEKLARASI FUNGSI-FUNGSI UTAMA UNTUK MENU
// ==================================================

// Fungsi untuk menginisialisasi semua variabel yang diperlukan untuk menu utama.
// Dipanggil di awal program setelah window dibuat.
void InitMainMenu();

// Fungsi untuk meng-update logika menu utama.
// Di sini dilakukan pengecekan input keyboard atau mouse untuk navigasi menu dan pemilihan item menu.
void UpdateMainMenu();

// Fungsi untuk menggambar menu utama ke layar.
// Berisi perintah untuk menampilkan background, tombol, teks, dan elemen visual lainnya di menu utama.
void DrawMainMenu();

// Fungsi untuk menggambar menu versi mini (opsional).
// Biasanya digunakan saat permainan di-pause, menampilkan menu kecil tanpa keluar dari game utama.
void DrawMainMenuMini();

// Fungsi untuk meng-update logika menu versi mini.
// Digunakan untuk mendeteksi input ketika menu mini aktif.
void UpdateMainMenuMini();

// ==================================================
// DEKLARASI FUNGSI-FUNGSI KONTROL GAME
// ==================================================

// Fungsi untuk mengecek apakah pemain memilih "Exit Game" dari menu.
// Return true jika pemain memilih keluar, sehingga game akan ditutup di game loop utama.
bool IsExitGame();

// Fungsi untuk mengecek apakah pemain memilih "Start Game" dari menu.
// Return true jika pemain memilih untuk memulai permainan, yang biasanya digunakan untuk transisi dari menu ke gameplay.
bool IsStartGame();

// Fungsi untuk mendapatkan level permainan yang dipilih oleh pemain di menu LEVEL SELECT.
// Return nilai level dalam bentuk angka, misalnya 1, 2, atau 3.
int GetSelectedLevel();

// Fungsi untuk mengatur status mulai game.
// Parameter value bernilai true jika permainan dimulai, dan false jika tidak.
void SetStartGame(bool value);

// Fungsi untuk mengambil nama pemain yang diinput pada menu NAME INPUT.
// Return berupa pointer ke string (const char *) yang menyimpan nama pemain.
const char *GetPlayerName();

// ==================================================
// DEKLARASI FUNGSI-FUNGSI UNTUK PENGATURAN SUARA
// ==================================================

// Fungsi untuk mengaktifkan atau menonaktifkan suara pada game.
// Fungsi ini biasanya digunakan di menu pengaturan (settings) oleh pemain untuk mematikan atau menyalakan suara.
void ToggleSound();

// Fungsi untuk mengecek apakah suara dalam keadaan aktif atau tidak.
// Return true jika suara aktif (on), dan false jika suara dalam keadaan mati (off).
bool IsSoundOn();

#endif // Akhir dari preprocessor directive #ifndef
