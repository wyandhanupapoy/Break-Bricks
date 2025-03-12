#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <stdbool.h>
#include <stdio.h>

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600

typedef enum {
    MENU_MAIN,
    MENU_LEVEL,
    MENU_HOW_TO_PLAY
} GameState;

SDL_Window *window = NULL;
SDL_Renderer *renderer = NULL;
TTF_Font *font = NULL;
GameState gameState = MENU_MAIN;
bool running = true;

void renderText(const char *text, int x, int y, SDL_Color color) {
    SDL_Surface *surface = TTF_RenderText_Solid(font, text, color);
    if (!surface) {
        printf("Failed to create text surface: %s\n", TTF_GetError());
        return;
    }

    SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface);
    if (!texture) {
        printf("Failed to create text texture: %s\n", SDL_GetError());
        SDL_FreeSurface(surface);
        return;
    }

    SDL_Rect destRect = {x, y, surface->w, surface->h};
    SDL_RenderCopy(renderer, texture, NULL, &destRect);
    SDL_FreeSurface(surface);
    SDL_DestroyTexture(texture);
}

void renderMainMenu() {
    SDL_Color color = {255, 255, 255, 255};
    renderText("Play", 350, 200, color);
    renderText("How to Play", 320, 300, color);
    renderText("Quit", 350, 400, color);
}

void renderLevelMenu() {
    SDL_Color color = {255, 255, 255, 255};
    renderText("Easy", 350, 200, color);
    renderText("Medium", 350, 300, color);
    renderText("Hard", 350, 400, color);
    renderText("Back", 350, 500, color);
}

void renderHowToPlay() {
    SDL_Color color = {255, 255, 255, 255};
    renderText("Use the paddle to bounce the ball and break bricks!", 150, 200, color);
    renderText("Back", 350, 500, color);
}

void handleMouseClick(int x, int y) {
    if (gameState == MENU_MAIN) {
        if (y > 200 && y < 250) gameState = MENU_LEVEL;
        else if (y > 300 && y < 350) gameState = MENU_HOW_TO_PLAY;
        else if (y > 400 && y < 450) running = false;
    } else if (gameState == MENU_LEVEL) {
        if (y > 500 && y < 550) gameState = MENU_MAIN;
        else if (y > 200 && y < 250) printf("Starting Easy Level\n");
        else if (y > 300 && y < 350) printf("Starting Medium Level\n");
        else if (y > 400 && y < 450) printf("Starting Hard Level\n");
    } else if (gameState == MENU_HOW_TO_PLAY) {
        if (y > 500 && y < 550) gameState = MENU_MAIN;
    }
}

void gameLoop() {
    SDL_Event event;
    while (running) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) running = false;
            else if (event.type == SDL_MOUSEBUTTONDOWN) {
                handleMouseClick(event.button.x, event.button.y);
            }
        }

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        if (gameState == MENU_MAIN) renderMainMenu();
        else if (gameState == MENU_LEVEL) renderLevelMenu();
        else if (gameState == MENU_HOW_TO_PLAY) renderHowToPlay();

        SDL_RenderPresent(renderer);
    }
}

int main(int argc, char *argv[]) {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
        return 1;
    }

    if (TTF_Init() == -1) {
        printf("TTF could not initialize! TTF_Error: %s\n", TTF_GetError());
        SDL_Quit();
        return 1;
    }

    window = SDL_CreateWindow("Brick Breaker Menu", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (!window) {
        printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
        TTF_Quit();
        SDL_Quit();
        return 1;
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer) {
        printf("Renderer could not be created! SDL_Error: %s\n", SDL_GetError());
        SDL_DestroyWindow(window);
        TTF_Quit();
        SDL_Quit();
        return 1;
    }

    font = TTF_OpenFont("arial.ttf", 24);
    if (!font) {
        printf("Failed to load font! TTF_Error: %s\n", TTF_GetError());
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        TTF_Quit();
        SDL_Quit();
        return 1;
    }

    gameLoop();

    TTF_CloseFont(font);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    TTF_Quit();
    SDL_Quit();
    return 0;
}
