#ifndef LEVEL_H
#define LEVEL_H

#include "block.h"  // Mengimpor definisi blok agar bisa digunakan dalam level

// Fungsi untuk menginisialisasi blok sesuai dengan level yang dipilih
void InitLevelBlocks(Block blocks[BLOCK_ROWS][BLOCK_COLS], int level);

// Fungsi untuk mengatur ulang blok saat level dimulai atau berganti
void SetLevel(Block blocks[BLOCK_ROWS][BLOCK_COLS], int level);  // Sekarang sudah diimplementasikan!

// Fungsi untuk memperbarui status blok saat terkena bola (mengubah warna atau menghancurkannya)
void UpdateBlockState(Block *block);

#endif // LEVEL_H
