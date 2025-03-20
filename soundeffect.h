#ifndef SOUNDEFFECT_H
#define SOUNDEFFECT_H

#include <raylib.h>

#define SOUNDEFFECT_ROWS 2
#define SOUNDEFFECT_COLS 3

extern Sound soundEffects[SOUNDEFFECT_ROWS][SOUNDEFFECT_COLS];

void LoadSoundEffects();
void UnloadSoundEffects();
void PlaySoundEffect(int row, int col);

#endif
