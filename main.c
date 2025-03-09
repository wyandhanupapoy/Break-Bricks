#include <SDL2/SDL.h>
#include <SDL2/SDL_main.h>
#include <SDL2/SDL_image.h>  
#include <stdio.h>
#include "nyawa.h"

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600

int main(int argc, char *argv[])
{
    // Inisialisasi SDL
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS) != 0) {
        printf("SDL Initialization Error: %s\n", SDL_GetError());
        return 1;
    }

    // Membuat jendela
    SDL_Window *window = SDL_CreateWindow("SDL2 Window", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 
                                          WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN);
    if (!window) {
        printf("Window Creation Error: %s\n", SDL_GetError());
        SDL_Quit();
        return 1;
    }

    // Membuat renderer
    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer) {
        printf("Renderer Creation Error: %s\n", SDL_GetError());
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    // Inisialisasi SDL_image
    if (!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG)) {
        printf("Failed to initialize SDL_image: %s\n", IMG_GetError());
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    // Inisialisasi nyawa
    Nyawa playerNyawa;
    if (!initNyawa(&playerNyawa, renderer, "gambar/heart.png")) {
        printf("Gagal menginisialisasi nyawa. Periksa apakah file gambar/heart.png benar-benar ada!\n");
        IMG_Quit();
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    // Loop utama
    int running = 1;
    SDL_Event event;
    
    while (running) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                running = 0;
            } 
            else if (event.type == SDL_KEYDOWN) {
                if (event.key.keysym.sym == SDLK_SPACE) {
                    kurangiNyawa(&playerNyawa);
                } 
                else if (event.key.keysym.sym == SDLK_r) {  // Reset nyawa jika tekan 'R'
                    resetNyawa(&playerNyawa);
                }
            }
        }

        // Mengatur warna latar belakang
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        // Render nyawa
        renderNyawa(&playerNyawa, renderer);

        // Menampilkan hasil render
        SDL_RenderPresent(renderer);

        // Delay untuk mengurangi penggunaan CPU (sekitar 60 FPS)
        SDL_Delay(16);
    }

    // Hapus sumber daya saat keluar
    destroyNyawa(&playerNyawa);

    // Membersihkan sumber daya
    IMG_Quit();
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
