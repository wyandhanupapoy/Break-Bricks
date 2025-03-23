/*
Nama Pembuat:   Wyandhanu Maulidan Nugraha
Nama Fitur:     Block
Deskripsi:      Fitur block untuk menampilkan blok-blok yang harus dihancurkan oleh pemain
*/

#include "block.h"

// 🔹 Update kondisi blok saat terkena bola
void UpdateBlockState(Block *block) {
    if (!block->active) return;

    block->hitPoints--; // Kurangi HP blok
    if (block->hitPoints <= 0) {
        block->active = false;
    } else {
        // 🔹 Update warna blok sesuai sisa HP
        if (block->hitPoints == 2) {
            block->color = (Color){255, 140, 26, 255}; // Orange Retro
        } else if (block->hitPoints == 1) {
            block->color = (Color){255, 204, 77, 255}; // Kuning Retro
        }
    }
}

// 🔹 Gambar semua blok
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

// 🔹 Cek tabrakan bola dengan blok
bool CheckBallBlockCollision(Vector2 ballPosition, float ballRadius, Rectangle blockRect) {
    return CheckCollisionCircleRec(ballPosition, ballRadius, blockRect);
}

// 🔹 Cek apakah semua blok sudah hancur
bool AllBlocksDestroyed(Block blocks[BLOCK_ROWS][BLOCK_COLS]) {
    for (int i = 0; i < BLOCK_ROWS; i++) {
        for (int j = 0; j < BLOCK_COLS; j++) {
            if (blocks[i][j].active) return false;
        }
    }
    return true;
}