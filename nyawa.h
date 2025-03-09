#ifndef NYAWA_H
#define NYAWA_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>

#define MAX_NYAWA 3
#define HEART_SIZE 40  // Ukuran hati dalam piksel

typedef struct {
    SDL_Texture *heartTexture;
    int heartRects[MAX_NYAWA][3]; // [i][0]=X, [i][1]=Y, [i][2]=Status (1 = aktif, 0 = hilang)
    int nyawa;
} Nyawa;

// Inisialisasi nyawa dengan tekstur hati
int initNyawa(Nyawa *nyawa, SDL_Renderer *renderer, const char *heartImagePath) {
    if (!nyawa || !renderer || !heartImagePath) {
        fprintf(stderr, "Invalid parameters passed to initNyawa\n");
        return 0;
    }

    SDL_Surface *heartSurface = IMG_Load(heartImagePath);
    if (!heartSurface) {
        fprintf(stderr, "Failed to load heart image: %s\n", IMG_GetError());
        return 0;
    }

    nyawa->heartTexture = SDL_CreateTextureFromSurface(renderer, heartSurface);
    SDL_FreeSurface(heartSurface);
    
    if (!nyawa->heartTexture) {
        fprintf(stderr, "Failed to create texture: %s\n", SDL_GetError());
        return 0;
    }

    nyawa->nyawa = MAX_NYAWA;
    for (int i = 0; i < MAX_NYAWA; i++) {
        nyawa->heartRects[i][0] = 10 + (i * (HEART_SIZE + 5)); // X Position
        nyawa->heartRects[i][1] = 10;  // Y Position
        nyawa->heartRects[i][2] = 1;   // Status aktif
    }
    return 1;
}

// Menampilkan nyawa di layar
void renderNyawa(Nyawa *nyawa, SDL_Renderer *renderer) {
    if (!nyawa || !renderer || !nyawa->heartTexture) return;
    
    for (int i = 0; i < MAX_NYAWA; i++) {
        if (nyawa->heartRects[i][2] == 1) { // Hanya render nyawa aktif
            SDL_Rect heartRect = { nyawa->heartRects[i][0], nyawa->heartRects[i][1], HEART_SIZE, HEART_SIZE };
            SDL_RenderCopy(renderer, nyawa->heartTexture, NULL, &heartRect);
        }
    }
}

// Mengurangi nyawa jika terkena damage
void kurangiNyawa(Nyawa *nyawa) {
    if (nyawa->nyawa > 0) {
        nyawa->nyawa--;  // Kurangi jumlah nyawa aktif
        nyawa->heartRects[nyawa->nyawa][2] = 0; // Set status hati terakhir menjadi 0 (hilang)
        printf("Nyawa berkurang! Sisa nyawa: %d\n", nyawa->nyawa);
    } else {
        printf("Nyawa sudah habis!\n");
    }
}

// Reset nyawa ke keadaan awal
void resetNyawa(Nyawa *nyawa) {
    nyawa->nyawa = MAX_NYAWA;
    for (int i = 0; i < MAX_NYAWA; i++) {
        nyawa->heartRects[i][2] = 1; // Aktifkan semua hati kembali
    }
    printf("Nyawa di-reset ke: %d\n", nyawa->nyawa);
}

// Menghapus tekstur sebelum keluar
void destroyNyawa(Nyawa *nyawa) {
    if (!nyawa) return;
    if (nyawa->heartTexture) {
        SDL_DestroyTexture(nyawa->heartTexture);
        nyawa->heartTexture = NULL;
    }
}

#endif // NYAWA_H
