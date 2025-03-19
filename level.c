#include "level.h"
#include "raylib.h"

void InitLevelBlocks(Block blocks[BLOCK_ROWS][BLOCK_COLS], int level) {
    Color colors[] = { DARKGRAY, BROWN, BEIGE };

    for (int i = 0; i < BLOCK_ROWS; i++) {
        for (int j = 0; j < BLOCK_COLS; j++) {
            blocks[i][j].rect.x = j * (BLOCK_WIDTH + BLOCK_SPACING) + 15;
            blocks[i][j].rect.y = i * (BLOCK_HEIGHT + BLOCK_SPACING) + 70;
            blocks[i][j].rect.width = BLOCK_WIDTH;
            blocks[i][j].rect.height = BLOCK_HEIGHT;
            blocks[i][j].active = true;

            if (level == 1) {
                blocks[i][j].color = BEIGE;
                blocks[i][j].colorIndex = 2;
            } else if (level == 2) {
                blocks[i][j].colorIndex = (j % 2 == 0) ? 2 : 1;  // Beige atau Brown
                blocks[i][j].color = colors[blocks[i][j].colorIndex];
            } else if (level == 3) {
                blocks[i][j].colorIndex = i % 3;  // Dark Gray, Brown, Beige
                blocks[i][j].color = colors[blocks[i][j].colorIndex];
            }
        }
    }
}

void UpdateBlockState(Block *block) {
    if (!block->active) return;

    if (block->colorIndex == 0) { // DARKGRAY -> BROWN
        block->colorIndex = 1;
        block->color = BROWN;
    } else if (block->colorIndex == 1) { // BROWN -> BEIGE
        block->colorIndex = 2;
        block->color = BEIGE;
    } else if (block->colorIndex == 2) { // BEIGE -> Hancur
        block->active = false;
    }
}
