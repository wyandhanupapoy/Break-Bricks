#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <stdio.h>
#include <stdbool.h>

int main() {
    // Inisialisasi SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("Error SDL_Init: %s\n", SDL_GetError());
        return 1;
    }

    if (TTF_Init() < 0) {
        printf("Error TTF_Init: %s\n", TTF_GetError());
        return 1;
    }

    // Buat window dan renderer
    SDL_Window *window = SDL_CreateWindow("Stopwatch Game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    if (!window || !renderer) {
        printf("Error membuat window atau renderer: %s\n", SDL_GetError());
        return 1;
    }

    // Load font
    TTF_Font *font = TTF_OpenFont("arial.ttf", 24);
    if (!font) {
        printf("Error load font: %s\n", TTF_GetError());
        return 1;
    }

    bool running = true;
    bool timing = false;
    Uint32 startTime = 0, elapsedTime = 0;
    SDL_Event event;

    while (running) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT || (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_ESCAPE)) {
                running = false;
            } else if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_RETURN) {
                if (!timing) {
                    startTime = SDL_GetTicks(); // Mulai stopwatch
                    timing = true;
                } else {
                    elapsedTime = SDL_GetTicks() - startTime; // Stop stopwatch
                    timing = false;
                }
            }
        }

        // Render background
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        // Hitung waktu
        Uint32 displayTime = timing ? SDL_GetTicks() - startTime : elapsedTime;
        char timeText[32];
        sprintf(timeText, "Time: %.2f s", displayTime / 1000.0);

        // Tampilkan waktu di layar
        renderText(renderer, font, "Press ENTER to start/stop", 50, 50);
        renderText(renderer, font, timeText, 50, 100);
        renderText(renderer, font, "Press ESC to exit", 50, 150);

        SDL_RenderPresent(renderer);
    }

    // Cleanup
    TTF_CloseFont(font);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    TTF_Quit();
    SDL_Quit();

    return 0;
}
