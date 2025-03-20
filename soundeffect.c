#include "soundeffect.h"
#include <stdio.h> // Untuk debug

Sound soundEffects[SOUNDEFFECT_ROWS][SOUNDEFFECT_COLS];

void LoadSoundEffects()
{
    InitAudioDevice();

    soundEffects[0][0] = LoadSound("assets/sounds/menu_click.wav");
    soundEffects[0][1] = LoadSound("assets/sounds/background.mp3");
    soundEffects[0][2] = LoadSound("assets/sounds/ball_bounce.wav");

    soundEffects[1][0] = LoadSound("assets/sounds/block_break.wav");
    soundEffects[1][1] = LoadSound("assets/sounds/win.wav");
    soundEffects[1][2] = LoadSound("assets/sounds/lose.wav");

    PlaySound(soundEffects[0][1]); // Backsound otomatis dimainkan saat game dimulai
}

void UnloadSoundEffects()
{
    for (int i = 0; i < SOUNDEFFECT_ROWS; i++)
    {
        for (int j = 0; j < SOUNDEFFECT_COLS; j++)
        {
            UnloadSound(soundEffects[i][j]);
        }
    }
    CloseAudioDevice();
}

void PlaySoundEffect(int row, int col)
{
    if (row < SOUNDEFFECT_ROWS && col < SOUNDEFFECT_COLS)
    {
        PlaySound(soundEffects[row][col]);
    }
}
