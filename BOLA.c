#include <SDL2/SDL.h>
#include <stdio.h>
#include "BOLA.h"

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600
#define BALL_RADIUS 15
#define GRAVITY 0.5f
#define BOUNCE_DAMPING 0.7f

// Ukuran Array 2D
#define BALL_ROWS 3
#define BALL_COLS 3

// Variabel SDL
SDL_Window *window = NULL;
SDL_Renderer *renderer = NULL;
int running = 1;

// Array 2D untuk Menyimpan Bola
Ball balls[BALL_ROWS][BALL_COLS];

// Inisialisasi SDL
int initSDL() {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("SDL gagal diinisialisasi: %s\n", SDL_GetError());
        return 0;
    }

    window = SDL_CreateWindow("Bola SDL2",
                              SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                              SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (!window) {
        printf("Gagal membuat window: %s\n", SDL_GetError());
        return 0;
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer) {
        printf("Gagal membuat renderer: %s\n", SDL_GetError());
        return 0;
    }

    return 1;
}

// Inisialisasi Bola dalam Array 2D
void initBalls() {
    for (int i = 0; i < BALL_ROWS; i++) {
        for (int j = 0; j < BALL_COLS; j++) {
            balls[i][j].x = 100 + j * 200;  // Posisi awal X
            balls[i][j].y = 50 + i * 150;   // Posisi awal Y
            balls[i][j].velocityX = 2.0f;   // Kecepatan X
            balls[i][j].velocityY = 0.0f;   // Kecepatan Y
        }
    }
}

// Update Posisi Bola
void updateBalls() {
    for (int i = 0; i < BALL_ROWS; i++) {
        for (int j = 0; j < BALL_COLS; j++) {
            balls[i][j].velocityY += GRAVITY;  // Efek gravitasi
            balls[i][j].x += balls[i][j].velocityX;
            balls[i][j].y += balls[i][j].velocityY;

            // Pantulan dari dinding kiri/kanan
            if (balls[i][j].x - BALL_RADIUS < 0 || balls[i][j].x + BALL_RADIUS > SCREEN_WIDTH) {
                balls[i][j].velocityX = -balls[i][j].velocityX;
            }

            // Pantulan dari lantai
            if (balls[i][j].y + BALL_RADIUS > SCREEN_HEIGHT) {
                balls[i][j].y = SCREEN_HEIGHT - BALL_RADIUS;
                balls[i][j].velocityY = -balls[i][j].velocityY * BOUNCE_DAMPING;
            }
        }
    }
}

// Render Bola
void renderBalls() {
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255); // Warna bola putih
    for (int i = 0; i < BALL_ROWS; i++) {
        for (int j = 0; j < BALL_COLS; j++) {
            for (int w = -BALL_RADIUS; w <= BALL_RADIUS; w++) {
                for (int h = -BALL_RADIUS; h <= BALL_RADIUS; h++) {
                    if (w * w + h * h <= BALL_RADIUS * BALL_RADIUS) {
                        SDL_RenderDrawPoint(renderer, balls[i][j].x + w, balls[i][j].y + h);
                    }
                }
            }
        }
    }
}

// Game Loop
void gameLoop() {
    SDL_Event event;
    while (running) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                running = 0;
            }
        }

        updateBalls();

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);
        renderBalls();
        SDL_RenderPresent(renderer);

        SDL_Delay(16); // ~60 FPS
    }
}

// Clean-up SDL
void closeSDL() {
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

// Fungsi Utama
int main(int argc, char *argv[]) {
    if (!initSDL()) {
        return -1;
    }

    initBalls();
    gameLoop();
    closeSDL();

    return 0;
}
