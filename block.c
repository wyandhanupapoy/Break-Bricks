#include "blok.h"

Block blocks[ROWS][COLUMNS];

// **Inisialisasi SDL & Window**
int initGame(Game *game) {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        SDL_Log("Gagal menginisialisasi SDL: %s", SDL_GetError());
        return 0;
    }

    game->window = SDL_CreateWindow("Breakout Game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                                    SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (!game->window) {
        SDL_Log("Gagal membuat window: %s", SDL_GetError());
        SDL_Quit();
        return 0;
    }

    game->renderer = SDL_CreateRenderer(game->window, -1, SDL_RENDERER_ACCELERATED);
    if (!game->renderer) {
        SDL_Log("Gagal membuat renderer: %s", SDL_GetError());
        SDL_DestroyWindow(game->window);
        SDL_Quit();
        return 0;
    }

    game->running = 1;
    initBlocks();
    return 1;
}

// **Event Handler (Menutup Window)**
void handleEvents(Game *game) {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT) {
            game->running = 0;
        }
    }
}

// **Update Game (Untuk Logika ke Depan)**
void updateGame() {
    // Bisa ditambahkan logika bola dan paddle di sini
}

// **Render Game (Menggambar Blok)**
void renderGame(Game *game) {
    SDL_SetRenderDrawColor(game->renderer, 0, 0, 0, 255);
    SDL_RenderClear(game->renderer);

    drawBlocks(game->renderer);

    SDL_RenderPresent(game->renderer);
}

// **Membersihkan SDL Sebelum Keluar**
void cleanUp(Game *game) {
    SDL_DestroyRenderer(game->renderer);
    SDL_DestroyWindow(game->window);
    SDL_Quit();
}

// **Inisialisasi Blok**
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

            // Variasi warna blok berdasarkan baris
            blocks[i][j].color.r = 50 + (i * 40);
            blocks[i][j].color.g = 100 + (j * 15);
            blocks[i][j].color.b = 200 - (i * 30);
            blocks[i][j].color.a = 255;
        }
    }
}

// **Menggambar Blok ke Layar**
void drawBlocks(SDL_Renderer *renderer) {
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLUMNS; j++) {
            if (!blocks[i][j].isDestroyed) {
                SDL_Rect rect = {blocks[i][j].x, blocks[i][j].y, blocks[i][j].width, blocks[i][j].height};
                SDL_SetRenderDrawColor(renderer, blocks[i][j].color.r, blocks[i][j].color.g, blocks[i][j].color.b, blocks[i][j].color.a);
                SDL_RenderFillRect(renderer, &rect);
            }
        }
    }
}
