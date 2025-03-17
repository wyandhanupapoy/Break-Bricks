#include "soundeffect.h"
#include <stdio.h>

void InitSoundEffects(Sound soundEffects[SOUND_ROWS][SOUND_COLS]) {
    InitAudioDevice();

    soundEffects[0][0] = LoadSound("assets/sounds/background.mp3");
    soundEffects[0][1] = LoadSound("assets/sounds/click_3.wav");
    soundEffects[0][2] = LoadSound("assets/sounds/Explosion4.wav");
    soundEffects[1][0] = LoadSound("assets/sounds/losetrumpet.wav");
    soundEffects[1][1] = LoadSound("assets/sounds/Random2.wav");
    soundEffects[1][2] = LoadSound("assets/sounds/Won!.wav");
}

void PlaySoundEffect(Sound soundEffects[SOUND_ROWS][SOUND_COLS], SoundType type) {
    switch (type) {
        case SOUND_BACKSOUND:
            PlaySound(soundEffects[0][0]);
            break;
        case SOUND_BUTTON:
            PlaySound(soundEffects[0][1]);
            break;
        case SOUND_BLOCK_BREAK:
            PlaySound(soundEffects[0][2]);
            break;
        case SOUND_LOSE:
            PlaySound(soundEffects[1][0]);
            break;
        case SOUND_BOUNCE:
            PlaySound(soundEffects[1][1]);
            break;
        case SOUND_WIN:
            PlaySound(soundEffects[1][2]);
            break;
    }
}

void UnloadSoundEffects(Sound soundEffects[SOUND_ROWS][SOUND_COLS]) {
    for (int i = 0; i < SOUND_ROWS; i++) {
        for (int j = 0; j < SOUND_COLS; j++) {
            UnloadSound(soundEffects[i][j]);
        }
    }
    CloseAudioDevice();
}
