/*
Nama Pembuat:   Wyandhanu Maulidan Nugraha
Nama Fitur:     Block
Deskripsi:      Fitur block untuk menampilkan blok-blok yang harus dihancurkan oleh pemain
*/

#ifndef BLOCK_H
#define BLOCK_H

#include <raylib.h>

#define BLOCK_ROWS 5
#define BLOCK_COLS 10
#define BLOCK_WIDTH 75
#define BLOCK_HEIGHT 25
#define BLOCK_SPACING 5

typedef struct {
    Rectangle rect;
    bool active;
    Color color;
    int hitPoints;
} Block;

// 🔹 Fungsi Blok
void DrawBlocks(Block blocks[BLOCK_ROWS][BLOCK_COLS]);
bool CheckBallBlockCollision(Vector2 ballPosition, float ballRadius, Rectangle blockRect);
bool AllBlocksDestroyed(Block blocks[BLOCK_ROWS][BLOCK_COLS]);

// 🔹 Tambahkan `extern` agar hanya sebagai referensi
extern void UpdateBlockState(Block *block); 

#endif // BLOCK_H