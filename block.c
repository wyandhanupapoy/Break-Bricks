#include "block.h"
#include "level.h"  // Tambahkan ini agar bisa menggunakan InitLevelBlocks

void InitBlocks(Block blocks[BLOCK_ROWS][BLOCK_COLS], int level) {
    InitLevelBlocks(blocks, level);  // Gunakan sistem level
}

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

bool CheckBallBlockCollision(Vector2 ballPosition, float ballRadius, Rectangle blockRect) {
    return CheckCollisionCircleRec(ballPosition, ballRadius, blockRect);
}

bool AllBlocksDestroyed(Block blocks[BLOCK_ROWS][BLOCK_COLS]) {
    for (int i = 0; i < BLOCK_ROWS; i++) {
        for (int j = 0; j < BLOCK_COLS; j++) {
            if (blocks[i][j].active) return false;
        }
    }
    return true;
}
