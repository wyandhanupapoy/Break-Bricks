#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <stdio.h>

int main(int argc, char *argv[]) {
    // Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("SDL could not initialize! SDL Error: %s\n", SDL_GetError());
        return -1;
    }

    // Initialize SDL_ttf
    if (TTF_Init() == -1) {
        printf("SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError());
        SDL_Quit();
        return -1;
    }

    // Create window
    SDL_Window* window = SDL_CreateWindow("Game UI",
                                          SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
                                          640, 480, SDL_WINDOW_SHOWN);
    if (window == NULL) {
        printf("Window could not be created! SDL Error: %s\n", SDL_GetError());
        TTF_Quit();
        SDL_Quit();
        return -1;
    }

    // Create renderer
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (renderer == NULL) {
        printf("Renderer could not be created! SDL Error: %s\n", SDL_GetError());
        SDL_DestroyWindow(window);
        TTF_Quit();
        SDL_Quit();
        return -1;
    }

    // Define colors
    SDL_Color white = {255, 255, 255, 255};
    SDL_Color red = {255, 0, 0, 255};
    SDL_Color green = {0, 255, 0, 255};

    // Define button positions
    SDL_Rect button1 = {150, 200, 150, 50}; // "WINNER" button
    SDL_Rect button2 = {340, 200, 150, 50}; // "GAME OVER" button

    // Event handling
    SDL_Event e;
    int quit = 0;
    int showWinner = 0; // Variable to track if "WINNER" text should be shown

    while (!quit) {
        while (SDL_PollEvent(&e) != 0) {
            if (e.type == SDL_QUIT) {
                quit = 1;
            }

            // Draw background
            SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
            SDL_RenderClear(renderer);

            // Draw buttons (blue for WINNER, red for GAME OVER)
            SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255); // Blue for WINNER
            SDL_RenderFillRect(renderer, &button1);
            SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255); // Red for GAME OVER
            SDL_RenderFillRect(renderer, &button2);

            // Render text on buttons
            SDL_Surface* textSurface = NULL;
            SDL_Texture* textTexture = NULL;
            TTF_Font* font = TTF_OpenFont("04B_30__.TTF", 24); // Normal font size

            if (font == NULL) {
                printf("Font could not be opened! SDL_ttf Error: %s\n", TTF_GetError());
                return -1;
            }

            // Render "WINNER" text on button 1
            textSurface = TTF_RenderText_Solid(font, "OPSI 1", white);
            textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
            SDL_FreeSurface(textSurface);
            SDL_Rect textRect1 = {200, 215, 100, 30}; // Position of "WINNER" text
            SDL_RenderCopy(renderer, textTexture, NULL, &textRect1);
            SDL_DestroyTexture(textTexture);

            // Render "GAME OVER" text on button 2
            textSurface = TTF_RenderText_Solid(font, "OPSI 2", white);
            textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
            SDL_FreeSurface(textSurface);
            SDL_Rect textRect2 = {370, 215, 150, 30}; // Position of "GAME OVER" text
            SDL_RenderCopy(renderer, textTexture, NULL, &textRect2);
            SDL_DestroyTexture(textTexture);

            // If "WINNER" button is clicked, show larger text
            if (showWinner) {
                // Larger font for WINNER message
                TTF_Font* largeFont = TTF_OpenFont("arial.ttf", 48); // Large font size
                if (largeFont == NULL) {
                    printf("Font could not be opened for large size! SDL_ttf Error: %s\n", TTF_GetError());
                    return -1;
                }

                // Center the "WINNER" text on the screen
                const char* winnerText = "WINNER";
                textSurface = TTF_RenderText_Solid(largeFont, winnerText, green);
                textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
                SDL_FreeSurface(textSurface);

                // Get text size for centering
                int textWidth = 0, textHeight = 0;
                TTF_SizeText(largeFont, winnerText, &textWidth, &textHeight);
                SDL_Rect winnerRect = {(640 - textWidth) / 2, 100, textWidth, textHeight}; // Centered position
                SDL_RenderCopy(renderer, textTexture, NULL, &winnerRect);
                SDL_DestroyTexture(textTexture);
                TTF_CloseFont(largeFont);
            }

            // Present the renderer
            SDL_RenderPresent(renderer);

            // Handle mouse click
            if (e.type == SDL_MOUSEBUTTONDOWN) {
                int x, y;
                SDL_GetMouseState(&x, &y);

                // Check if "WINNER" button is clicked
                if (x >= button1.x && x <= button1.x + button1.w && y >= button1.y && y <= button1.y + button1.h) {
                    showWinner = 1; // Show "WINNER" text
                }
                // Check if "GAME OVER" button is clicked
                if (x >= button2.x && x <= button2.x + button2.w && y >= button2.y && y <= button2.y + button2.h) {
                    printf("GAME OVER\n");
                }
            }
        }
    }

    // Clean up and quit SDL
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    TTF_Quit();
    SDL_Quit();

    return 0;
}
