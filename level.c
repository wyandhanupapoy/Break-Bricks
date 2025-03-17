#include "level.h"
#include "block.h"
#include <raylib.h>
#include <stdio.h>

void SetLevel(Block blocks[BLOCK_ROWS][BLOCK_COLS], int level) {
    for (int i = 0; i < BLOCK_ROWS; i++) {
        for (int j = 0; j < BLOCK_COLS; j++) {
            // Posisi tetap sama seperti di InitBlocks()
            blocks[i][j].rect.x = j * (BLOCK_WIDTH + BLOCK_SPACING) + 15;
            blocks[i][j].rect.y = i * (BLOCK_HEIGHT + BLOCK_SPACING) + 70;
            blocks[i][j].rect.width = BLOCK_WIDTH;
            blocks[i][j].rect.height = BLOCK_HEIGHT;
            blocks[i][j].active = true; // Pastikan blok aktif

            // Tentukan warna & ketahanan blok berdasarkan level
            switch (level) {
                case 1:
                    blocks[i][j].color = (Color){210, 180, 140, 255}; // Coklat muda (Kayu)
                    blocks[i][j].durability = 1;
                    break;
                case 2:
                    blocks[i][j].color = (Color){128, 0, 0, 255}; // Merah marun (Batu Bata)
                    blocks[i][j].durability = 2;
                    break;
                case 3:
                    if (i < BLOCK_ROWS / 3) {
                        blocks[i][j].color = (Color){169, 169, 169, 255}; // Abu-abu (Besi)
                        blocks[i][j].durability = 3;
                    } else if (i < 2 * BLOCK_ROWS / 3) {
                        blocks[i][j].color = (Color){128, 0, 0, 255}; // Merah marun (Batu Bata)
                        blocks[i][j].durability = 2;
                    } else {
                        blocks[i][j].color = (Color){210, 180, 140, 255}; // Coklat muda (Kayu)
                        blocks[i][j].durability = 1;
                    }
                    break;
                default:
                    blocks[i][j].color = (Color){210, 180, 140, 255}; // Default ke kayu
                    blocks[i][j].durability = 1;
                    break;
            }
        }
    }
}

void UpdateBlockState(Block *block) {
    if (block->active && block->durability > 0) {
        block->durability--;

        // Ubah warna dan ketahanan berdasarkan perubahan durability
        if (block->durability == 2) {
            block->color = (Color){128, 0, 0, 255}; // Batu bata
        } else if (block->durability == 1) {
            block->color = (Color){210, 180, 140, 255}; // Kayu
        } else if (block->durability == 0) {
            block->active = false; // Blok hancur
        }
    }
}
