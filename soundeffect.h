#ifndef SOUNDEFFECT_H
#define SOUNDEFFECT_H

#include <raylib.h>

#define SOUND_ROWS 2
#define SOUND_COLS 3

typedef enum {
    SOUND_BACKSOUND,
    SOUND_BUTTON,
    SOUND_BLOCK_BREAK,
    SOUND_LOSE,
    SOUND_BOUNCE,
    SOUND_WIN
} SoundType;

void InitSoundEffects(Sound soundEffects[SOUND_ROWS][SOUND_COLS]);
void PlaySoundEffect(Sound soundEffects[SOUND_ROWS][SOUND_COLS], SoundType type);
void UnloadSoundEffects(Sound soundEffects[SOUND_ROWS][SOUND_COLS]);

#endif
