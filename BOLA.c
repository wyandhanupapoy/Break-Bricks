#include "ball.h"
#include <SDL2/SDL.h>
#include <stdio.h>

#define BALL_COUNT_X 3  // Jumlah bola dalam sumbu X
#define BALL_COUNT_Y 3  // Jumlah bola dalam sumbu Y

// Variabel global SDL
SDL_Window *window = NULL;
SDL_Renderer *renderer = NULL;
int running = 1;  // Status program

// Array 2D untuk menyimpan bola
Ball balls[BALL_COUNT_X][BALL_COUNT_Y];

// Inisialisasi bola dengan posisi awal berbeda
void initBalls() {
    for (int i = 0; i < BALL_COUNT_X; i++) {
        for (int j = 0; j < BALL_COUNT_Y; j++) {
            float startX = 100 + i * 200;  // Jarak antar bola
            float startY = 50 + j * 150;   // Jarak antar bola
            initBall(&balls[i][j], startX, startY, 15);
        }
    }
}

// Inisialisasi SDL
int initSDL() {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("SDL tidak dapat diinisialisasi! SDL_Error: %s\n", SDL_GetError());
        return 0;
    }

    window = SDL_CreateWindow("Break Bricks", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                              SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (!window) {
        printf("Gagal membuat window! SDL_Error: %s\n", SDL_GetError());
        return 0;
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer) {
        printf("Gagal membuat renderer! SDL_Error: %s\n", SDL_GetError());
        return 0;
    }

    return 1;
}

// Fungsi utama untuk game loop
void gameLoop() {
    SDL_Event event;
    while (running) {
        // Event handler
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                running = 0;
            }
        }

        // Update bola
        for (int i = 0; i < BALL_COUNT_X; i++) {
            for (int j = 0; j < BALL_COUNT_Y; j++) {
                updateBall(&balls[i][j]);
            }
        }

        // Render bola
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); // Background hitam
        SDL_RenderClear(renderer);
        for (int i = 0; i < BALL_COUNT_X; i++) {
            for (int j = 0; j < BALL_COUNT_Y; j++) {
                renderBall(renderer, &balls[i][j]);
            }
        }
        SDL_RenderPresent(renderer);

        SDL_Delay(16);  // ~60 FPS
    }
}

// Fungsi utama program
int main(int argc, char *argv[]) {
    if (!initSDL()) {
        return -1;
    }

    initBalls();
    gameLoop();

    // Cleanup
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
