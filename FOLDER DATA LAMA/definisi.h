// definisi.h - File berisi definisi konstanta dan struktur data yang digunakan game
#ifndef DEFINISI_H
#define DEFINISI_H

// Definisi ukuran layar dan area permainan
#define BARIS 25
#define KOLOM 40
#define LEBAR_LAYAR 60
#define AREA_GAME_MULAI 15 // Kolom dimana area game dimulai

// Definisi untuk paddle
#define PADDLE_PANJANG 5

// Definisi untuk blok
#define JUMLAH_BLOK_BARIS 3
#define JUMLAH_BLOK_KOLOM 8
#define TOTAL_BLOK (JUMLAH_BLOK_BARIS * JUMLAH_BLOK_KOLOM)

// Struktur untuk menyimpan data permainan
typedef struct {
    int skor;
    int level;
    int kecepatan;
    char nama[50];
    int waktu_bermain;
    int nyawa;
    int blok_tersisa;
} DataPermainan;

// Struktur untuk paddle
typedef struct {
    int x;
    int y;
    int panjang;
    char bentuk;
} Paddle;

// Struktur untuk bola
typedef struct {
    int x;
    int y;
    int dx; // Kecepatan horizontal (arah X)
    int dy; // Kecepatan vertikal (arah Y)
    char bentuk;
} Bola;

// Struktur untuk blok
typedef struct {
    int x;
    int y;
    int aktif;
    char bentuk;
    int nilai; // Nilai poin saat blok dihancurkan
} Blok;

#endif // DEFINISI_H