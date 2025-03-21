#include "sound.h"
#include "raylib.h"

// Sound effect variabel
static Sound buttonClick;
static Sound paddleHit;
static Sound blockHit;
static Sound loseLife;
static Sound gameOverSound;
static Sound gameWinSound;

void InitSoundEffects()
{
    InitAudioDevice();

    // Load sound file (sesuaikan path dengan file yang kamu punya)
    buttonClick = LoadSound("assets/sounds/button_click.wav");
    paddleHit = LoadSound("assets/sounds/paddle_hit.wav");
    blockHit = LoadSound("assets/sounds/block_hit.wav");
    loseLife = LoadSound("assets/sounds/lose_life.wav");
    gameOverSound = LoadSound("assets/sounds/game_over.wav");
    gameWinSound = LoadSound("assets/sounds/game_win.wav");
}

void UnloadSoundEffects()
{
    UnloadSound(buttonClick);
    UnloadSound(paddleHit);
    UnloadSound(blockHit);
    UnloadSound(loseLife);
    UnloadSound(gameOverSound);
    UnloadSound(gameWinSound);

    CloseAudioDevice();
}

void PlayButtonClick()
{
    PlaySound(buttonClick);
}

void PlayPaddleHit()
{
    PlaySound(paddleHit);
}

void PlayBlockHit()
{
    PlaySound(blockHit);
}

void PlayLoseLife()
{
    PlaySound(loseLife);
}

void PlayGameOver()
{
    PlaySound(gameOverSound);
}

void PlayGameWin()
{
    PlaySound(gameWinSound);
}
