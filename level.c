#include "level.h"
#include "raylib.h"
#include <stdlib.h>  // Untuk rand()
#include <time.h>    // Untuk srand()

void InitLevelBlocks(Block blocks[BLOCK_ROWS][BLOCK_COLS], int level) {
    srand(time(NULL));  // Seed angka acak agar variasi tiap run berbeda

    Color colors[3] = { DARKGRAY, BROWN, BEIGE };  // Warna blok tersedia

    int maxColorIndex;
    if (level == 1) {
        maxColorIndex = 2;  // Hanya BEIGE (index 2)
    } else if (level == 2) {
        maxColorIndex = 1;  // BROWN (1) dan BEIGE (2)
    } else {
        maxColorIndex = 0;  // DARKGRAY (0), BROWN (1), dan BEIGE (2)
    }

    for (int i = 0; i < BLOCK_ROWS; i++) {
        for (int j = 0; j < BLOCK_COLS; j++) {
            blocks[i][j].rect.x = j * (BLOCK_WIDTH + BLOCK_SPACING) + 15;
            blocks[i][j].rect.y = i * (BLOCK_HEIGHT + BLOCK_SPACING) + 70;
            blocks[i][j].rect.width = BLOCK_WIDTH;
            blocks[i][j].rect.height = BLOCK_HEIGHT;
            blocks[i][j].active = true;

            // Pilih warna acak sesuai batas level
            int randomIndex = rand() % (3 - maxColorIndex) + maxColorIndex;
            blocks[i][j].color = colors[randomIndex];
            blocks[i][j].colorIndex = randomIndex;
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

// **Implementasi SetLevel**
void SetLevel(Block blocks[BLOCK_ROWS][BLOCK_COLS], int level) {
    InitLevelBlocks(blocks, level);
}
