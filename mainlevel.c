#include "level.h"
#include "block.h"

// Inisialisasi level
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
