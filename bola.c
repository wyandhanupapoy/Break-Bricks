#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdbool.h>

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600
#define BALL_SIZE 10

void moveBall(float ball[2][2]) {
    ball[0][0] += ball[1][0]; // Update posisi X
    ball[0][1] += ball[1][1]; // Update posisi Y

    // Pantulan terhadap dinding
    if (ball[0][0] <= 0 || ball[0][0] >= SCREEN_WIDTH - BALL_SIZE) {
        ball[1][0] = -ball[1][0]; // Balik arah X
    }
    if (ball[0][1] <= 0 || ball[0][1] >= SCREEN_HEIGHT - BALL_SIZE) {
        ball[1][1] = -ball[1][1]; // Balik arah Y
    }
}

int main(int argc, char *argv[]) {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
        return -1;
    }

    SDL_Window *window = SDL_CreateWindow("Break Bricks - Ball", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (!window) {
        printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
        SDL_Quit();
        return -1;
    }

    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer) {
        printf("Renderer could not be created! SDL_Error: %s\n", SDL_GetError());
        SDL_DestroyWindow(window);
        SDL_Quit();
        return -1;
    }

    // Inisialisasi bola dengan array 2D
    float ball[2][2] = {
        {SCREEN_WIDTH / 2.0, SCREEN_HEIGHT / 2.0}, // Posisi awal (x, y)
        {4.0, -4.0} // Kecepatan awal (vx, vy)
    };

    bool running = true;
    SDL_Event event;

    while (running) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                running = false;
            }
        }

        moveBall(ball);

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_Rect ballRect = {ball[0][0], ball[0][1], BALL_SIZE, BALL_SIZE};
        SDL_RenderFillRect(renderer, &ballRect);

        SDL_RenderPresent(renderer);
        SDL_Delay(16);
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
