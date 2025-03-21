#include "block.h"
#include <stdlib.h>  // Untuk `rand()`
#include <time.h>    // Untuk `srand(time(NULL))`

// 🔹 Warna Blok untuk Tema Retro
Color retroColors[] = {
    (Color){255, 85, 85, 255},     // Merah terang
    (Color){255, 204, 77, 255},    // Kuning cerah
    (Color){102, 255, 102, 255},   // Hijau neon
    (Color){102, 204, 255, 255},   // Biru langit
    (Color){204, 102, 255, 255}    // Ungu retro
};

#include "block.h"

void UpdateBlockState(Block *block)
{
    if (!block->active)
        return;

    block->hitPoints--; // Kurangi HP blok

    if (block->hitPoints <= 0)
    {
        block->active = false;
    }
    else
    {
        // 🔹 **Update warna blok sesuai sisa hitPoints**
        if (block->hitPoints == 2)
        {
            block->color = (Color){255, 140, 26, 255}; // **Orange Retro**
        }
        else if (block->hitPoints == 1)
        {
            block->color = (Color){255, 204, 77, 255}; // **Kuning Retro**
        }
    }
}


// 🔹 Inisialisasi Blok Berdasarkan Level
void InitBlocks(Block blocks[BLOCK_ROWS][BLOCK_COLS], int level) {
    srand(time(NULL));

    for (int i = 0; i < BLOCK_ROWS; i++) {
        for (int j = 0; j < BLOCK_COLS; j++) {
            blocks[i][j].rect.x = j * (BLOCK_WIDTH + BLOCK_SPACING) + 15;
            blocks[i][j].rect.y = i * (BLOCK_HEIGHT + BLOCK_SPACING) + 70;
            blocks[i][j].rect.width = BLOCK_WIDTH;
            blocks[i][j].rect.height = BLOCK_HEIGHT;
            blocks[i][j].active = true;
            blocks[i][j].color = retroColors[i % 5];

            // 🔹 Hit Points Bergantung pada Level
            if (level == 1) {
                blocks[i][j].hitPoints = 1; // Mudah
            } else if (level == 2) {
                blocks[i][j].hitPoints = (rand() % 2) + 1; // 1-2 hit
            } else if (level == 3) {
                blocks[i][j].hitPoints = (rand() % 3) + 1; // 1-3 hit
            }
        }
    }
}

// 🔹 Gambar Blok
void DrawBlocks(Block blocks[BLOCK_ROWS][BLOCK_COLS]) {
    for (int i = 0; i < BLOCK_ROWS; i++) {
        for (int j = 0; j < BLOCK_COLS; j++) {
            if (blocks[i][j].active) {
                DrawRectangleRec(blocks[i][j].rect, blocks[i][j].color);
                DrawRectangleLinesEx(blocks[i][j].rect, 2, BLACK);
            }
        }
    }
}

// 🔹 Cek Tabrakan Bola dengan Blok
bool CheckBallBlockCollision(Vector2 ballPosition, float ballRadius, Rectangle blockRect) {
    return CheckCollisionCircleRec(ballPosition, ballRadius, blockRect);
}

// 🔹 Mengecek Apakah Semua Blok Sudah Hancur
bool AllBlocksDestroyed(Block blocks[BLOCK_ROWS][BLOCK_COLS]) {
    for (int i = 0; i < BLOCK_ROWS; i++) {
        for (int j = 0; j < BLOCK_COLS; j++) {
            if (blocks[i][j].active) return false;
        }
    }
    return true;
}

