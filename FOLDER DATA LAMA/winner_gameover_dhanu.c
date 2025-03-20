#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>  // Include SDL_ttf header for text rendering
#include <stdio.h>

// Window dimensions
#define WINDOW_WIDTH 400
#define WINDOW_HEIGHT 300

// Button structure
typedef struct {
    SDL_Rect rect;
    const char* label;
    SDL_Color color;
} Button;

// Function to draw a button with text
void drawButton(SDL_Renderer *renderer, Button *button, TTF_Font *font) {
    // Set button color and draw
    SDL_SetRenderDrawColor(renderer, button->color.r, button->color.g, button->color.b, 255);
    SDL_RenderFillRect(renderer, &button->rect);
    
    // Draw label on button (this part requires SDL_ttf for text rendering)
    SDL_Surface* surface = TTF_RenderText_Solid(font, button->label, (SDL_Color){0, 0, 0, 255});
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);
    
    int text_width = 0, text_height = 0;
    SDL_QueryTexture(texture, NULL, NULL, &text_width, &text_height);
    
    SDL_Rect text_rect = { button->rect.x + (button->rect.w - text_width) / 2, 
                           button->rect.y + (button->rect.h - text_height) / 2, 
                           text_width, text_height };
    SDL_RenderCopy(renderer, texture, NULL, &text_rect);
    SDL_DestroyTexture(texture);
}

int main(int argc, char* argv[]) {
    SDL_Init(SDL_INIT_VIDEO);
    TTF_Init();  // Initialize SDL_ttf for text rendering

    SDL_Window *window = SDL_CreateWindow("SDL2 Button Click Game", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN);
    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    // Create a font
    TTF_Font *font = TTF_OpenFont("arial.ttf", 24);  // Make sure you have this font file in your directory or replace with another font

    // Define the buttons
    Button buttons[2] = {
        {{100, 100, 200, 50}, "Start", {0, 255, 0}}, // Green Start button
        {{100, 180, 200, 50}, "Exit", {255, 0, 0}}   // Red Exit button
    };

    SDL_Event e;
    int quit = 0;
    int game_over = 0;

    // Main loop
    while (!quit) {
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_QUIT) {
                quit = 1;
            } else if (e.type == SDL_MOUSEBUTTONDOWN && e.button.button == SDL_BUTTON_LEFT) {
                // Get mouse position
                int x, y;
                SDL_GetMouseState(&x, &y);

                // Check if any button was clicked
                for (int i = 0; i < 2; i++) {
                    if (x >= buttons[i].rect.x && x <= buttons[i].rect.x + buttons[i].rect.w &&
                        y >= buttons[i].rect.y && y <= buttons[i].rect.y + buttons[i].rect.h) {
                        if (i == 0) {  // Start button
                            printf("Winner!\n");
                            game_over = 1;
                        } else {  // Exit button
                            printf("Game Over!\n");
                            quit = 1;
                        }
                    }
                }
            }
        }

        // Clear screen
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255); // White background
        SDL_RenderClear(renderer);

        // Draw buttons
        for (int i = 0; i < 2; i++) {
            drawButton(renderer, &buttons[i], font);
        }

        // Update the screen
        SDL_RenderPresent(renderer);

        // Delay to control the frame rate
        SDL_Delay(16);
    }

    // Clean up
    TTF_CloseFont(font);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    TTF_Quit();
    SDL_Quit();

    return 0;
}
