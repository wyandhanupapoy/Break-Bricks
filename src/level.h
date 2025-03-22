#ifndef LEVEL_H
#define LEVEL_H

#include "raylib.h"
#include "block.h"

// 🔹 Fungsi untuk inisialisasi blok berdasarkan level
void InitLevelBlocks(Block blocks[BLOCK_ROWS][BLOCK_COLS], int level);

// 🔹 Fungsi untuk mengatur level dan memanggil `InitLevelBlocks`
void SetLevel(Block blocks[BLOCK_ROWS][BLOCK_COLS], int level);

// 🔹 Fungsi untuk memperbarui status blok (misalnya saat terkena bola)
void UpdateBlockState(Block *block);

#endif // LEVEL_H
