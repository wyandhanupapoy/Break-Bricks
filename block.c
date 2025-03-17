#include "block.h"
#include <raylib.h>
#include <stdio.h>

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
                blocks[i][j].durability = 1;
                blocks[i][j].color = (Color){139, 69, 19, 255}; // Brown
            } else if (level == 2) {
                blocks[i][j].durability = (i < BLOCK_ROWS / 2) ? 2 : 1;
                blocks[i][j].color = (blocks[i][j].durability == 2) ? (Color){255, 0, 0, 255} : (Color){139, 69, 19, 255};
            } else {
                blocks[i][j].durability = (i < BLOCK_ROWS / 3) ? 3 : (i < 2 * BLOCK_ROWS / 3) ? 2 : 1;
                if (blocks[i][j].durability == 3) blocks[i][j].color = (Color){105, 105, 105, 255};
                else if (blocks[i][j].durability == 2) blocks[i][j].color = (Color){255, 0, 0, 255};
                else blocks[i][j].color = (Color){139, 69, 19, 255};
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
        if (block->durability == 2) block->color = (Color){255, 0, 0, 255}; // RED
        else if (block->durability == 1) block->color = (Color){139, 69, 19, 255}; // BROWN
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
