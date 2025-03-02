#ifndef SOUND_EFFECTS_H
#define SOUND_EFFECTS_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>

// Deklarasi variabel untuk menyimpan efek suara dan musik latar
extern Mix_Music *backgroundMusic;
extern Mix_Chunk *clickSound;
extern Mix_Chunk *paddleBounce;
extern Mix_Chunk *wallBounce;
extern Mix_Chunk *blockBreak;
extern Mix_Chunk *winSound;
extern Mix_Chunk *loseSound;

// Fungsi untuk inisialisasi audio
int initAudio();

// Fungsi untuk memuat semua sound effect
int loadSounds();

// Fungsi untuk memainkan efek suara tertentu
void playBackgroundMusic();
void playClickSound();
void playPaddleBounceSound();
void playWallBounceSound();
void playBlockBreakSound();
void playWinSound();
void playLoseSound();

// Fungsi untuk membersihkan dan membebaskan memory SDL_mixer
void cleanUpAudio();

#endif // SOUND_EFFECTS_H
