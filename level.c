#include "level.h"
#include "block.h"
#include <stdlib.h> // Untuk fungsi `rand()`
#include <time.h>   // Untuk seeding angka acak

void InitLevelBlocks(Block blocks[BLOCK_ROWS][BLOCK_COLS], int level) {
    srand(time(NULL));

    for (int i = 0; i < BLOCK_ROWS; i++) {
        for (int j = 0; j < BLOCK_COLS; j++) {
            blocks[i][j].rect.x = j * (BLOCK_WIDTH + BLOCK_SPACING) + 15;
            blocks[i][j].rect.y = i * (BLOCK_HEIGHT + BLOCK_SPACING) + 70;
            blocks[i][j].rect.width = BLOCK_WIDTH;
            blocks[i][j].rect.height = BLOCK_HEIGHT;
            blocks[i][j].active = true;

            if (level == 1) {
                blocks[i][j].hitPoints = 1;
                blocks[i][j].color = (Color){255, 204, 77, 255}; // Kuning Retro
            }
            else if (level == 2) {
                int randomType = rand() % 2; // 0 atau 1
                if (randomType == 0) {
                    blocks[i][j].hitPoints = 1;
                    blocks[i][j].color = (Color){255, 204, 77, 255}; // Kuning Retro
                } else {
                    blocks[i][j].hitPoints = 2;
                    blocks[i][j].color = (Color){255, 140, 26, 255}; // Orange Retro
                }
            }
            else if (level == 3) {
                int randomType = rand() % 3; // 🔥 0 - 2 (Kuning, Orange, Ungu)
                if (randomType == 0) {
                    blocks[i][j].hitPoints = 1;
                    blocks[i][j].color = (Color){255, 204, 77, 255}; // Kuning Retro
                } else if (randomType == 1) {
                    blocks[i][j].hitPoints = 2;
                    blocks[i][j].color = (Color){255, 140, 26, 255}; // Orange Retro
                } else {
                    blocks[i][j].hitPoints = 3;
                    blocks[i][j].color = (Color){140, 90, 200, 255}; // Ungu Retro
                }
            }
        }
    }
}

// 🔹 Atur Level (Memanggil `InitLevelBlocks`)
void SetLevel(Block blocks[BLOCK_ROWS][BLOCK_COLS], int level) {
    InitLevelBlocks(blocks, level);
}
