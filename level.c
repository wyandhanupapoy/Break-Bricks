#include "level.h"
#include "block.h"
#include <raylib.h>
#include <stdio.h>

void SetLevel(Block blocks[BLOCK_ROWS][BLOCK_COLS], int level) {
    for (int i = 0; i < BLOCK_ROWS; i++) {
        for (int j = 0; j < BLOCK_COLS; j++) {
            switch (level) {
                case 1:
                    blocks[i][j].color = (Color){210, 180, 140, 255}; // Coklat muda
                    blocks[i][j].durability = 1;
                    break;
                case 2:
                    blocks[i][j].color = (Color){128, 0, 0, 255}; // Merah marun
                    blocks[i][j].durability = 2;
                    break;
                case 3:
                    blocks[i][j].color = (Color){169, 169, 169, 255}; // Abu-abu
                    blocks[i][j].durability = 3;
                    break;
                default:
                    blocks[i][j].color = (Color){210, 180, 140, 255}; // Default ke coklat muda
                    blocks[i][j].durability = 1;
                    break;
            }
        }
    }
}
