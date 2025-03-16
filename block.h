#ifndef BLOCK_H
#define BLOCK_H

#include "raylib.h"

// Konstanta untuk blok
#define BLOCK_ROWS 5
#define BLOCK_COLS 10
#define BLOCK_WIDTH 75
#define BLOCK_HEIGHT 25
#define BLOCK_SPACING 5

// Struktur untuk blok
typedef struct {
    Rectangle rect;  // Posisi dan ukuran blok
    bool active;     // Status blok (aktif/hancur)
    Color color;     // Warna blok
} Block;

// Deklarasi fungsi
void InitBlocks(Block blocks[BLOCK_ROWS][BLOCK_COLS]);
void DrawBlocks(Block blocks[BLOCK_ROWS][BLOCK_COLS]);
bool CheckBallBlockCollision(Vector2 ballPosition, float ballRadius, Rectangle blockRect);
bool AllBlocksDestroyed(Block blocks[BLOCK_ROWS][BLOCK_COLS]);

#endif // BLOCK_H
