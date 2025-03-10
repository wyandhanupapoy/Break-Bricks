#include "block.h"

Block blocks[ROWS][COLUMNS]; // Definisi array blok

void initBlocks() {
    int startX = 50, startY = 50;
    int blockWidth = 70, blockHeight = 20;
    int spacing = 5;

    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLUMNS; j++) {
            blocks[i][j].x = startX + j * (blockWidth + spacing);
            blocks[i][j].y = startY + i * (blockHeight + spacing);
            blocks[i][j].width = blockWidth;
            blocks[i][j].height = blockHeight;
            blocks[i][j].isDestroyed = 0;
        }
    }
}

void drawBlocks(SDL_Renderer *renderer) {
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLUMNS; j++) {
            if (!blocks[i][j].isDestroyed) {
                SDL_Rect rect = {blocks[i][j].x, blocks[i][j].y, blocks[i][j].width, blocks[i][j].height};
                SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);  // Warna biru
                SDL_RenderFillRect(renderer, &rect);
            }
        }
    }
}
