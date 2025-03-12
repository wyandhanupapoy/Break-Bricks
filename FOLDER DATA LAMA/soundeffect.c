#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>
#include <stdio.h>

// Deklarasi variabel sound
Mix_Music *backgroundMusic = NULL;
Mix_Chunk *clickSound = NULL;
Mix_Chunk *paddleBounce = NULL;
Mix_Chunk *wallBounce = NULL;
Mix_Chunk *blockBreak = NULL;
Mix_Chunk *winSound = NULL;
Mix_Chunk *loseSound = NULL;

// Inisialisasi SDL_mixer
int initAudio() {
    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
        printf("SDL_mixer Error: %s\n", Mix_GetError());
        return 0;
    }
    return 1;
}

// Load semua efek suara
int loadSounds() {
    backgroundMusic = Mix_LoadMUS("assets/sounds/background.mp3");
    clickSound = Mix_LoadWAV("assets/sounds/click_3.wav");
    paddleBounce = Mix_LoadWAV("assets/sounds/Random2.wav");
    wallBounce = Mix_LoadWAV("assets/sounds/Random2.wav");
    blockBreak = Mix_LoadWAV("assets/sounds/Explosion4.wav");
    winSound = Mix_LoadWAV("assets/sounds/Won!.wav");
    loseSound = Mix_LoadWAV("assets/sounds/losetrumpet.wav");
    
    if (!backgroundMusic || !clickSound || !paddleBounce || !wallBounce || !blockBreak || !winSound || !loseSound) {
        printf("Failed to load sound: %s\n", Mix_GetError());
        return 0;
    }
    return 1;
}

// Memainkan backsound game
void playBackgroundMusic() {
    Mix_PlayMusic(backgroundMusic, -1); // -1 agar loop terus-menerus
}

// Memainkan efek suara
void playClickSound() {
    Mix_PlayChannel(-1, clickSound, 0);
}

void playPaddleBounceSound() {
    Mix_PlayChannel(-1, paddleBounce, 0);
}

void playWallBounceSound() {
    Mix_PlayChannel(-1, wallBounce, 0);
}

void playBlockBreakSound() {
    Mix_PlayChannel(-1, blockBreak, 0);
}

void playWinSound() {
    Mix_PlayChannel(-1, winSound, 0);
}

void playLoseSound() {
    Mix_PlayChannel(-1, loseSound, 0);
}

// Membersihkan dan menutup SDL_mixer
void cleanUpAudio() {
    Mix_FreeMusic(backgroundMusic);
    Mix_FreeChunk(clickSound);
    Mix_FreeChunk(paddleBounce);
    Mix_FreeChunk(wallBounce);
    Mix_FreeChunk(blockBreak);
    Mix_FreeChunk(winSound);
    Mix_FreeChunk(loseSound);
    Mix_CloseAudio();
}
