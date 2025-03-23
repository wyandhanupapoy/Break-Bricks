//Nama Pembuat: Nezya Zulfa Fauziah  
//Nama Fitur: Level  
//Deskripsi: Fitur level menentukan tingkat kesulitan permainan dengan membedakan ketahanan blok berdasarkan warna. **Level 1** hanya memiliki blok **kuning** (1 ketahanan). **Level 2** menambahkan blok **oranye** (2 ketahanan), yang berubah menjadi kuning sebelum hancur. **Level 3** menambah blok **ungu** (3 ketahanan), yang berubah menjadi oranye, lalu kuning sebelum hancur. Fitur ini memberikan variasi dan tantangan bagi pemain sesuai level yang dipilih.

#ifndef LEVEL_H
#define LEVEL_H

#include "raylib.h"
#include "block.h"

// Fungsi untuk inisialisasi blok berdasarkan level
void InitLevelBlocks(Block blocks[BLOCK_ROWS][BLOCK_COLS], int level);

// Fungsi untuk mengatur level dan memanggil `InitLevelBlocks`
void SetLevel(Block blocks[BLOCK_ROWS][BLOCK_COLS], int level);

// Fungsi untuk memperbarui status blok (misalnya saat terkena bola)
void UpdateBlockState(Block *block);

#endif // LEVEL_H
