#include <SDL2/SDL.h>

#define SCREEN_WIDTH 650  // Lebar layar lebih besar
#define SCREEN_HEIGHT 800
#define GRID_ROWS 20
#define GRID_COLS 15
#define CELL_SIZE 30
#define SCORE_PANEL_WIDTH 200 // Lebar panel skor diperbesar
#define BORDER_THICKNESS 5 // Ketebalan border

SDL_Window *window = NULL;
SDL_Renderer *renderer = NULL;
int grid[GRID_ROWS][GRID_COLS] = {0}; // Grid game dengan array

void initSDL() {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("SDL tidak dapat diinisialisasi: %s\n", SDL_GetError());
        exit(1);
    }

    window = SDL_CreateWindow("Gamebot SDL", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (!window) {
        printf("Gagal membuat jendela: %s\n", SDL_GetError());
        exit(1);
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer) {
        printf("Gagal membuat renderer: %s\n", SDL_GetError());
        exit(1);
    }
}

void drawBorders() {
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

    // Border area permainan (sisi kiri)
    SDL_Rect leftBorder = { 0, 0, GRID_COLS * CELL_SIZE, SCREEN_HEIGHT };
    SDL_RenderDrawRect(renderer, &leftBorder);

    // Border panel skor (sisi kanan, lebih lebar)
    SDL_Rect rightBorder = { GRID_COLS * CELL_SIZE, 0, SCORE_PANEL_WIDTH, SCREEN_HEIGHT };
    SDL_RenderDrawRect(renderer, &rightBorder);

    // Garis pemisah antara game dan skor
    SDL_Rect separator = { GRID_COLS * CELL_SIZE, 0, BORDER_THICKNESS, SCREEN_HEIGHT };
    SDL_RenderFillRect(renderer, &separator);
}

void gameLoop() {
    int running = 1;
    SDL_Event event;

    while (running) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                running = 0;
            }
        }

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        drawBorders();

        SDL_RenderPresent(renderer);
        SDL_Delay(100);
    }
}

void cleanupSDL() {
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

int main() {
    initSDL();
    gameLoop();
    cleanupSDL();
    return 0;
}
