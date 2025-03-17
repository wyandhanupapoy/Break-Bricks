#include "level.h"
#include "block.h"
#include <raylib.h>
#include <stdio.h>

Sound soundMetalToBrick;
Sound soundBrickToWood;
Sound soundWoodBreak;

void LoadLevelSounds() {
    soundMetalToBrick = LoadSound("metal_to_brick.wav");
    soundBrickToWood = LoadSound("brick_to_wood.wav");
    soundWoodBreak = LoadSound("wood_break.wav");
}

void SetLevel(Block blocks[BLOCK_ROWS][BLOCK_COLS], int level) {
    for (int i = 0; i < BLOCK_ROWS; i++) {
        for (int j = 0; j < BLOCK_COLS; j++) {
            switch (level) {
                case 1:
                    blocks[i][j].color = (Color){139, 69, 19, 255};
                    blocks[i][j].durability = 1;
                    break;
                case 2:
                    if (i < BLOCK_ROWS / 2) {
                        blocks[i][j].color = (Color){255, 0, 0, 255};
                        blocks[i][j].durability = 2;
                    } else {
                        blocks[i][j].color = (Color){139, 69, 19, 255};
                        blocks[i][j].durability = 1;
                    }
                    break;
                case 3:
                    if (i < BLOCK_ROWS / 3) {
                        blocks[i][j].color = (Color){105, 105, 105, 255};
                        blocks[i][j].durability = 3;
                    } else if (i < 2 * BLOCK_ROWS / 3) {
                        blocks[i][j].color = (Color){255, 0, 0, 255};
                        blocks[i][j].durability = 2;
                    } else {
                        blocks[i][j].color = (Color){139, 69, 19, 255};
                        blocks[i][j].durability = 1;
                    }
                    break;
                default:
                    blocks[i][j].color = (Color){139, 69, 19, 255};
                    blocks[i][j].durability = 1;
                    break;
            }

            printf("Block[%d][%d]: Warna = (%d, %d, %d, %d), Durability = %d\n",
                   i, j, blocks[i][j].color.r, blocks[i][j].color.g,
                   blocks[i][j].color.b, blocks[i][j].color.a, blocks[i][j].durability);
        }
    }
}
