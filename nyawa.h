#ifndef NYAWA_H
#define NYAWA_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>

#define MAX_NYAWA 3
#define HEART_SIZE 40  // Ukuran hati dalam piksel

typedef struct {
    SDL_Texture *heartTexture;
    SDL_Rect heartRects[MAX_NYAWA];
    int nyawa;
} Nyawa;

// Inisialisasi nyawa dengan tekstur hati
int initNyawa(Nyawa *nyawa, SDL_Renderer *renderer, const char *heartImagePath) {
    SDL_Surface *heartSurface = IMG_Load(heartImagePath);
    if (!heartSurface) {
        printf("Failed to load heart image: %s\n", IMG_GetError());
        return 0;
    }

    nyawa->heartTexture = SDL_CreateTextureFromSurface(renderer, heartSurface);
    SDL_FreeSurface(heartSurface);
    if (!nyawa->heartTexture) {
        printf("Failed to create texture: %s\n", SDL_GetError());
        return 0;
    }

    nyawa->nyawa = MAX_NYAWA;
    for (int i = 0; i < MAX_NYAWA; i++) {
        nyawa->heartRects[i].x = 10 + (i * (HEART_SIZE + 5));  // Jarak antar hati
        nyawa->heartRects[i].y = 10;
        nyawa->heartRects[i].w = HEART_SIZE;
        nyawa->heartRects[i].h = HEART_SIZE;
    }
    return 1;
}

// Menampilkan nyawa di layar
void renderNyawa(Nyawa *nyawa, SDL_Renderer *renderer) {
    for (int i = 0; i < nyawa->nyawa; i++) {
        SDL_RenderCopy(renderer, nyawa->heartTexture, NULL, &nyawa->heartRects[i]);
    }
}

// Mengurangi nyawa jika terkena damage
void kurangiNyawa(Nyawa *nyawa) {
    if (nyawa->nyawa > 0) {
        nyawa->nyawa--;
    }
}

// Menghapus tekstur sebelum keluar
void destroyNyawa(Nyawa *nyawa) {
    if (nyawa->heartTexture) {
        SDL_DestroyTexture(nyawa->heartTexture);
        nyawa->heartTexture = NULL;
    }
}

#endif // NYAWA_H
