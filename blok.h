#ifndef BLOCK_H
#define BLOCK_H

#include <SDL2/SDL.h>

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600
#define ROWS 5
#define COLUMNS 10

typedef struct {
    int x, y;
    int width, height;
    int isDestroyed;
} Block;

extern Block blocks[ROWS][COLUMNS];  // Deklarasi array blok

void initBlocks();
void drawBlocks(SDL_Renderer *renderer);

#endif
