#include "level.h"
#include "raylib.h"

void InitLevelBlocks(Block blocks[BLOCK_ROWS][BLOCK_COLS]) {
    Color colors[3] = { DARKGRAY, BROWN, BEIGE };

    for (int i = 0; i < BLOCK_ROWS; i++) {
        for (int j = 0; j < BLOCK_COLS; j++) {
            blocks[i][j].rect.x = j * (BLOCK_WIDTH + BLOCK_SPACING) + 15;
            blocks[i][j].rect.y = i * (BLOCK_HEIGHT + BLOCK_SPACING) + 70;
            blocks[i][j].rect.width = BLOCK_WIDTH;
            blocks[i][j].rect.height = BLOCK_HEIGHT;
            blocks[i][j].active = true;

            // Pilih warna acak dan simpan indeksnya
            int colorIndex = GetRandomValue(0, 2);
            blocks[i][j].color = colors[colorIndex];
            blocks[i][j].colorIndex = colorIndex;
        }
    }
}

void UpdateBlockState(Block *block) {
    if (!block->active) return;

    // Jika warna sekarang DARKGRAY (0), ubah ke BROWN (1)
    if (block->colorIndex == 0) {
        block->colorIndex = 1;
        block->color = BROWN;
    } 
    // Jika warna sekarang BROWN (1), ubah ke BEIGE (2)
    else if (block->colorIndex == 1) {
        block->colorIndex = 2;
        block->color = BEIGE;
    } 
    // Jika warna sekarang BEIGE (2), blok hancur
    else if (block->colorIndex == 2) {
        block->active = false;
    }
}
