#ifndef SOUND_H
#define SOUND_H

#include "raylib.h"

// Fungsi utama
void InitSoundEffects();
void UnloadSoundEffects();

// Fungsi play
void PlayButtonClick();
void PlayPaddleHit();
void PlayBlockHit();
void PlayLoseLife();
void PlayGameOver();
void PlayGameWin();

#endif
