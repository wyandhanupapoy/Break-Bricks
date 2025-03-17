#include "level.h"
#include "block.h"
#include <raylib.h>

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
                case 1: // Level 1: Semua blok kayu
                    blocks[i][j].color = BROWN;
                    blocks[i][j].durability = 1;
                    break;
                case 2: // Level 2: Kayu dan batu bata
                    if (i < BLOCK_ROWS / 2) {
                        blocks[i][j].color = GRAY;
                        blocks[i][j].durability = 2;
                    } else {
                        blocks[i][j].color = BROWN;
                        blocks[i][j].durability = 1;
                    }
                    break;
                case 3: // Level 3: Kayu, batu bata, dan besi
                    if (i < BLOCK_ROWS / 3) {
                        blocks[i][j].color = DARKGRAY;
                        blocks[i][j].durability = 3;
                    } else if (i < 2 * BLOCK_ROWS / 3) {
                        blocks[i][j].color = GRAY;
                        blocks[i][j].durability = 2;
                    } else {
                        blocks[i][j].color = BROWN;
                        blocks[i][j].durability = 1;
                    }
                    break;
            }
        }
    }
}

void UpdateBlockState(Block *block);
