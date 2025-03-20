#ifndef BLOCK_H
#define BLOCK_H

#include <raylib.h>  // Mengimpor Raylib untuk menggambar blok dan mendeteksi tabrakan

// Konstanta untuk menentukan jumlah baris dan kolom blok dalam permainan
#define BLOCK_ROWS 5
#define BLOCK_COLS 10

// Ukuran dan jarak antar blok dalam piksel
#define BLOCK_WIDTH 75
#define BLOCK_HEIGHT 25
#define BLOCK_SPACING 5

// Struktur data untuk merepresentasikan sebuah blok dalam permainan
typedef struct {
    Rectangle rect;  // Posisi dan ukuran blok
    bool active;     // Status blok (aktif atau sudah dihancurkan)
    Color color;     // Warna blok
    int colorIndex;  // Indeks warna untuk perubahan warna berdasarkan level
} Block;

// Fungsi untuk menginisialisasi blok berdasarkan level yang dipilih
void InitBlocks(Block blocks[BLOCK_ROWS][BLOCK_COLS], int level);

// Fungsi untuk menggambar semua blok yang masih aktif
void DrawBlocks(Block blocks[BLOCK_ROWS][BLOCK_COLS]);

// Fungsi untuk mengecek apakah bola bertabrakan dengan suatu blok
bool CheckBallBlockCollision(Vector2 ballPosition, float ballRadius, Rectangle blockRect);

// Fungsi untuk mengecek apakah semua blok telah dihancurkan
bool AllBlocksDestroyed(Block blocks[BLOCK_ROWS][BLOCK_COLS]);

#endif // BLOCK_H
