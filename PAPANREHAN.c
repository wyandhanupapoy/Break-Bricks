#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <time.h>

#define SDL_MAIN_HANDLED
#define WIDTH 800
#define HEIGHT 600
#define GRID_ROWS 5
#define GRID_COLS 5
#define TIMER_HEIGHT 20

typedef struct {
    int max_time;
    int start_time;
} Timer;

void draw_timer_bar(SDL_Renderer *renderer, Timer *timer) {
    int elapsed = (int)(time(NULL) - timer->start_time);
    int time_left = timer->max_time - elapsed;
    float percentage = (float)time_left / timer->max_time;
    
    if (percentage < 0) percentage = 0;
    int bar_width = (int)(WIDTH * percentage);
    
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
    SDL_Rect bar = {0, 0, bar_width, TIMER_HEIGHT};
    SDL_RenderFillRect(renderer, &bar);
}

void initialize_grid(int grid[GRID_ROWS][GRID_COLS]) {
    for (int i = 0; i < GRID_ROWS; i++) {
        for (int j = 0; j < GRID_COLS; j++) {
            grid[i][j] = 1;
        }
    }
}

void draw_grid(SDL_Renderer *renderer, int grid[GRID_ROWS][GRID_COLS]) {
    int block_width = WIDTH / GRID_COLS;
    int block_height = (HEIGHT / 2) / GRID_ROWS;
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

    for (int i = 0; i < GRID_ROWS; i++) {
        for (int j = 0; j < GRID_COLS; j++) {
            if (grid[i][j] == 1) {
                SDL_Rect block = { j * block_width, i * block_height + TIMER_HEIGHT, block_width - 2, block_height - 2 };
                SDL_RenderFillRect(renderer, &block);
            }
        }
    }
}

int main(int argc, char *argv[]) {
    SDL_SetMainReady();

    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("SDL initialization failed: %s\n", SDL_GetError());
        return 1;
    }
    
    SDL_Window *window = SDL_CreateWindow("Block Breaker Timer", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT, SDL_WINDOW_SHOWN);
    if (!window) {
        printf("Window creation failed: %s\n", SDL_GetError());
        SDL_Quit();
        return 1;
    }

    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer) {
        printf("Renderer creation failed: %s\n", SDL_GetError());
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    Timer timer = {60, (int)time(NULL)};
    int grid[GRID_ROWS][GRID_COLS];
    initialize_grid(grid);

    SDL_Event event;
    int running = 1;
    while (running) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                running = 0;
            }
        }

        int elapsed = (int)(time(NULL) - timer.start_time);
        if (elapsed >= timer.max_time) {
            running = 0;
        }

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);
        
        draw_timer_bar(renderer, &timer);
        draw_grid(renderer, grid);

        SDL_RenderPresent(renderer);
        SDL_Delay(1000 / 60);
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}
