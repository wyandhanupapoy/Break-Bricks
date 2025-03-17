#include "level.h"
#include "block.h"

void SetLevel(Block blocks[BLOCK_ROWS][BLOCK_COLS], int level) {
    for (int i = 0; i < BLOCK_ROWS; i++) {
        for (int j = 0; j < BLOCK_COLS; j++) {
            switch (level) {
                case 1: // Level 1: Semua blok kayu (mudah dihancurkan)
                    blocks[i][j].color = BROWN;
                    blocks[i][j].durability = 1;
                    break;
                case 2: // Level 2: Kayu dan batu bata
                    if (i < BLOCK_ROWS / 2) {
                        blocks[i][j].color = GRAY; // Batu bata
                        blocks[i][j].durability = 2;
                    } else {
                        blocks[i][j].color = BROWN; // Kayu
                        blocks[i][j].durability = 1;
                    }
                    break;
                case 3: // Level 3: Kayu, batu bata, dan besi
                    if (i < BLOCK_ROWS / 3) {
                        blocks[i][j].color = DARKGRAY; // Besi
                        blocks[i][j].durability = 3;
                    } else if (i < 2 * BLOCK_ROWS / 3) {
                        blocks[i][j].color = GRAY; // Batu bata
                        blocks[i][j].durability = 2;
                    } else {
                        blocks[i][j].color = BROWN; // Kayu
                        blocks[i][j].durability = 1;
                    }
                    break;
            }
        }
    }
}

void UpdateBlockState(Block *block) {
    if (block->active) {
        block->durability--;

        // Jika daya tahan habis, blok berubah jenis atau hancur
        if (block->durability == 2) {
            block->color = GRAY; // Dari besi ke batu bata
        } else if (block->durability == 1) {
            block->color = BROWN; // Dari batu bata ke kayu
        } else if (block->durability <= 0) {
            block->active = false; // Kayu hancur
        }
    }
}
