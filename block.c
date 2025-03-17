#include "block.h"
#include "layout.h"  // Tambahkan ini agar bisa mengenali GAME_AREA_WIDTH

void InitBlocks(Block blocks[BLOCK_ROWS][BLOCK_COLS]) {
    Color colors[BLOCK_ROWS] = { BLUE, GREEN, YELLOW, ORANGE, RED };

    int offsetX = (GAME_AREA_WIDTH - (BLOCK_COLS * (BLOCK_WIDTH + BLOCK_SPACING) - BLOCK_SPACING)) / 2;
    int offsetY = 70; // Jarak dari atas layar
    
    for (int i = 0; i < BLOCK_ROWS; i++) {
        for (int j = 0; j < BLOCK_COLS; j++) {
            blocks[i][j].rect.x = offsetX + j * (BLOCK_WIDTH + BLOCK_SPACING);
            blocks[i][j].rect.y = offsetY + i * (BLOCK_HEIGHT + BLOCK_SPACING);
            blocks[i][j].rect.width = BLOCK_WIDTH;
            blocks[i][j].rect.height = BLOCK_HEIGHT;
            blocks[i][j].active = true;
            blocks[i][j].color = colors[i];
        }
    }
}

void DrawBlocks(Block blocks[BLOCK_ROWS][BLOCK_COLS]) {
    for (int i = 0; i < BLOCK_ROWS; i++) {
        for (int j = 0; j < BLOCK_COLS; j++) {
            if (blocks[i][j].active) {
                DrawRectangleRec(blocks[i][j].rect, blocks[i][j].color);
                DrawRectangleLinesEx(blocks[i][j].rect, 2, BLACK);
            }
        }
    }
}

bool CheckBallBlockCollision(Vector2 ballPosition, float ballRadius, Rectangle blockRect) {
    return CheckCollisionCircleRec(ballPosition, ballRadius, blockRect);
}

bool AllBlocksDestroyed(Block blocks[BLOCK_ROWS][BLOCK_COLS]) {
    for (int i = 0; i < BLOCK_ROWS; i++) {
        for (int j = 0; j < BLOCK_COLS; j++) {
            if (blocks[i][j].active) return false;
        }
    }
    return true;
}
