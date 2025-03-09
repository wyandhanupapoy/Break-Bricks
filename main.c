#include <SDL2/SDL.h>
#include <SDL2/SDL_main.h>
#include <stdio.h>
#include "nyawa.h"

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600

int main(int argc, char *argv[])
{
    // Inisialisasi SDL
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS) != 0)
    {
        printf("SDL Initialization Error: %s\n", SDL_GetError());
        return 1;
    }

    // Membuat jendela
    SDL_Window *window = SDL_CreateWindow("SDL2 Window", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN);
    if (!window)
    {
        printf("Window Creation Error: %s\n", SDL_GetError());
        SDL_Quit();
        return 1;
    }

    // Membuat renderer
    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer)
    {
        printf("Renderer Creation Error: %s\n", SDL_GetError());
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    if (!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG)) {
        printf("Failed to initialize SDL_image: %s\n", IMG_GetError());
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }    

    // Loop utama
    int running = 1;

    // Inisialisasi di awal
    Nyawa playerNyawa;
    if (!initNyawa(&playerNyawa, renderer, "gambar/heart.png")) {
        printf("Gagal menginisialisasi nyawa.\n");
        printf("Periksa apakah file gambar/heart.png benar-benar ada!\n");
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    SDL_Event event;
    while (running)
    {
        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT)
            {
                running = 0;
            }
            else if (event.type == SDL_KEYDOWN) {
                if (event.key.keysym.sym == SDLK_SPACE) {
                    kurangiNyawa(&playerNyawa);
                    printf("Nyawa: %d\n", playerNyawa.nyawa);  // Debugging untuk cek apakah nyawa berkurang
                }
            }
        }

        // Mengatur warna latar belakang
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        // Di dalam loop render
        renderNyawa(&playerNyawa, renderer);

        // Menampilkan hasil render
        SDL_RenderPresent(renderer);
    }

    // Hapus sumber daya saat keluar
    destroyNyawa(&playerNyawa);

    // Membersihkan sumber daya
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    IMG_Quit();

    return 0;
}