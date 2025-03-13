#include "block.h"

// Inisialisasi blok dalam array 2D
void InitBlocks(Block blocks[BLOCK_ROWS][BLOCK_COLS]) {
    for (int i = 0; i < BLOCK_ROWS; i++) {
        for (int j = 0; j < BLOCK_COLS; j++) {
            blocks[i][j].rect.x = j * (BLOCK_WIDTH + BLOCK_SPACING);
            blocks[i][j].rect.y = i * (BLOCK_HEIGHT + BLOCK_SPACING);
            blocks[i][j].rect.width = BLOCK_WIDTH;
            blocks[i][j].rect.height = BLOCK_HEIGHT;
            blocks[i][j].active = true; // Semua blok aktif di awal
        }
    }
}

// Menggambar blok ke layar
void DrawBlocks(Block blocks[BLOCK_ROWS][BLOCK_COLS]) {
    for (int i = 0; i < BLOCK_ROWS; i++) {
        for (int j = 0; j < BLOCK_COLS; j++) {
            if (blocks[i][j].active) {
                DrawRectangleRec(blocks[i][j].rect, BLUE);  // Blok berwarna biru
                DrawRectangleLinesEx(blocks[i][j].rect, 2, BLACK); // Outline hitam
            }
        }
    }
}

// Implement the collision detection function
bool CheckBallBlockCollision(Vector2 ballPosition, float ballRadius, Rectangle blockRect) {
    return CheckCollisionCircleRec(ballPosition, ballRadius, blockRect);
}