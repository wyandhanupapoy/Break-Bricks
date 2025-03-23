/*
Nama Pembuat:   Wyandhanu Maulidan Nugraha
Nama Fitur:     Block
Deskripsi:      Fitur block untuk menampilkan blok-blok yang harus dihancurkan oleh pemain
*/

#ifndef BLOCK_H
#define BLOCK_H

#include "raylib.h"

// Konstanta jumlah baris dan kolom blok
#define ROWS 5
#define COLS 10
#define BLOCK_WIDTH 75
#define BLOCK_HEIGHT 25
#define BLOCK_SPACING 5

// Struktur untuk blok
typedef struct {
    Rectangle rect;  // Posisi dan ukuran blok
    bool active;     // Status blok (aktif/hancur)
} Block;

// Deklarasi fungsi
void InitBlocks(Block blocks[ROWS][COLS]);
void DrawBlocks(Block blocks[ROWS][COLS]);

#endif
