#include "soundeffect.h"
#include <raylib.h>         // Untuk fungsi grafis dan input

// Panggil saat game dimulai
LoadSoundEffects();

// Contoh pemakaian suara dalam game:
if (IsKeyPressed(KEY_SPACE))
{
    PlaySoundEffect(0, 0); // Menu Click Sound
    gameState = GAME_PLAY;
}

if (bola mengenai paddle atau dinding)
{
    PlaySoundEffect(0, 2); // Ball Bounce Sound
}

if (bola menghancurkan blok)
{
    PlaySoundEffect(1, 0); // Block Break Sound
}

if (game menang)
{
    PlaySoundEffect(1, 1); // Win Sound
}

if (game kalah)
{
    PlaySoundEffect(1, 2); // Lose Sound
}

// Panggil saat game selesai
UnloadSoundEffects();
