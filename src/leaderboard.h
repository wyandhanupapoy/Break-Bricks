/*
 * Nama Pembuat:    Wyandhanu Maulidan Nugraha
 * Nama Fitur:      Leaderboard (Linked List) - Header File
 * Deskripsi:       File header untuk fitur leaderboard. Mendefinisikan struktur data
 *                  dan mendeklarasikan fungsi-fungsi yang terkait dengan pengelolaan
 *                  dan penampilan leaderboard.
 */

#ifndef LEADERBOARD_H // Pengawal Inklusi (Include Guard) - Mencegah duplikasi definisi jika file ini di-include berkali-kali
#define LEADERBOARD_H

#include <raylib.h>  // Diperlukan untuk tipe data seperti Texture2D, Color, dll.
#include <stdbool.h> // Diperlukan untuk tipe data boolean (true/false)

// === Konstanta ===
// Konstanta ini mendefinisikan batas-batas dan nama file yang digunakan oleh leaderboard.

#define MAX_NAME_LENGTH 20       // Panjang maksimum nama pemain yang bisa disimpan.
#define MAX_LEADERBOARD_ENTRIES 100 // Jumlah entri maksimum yang akan disimpan dan ditampilkan di leaderboard.
                                 // Jika ada lebih dari 10 entri, hanya 10 teratas yang disimpan.
#define LEADERBOARD_FILE "assets/data_leaderboard/leaderboard.dat" // Path dan nama file tempat data leaderboard disimpan secara permanen.
                                                                   // Ekstensi .dat menandakan file data biner.
#define SCROLL_SPEED 20          // Kecepatan scroll saat melihat leaderboard di menu.

// === Warna Kustom ===
// Definisi warna kustom untuk medali, agar mudah digunakan.
#define SILVER (Color){192, 192, 192, 255} // Warna perak (abu-abu terang)
#define BRONZE (Color){205, 127, 50, 255}  // Warna perunggu

// === Struktur Data untuk Entri Leaderboard ===
// Struktur `LeaderboardNode` mendefinisikan bagaimana setiap entri skor pemain disimpan.
// Ini adalah "node" dalam linked list kita.
typedef struct LeaderboardNode {
    char name[MAX_NAME_LENGTH]; // Nama pemain. Array karakter (string) dengan panjang maksimum MAX_NAME_LENGTH.
    int score;                  // Skor yang dicapai pemain.
    float time;                 // Waktu yang ditempuh pemain (dalam detik).
    int level;                  // Level terakhir yang dicapai pemain.
    char status[10];            // Status akhir permainan ("WIN" atau "GAME OVER").
    struct LeaderboardNode* next; // Pointer ke entri (node) berikutnya dalam linked list.
                                  // Jika ini adalah entri terakhir, 'next' akan bernilai NULL.
} LeaderboardNode;

// === Deklarasi Fungsi ===
// Fungsi-fungsi ini adalah antarmuka publik dari modul leaderboard.
// Bagian lain dari game akan memanggil fungsi-fungsi ini untuk berinteraksi dengan leaderboard.

// --- Fungsi Inisialisasi & Pembersihan ---
void InitLeaderboard(); // Fungsi untuk menginisialisasi sistem leaderboard.
                        // Biasanya dipanggil saat game pertama kali dimulai.
                        // Ini juga akan mencoba memuat data leaderboard dari file.
void FreeLeaderboard(); // Fungsi untuk membersihkan semua entri leaderboard dari memori.
                        // Penting untuk mencegah kebocoran memori (memory leak).
                        // Dipanggil saat game ditutup.

// --- Fungsi Operasi Leaderboard ---
void AddEntryToLeaderboard(const char *name, int score, float time, int level, const char *status);
                        // Fungsi untuk menambahkan entri baru ke leaderboard.
                        // Entri akan disisipkan secara terurut berdasarkan skor (tertinggi dulu),
                        // lalu waktu (tercepat dulu), dan status (WIN lebih dulu dari GAME OVER).
void SaveLeaderboard(const char *filename);
                        // Fungsi untuk menyimpan data leaderboard saat ini ke dalam file.
                        // Ini memastikan skor tetap ada meskipun game ditutup dan dibuka lagi.
void LoadLeaderboard(const char *filename);
                        // Fungsi untuk memuat data leaderboard dari file ke dalam memori.
                        // Biasanya dipanggil oleh InitLeaderboard().
int GetLeaderboardCount();  // Fungsi untuk mendapatkan jumlah entri yang ada di leaderboard saat ini.

// --- Fungsi Tampilan ---
void DrawLeaderboardInfo(int x, int y, int maxEntriesToDisplay);
                        // Fungsi untuk menggambar versi ringkas dari leaderboard.
                        // Berguna untuk ditampilkan di layar game over atau game win.
                        // 'maxEntriesToDisplay' menentukan berapa banyak entri teratas yang ditampilkan.
void DrawLeaderboardMenuScreen(int scrollOffset);
                        // Fungsi untuk menggambar layar menu leaderboard yang lengkap dan interaktif.
                        // 'scrollOffset' digunakan untuk menggeser tampilan jika entri lebih banyak dari area layar.

// --- Fungsi untuk Tekstur Medali ---
// Medali (emas, perak, perunggu) ditampilkan untuk 3 peringkat teratas.
void LoadMedalTextures(void);   // Memuat gambar (tekstur) medali dari file ke memori.
void UnloadMedalTextures(void); // Melepaskan tekstur medali dari memori saat tidak lagi dibutuhkan.
void SetMedalScale(float scale); // Mengatur skala (ukuran) tampilan medali.
void SetMedalSize(int width, int height); // Mengatur dimensi (lebar dan tinggi) medali secara spesifik.

#endif // LEADERBOARD_H