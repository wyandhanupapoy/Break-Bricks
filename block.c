#include "block.h"
#include <raylib.h>
#include <raymath.h>

void InitBlocks(Block blocks[BLOCK_ROWS][BLOCK_COLS], int level) {
    for (int i = 0; i < BLOCK_ROWS; i++) {
        for (int j = 0; j < BLOCK_COLS; j++) {
            blocks[i][j].rect.x = j * (BLOCK_WIDTH + BLOCK_SPACING) + 15;
            blocks[i][j].rect.y = i * (BLOCK_HEIGHT + BLOCK_SPACING) + 70;
            blocks[i][j].rect.width = BLOCK_WIDTH;
            blocks[i][j].rect.height = BLOCK_HEIGHT;
            blocks[i][j].active = true;

            // Menentukan jenis blok berdasarkan level
            if (level == 1) {
                blocks[i][j].durability = 1; // Kayu
                blocks[i][j].color = BROWN;
            } else if (level == 2) {
                blocks[i][j].durability = (i < BLOCK_ROWS / 2) ? 2 : 1; // Batu bata dan kayu
                blocks[i][j].color = (blocks[i][j].durability == 2) ? RED : BROWN;
            } else {
                blocks[i][j].durability = (i < BLOCK_ROWS / 3) ? 3 : (i < 2 * BLOCK_ROWS / 3) ? 2 : 1; // Besi, batu bata, kayu
                if (blocks[i][j].durability == 3) blocks[i][j].color = GRAY;
                else if (blocks[i][j].durability == 2) blocks[i][j].color = RED;
                else blocks[i][j].color = BROWN;
            }
        }
    }
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

bool CheckBallBlockCollision(Vector2 ballPosition, float ballRadius, Block *block) {
    if (block->active && CheckCollisionCircleRec(ballPosition, ballRadius, block->rect)) {
        UpdateBlockState(block);
        return true;
    }
    return false;
}

void UpdateBlockState(Block *block) {
    if (block->durability > 1) {
        block->durability--;
        if (block->durability == 2) block->color = RED;
        else if (block->durability == 1) block->color = BROWN;
    } else {
        block->active = false;
    }
}

bool AllBlocksDestroyed(Block blocks[BLOCK_ROWS][BLOCK_COLS]) {
    for (int i = 0; i < BLOCK_ROWS; i++) {
        for (int j = 0; j < BLOCK_COLS; j++) {
            if (blocks[i][j].active) return false;
        }
    }
    return true;
}
