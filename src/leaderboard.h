/*
Nama Pembuat:   Wyandhanu Maulidan Nugraha
Nama Fitur:     Leaderboard (Linked List)
Deskripsi:      Fitur leaderboard untuk menyimpan data pemain dan menampilkannya dalam bentuk tabel
                menggunakan implementasi linked list.
*/
#ifndef LEADERBOARD_H
#define LEADERBOARD_H

#include <raylib.h>
#include <stdbool.h> // Untuk bool

#define MAX_NAME_LENGTH 20
#define MAX_LEADERBOARD_ENTRIES 10 // Batas maksimal entri yang disimpan dan ditampilkan (bisa disesuaikan)
#define LEADERBOARD_FILE "src/leaderboard.dat"
#define SCROLL_SPEED 20 // Kecepatan scroll di menu leaderboard

// Warna kustom
#define SILVER (Color){192, 192, 192, 255}
#define BRONZE (Color){205, 127, 50, 255}

// Struktur untuk satu node dalam linked list leaderboard
typedef struct LeaderboardNode {
    char name[MAX_NAME_LENGTH];
    int score;
    float time;
    int level;
    char status[10]; // "WIN" atau "GAME OVER"
    struct LeaderboardNode* next;
} LeaderboardNode;

// Fungsi Inisialisasi & Pembersihan
void InitLeaderboard(); // Menginisialisasi leaderboard (mengosongkan list)
void FreeLeaderboard(); // Membersihkan semua entri dari memori

// Fungsi Operasi Leaderboard
void AddEntryToLeaderboard(const char *name, int score, float time, int level, const char *status);
void SaveLeaderboard(const char *filename);
void LoadLeaderboard(const char *filename);
int GetLeaderboardCount(); // Mendapatkan jumlah entri saat ini

// Fungsi Tampilan
void DrawLeaderboardInfo(int x, int y, int maxEntriesToDisplay); // Menggambar leaderboard ringkas (misalnya di layar game over/win)
void DrawLeaderboardMenuScreen(int scrollOffset); // Menggambar layar menu leaderboard lengkap

// Fungsi untuk Tekstur Medali (tetap sama)
void LoadMedalTextures(void);
void UnloadMedalTextures(void);
void SetMedalScale(float scale); // Opsional, jika ingin mengatur skala dari luar
void SetMedalSize(int width, int height); // Opsional, jika ingin mengatur ukuran dari luar

static void FreeLeaderboardRecursive(LeaderboardNode* node);

#endif // LEADERBOARD_H