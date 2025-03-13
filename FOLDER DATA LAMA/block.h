#ifndef BLOK_H
#define BLOK_H

#include <SDL2/SDL.h>

// Konstanta game
#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600
#define ROWS 5
#define COLUMNS 10
#define FPS 60

// Struktur blok dalam game
typedef struct {
    int x, y;
    int width, height;
    int isDestroyed;
    SDL_Color color;
} Block;

// Struktur utama game (menyimpan window dan renderer)
typedef struct {
    SDL_Window *window;
    SDL_Renderer *renderer;
    int running;
} Game;

extern Block blocks[ROWS][COLUMNS];

// Fungsi utama game
int initGame(Game *game);
void handleEvents(Game *game);
void updateGame();
void renderGame(Game *game);
void cleanUp(Game *game);

// Fungsi khusus blok
void initBlocks();
void drawBlocks(SDL_Renderer *renderer);

#endif
