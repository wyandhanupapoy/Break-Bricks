#include "level.h"
#include "raylib.h"
#include <stdlib.h>  // Untuk fungsi rand()
#include <time.h>    // Untuk seeding angka acak

// Fungsi untuk menginisialisasi blok berdasarkan level yang dipilih
void InitLevelBlocks(Block blocks[BLOCK_ROWS][BLOCK_COLS], int level) {
    srand(time(NULL));  // Seed angka acak agar variasi warna blok berbeda setiap permainan

    Color colors[3] = { DARKGRAY, BROWN, BEIGE };  // Daftar warna blok yang digunakan

    int maxColorIndex;
    if (level == 1) {
        maxColorIndex = 2;  // Hanya BEIGE (index 2)
    } else if (level == 2) {
        maxColorIndex = 1;  // Kombinasi BROWN (1) dan BEIGE (2)
    } else {
        maxColorIndex = 0;  // Kombinasi DARKGRAY (0), BROWN (1), dan BEIGE (2)
    }

    // Loop untuk menginisialisasi posisi dan warna setiap blok dalam grid
    for (int i = 0; i < BLOCK_ROWS; i++) {
        for (int j = 0; j < BLOCK_COLS; j++) {
            blocks[i][j].rect.x = j * (BLOCK_WIDTH + BLOCK_SPACING) + 15;  // Posisi X dengan jarak antar blok
            blocks[i][j].rect.y = i * (BLOCK_HEIGHT + BLOCK_SPACING) + 70; // Posisi Y dengan jarak antar blok
            blocks[i][j].rect.width = BLOCK_WIDTH;   // Lebar blok
            blocks[i][j].rect.height = BLOCK_HEIGHT; // Tinggi blok
            blocks[i][j].active = true;  // Setiap blok aktif saat awal permainan

            // Pilih warna acak dari daftar warna yang sesuai dengan level
            int randomIndex = rand() % (3 - maxColorIndex) + maxColorIndex;
            blocks[i][j].color = colors[randomIndex];
            blocks[i][j].colorIndex = randomIndex;
        }
    }
}

// Fungsi untuk memperbarui status blok setelah terkena bola
void UpdateBlockState(Block *block) {
    if (!block->active) return;  // Jika blok sudah tidak aktif, tidak perlu diupdate

    if (block->colorIndex == 0) { // Jika blok DARKGRAY, ubah menjadi BROWN
        block->colorIndex = 1;
        block->color = BROWN;
    } else if (block->colorIndex == 1) { // Jika blok BROWN, ubah menjadi BEIGE
        block->colorIndex = 2;
        block->color = BEIGE;
    } else if (block->colorIndex == 2) { // Jika blok BEIGE, blok hancur (non-aktif)
        block->active = false;
    }
}

// Fungsi untuk mengatur ulang level dan menginisialisasi ulang blok
void SetLevel(Block blocks[BLOCK_ROWS][BLOCK_COLS], int level) {
    InitLevelBlocks(blocks, level);
}
