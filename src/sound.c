//Nama Pembuat: Siti Soviyyah
//Nama Fitur: Sound Effect
//Deskripsi: Fitur ini berguna untuk menambahkan efek suara dan musik latar untuk meningkatkan pengalaman bermain game.

#include "sound.h"
#include "raylib.h"
#include <stdio.h>

// Variabel untuk efek suara
static Sound buttonClick;
static Sound paddleHit;
static Sound blockHit;
static Sound loseLife;
static Sound gameOverSound;
static Sound gameWinSound;
static Music backgroundMusic;

static float volume = 0.5f;  // Default volume (0.0 - 1.0)
static bool musicPlaying = false;
static bool musicPaused = false;

// 🔹 Inisialisasi Efek Suara & Musik
void InitSoundEffects()
{
    InitAudioDevice();

    // Load efek suara
    buttonClick = LoadSound("assets/sounds/click_button.mp3");
    paddleHit = LoadSound("assets/sounds/paddle_hit.wav");
    blockHit = LoadSound("assets/sounds/block_hit.wav");
    loseLife = LoadSound("assets/sounds/lose_life.wav");
    gameOverSound = LoadSound("assets/sounds/game_over.wav");
    gameWinSound = LoadSound("assets/sounds/game_win.wav");

    // Load background music
    backgroundMusic = LoadMusicStream("assets/sounds/background_music.mp3");
    SetMusicVolume(backgroundMusic, volume);
}

// 🔹 Membersihkan Efek Suara & Musik
void UnloadSoundEffects()
{
    UnloadSound(buttonClick);
    UnloadSound(paddleHit);
    UnloadSound(blockHit);
    UnloadSound(loseLife);
    UnloadSound(gameOverSound);
    UnloadSound(gameWinSound);
    UnloadMusicStream(backgroundMusic);

    CloseAudioDevice();
}

// 🔹 Fungsi Efek Suara
void PlayButtonClick()  { PlaySound(buttonClick); }
void PlayPaddleHit()    { PlaySound(paddleHit); }
void PlayBlockHit()     { PlaySound(blockHit); }
void PlayLoseLife()     { PlaySound(loseLife); }
void PlayGameOver()     { PlaySound(gameOverSound); }
void PlayGameWin()      { PlaySound(gameWinSound); }
void PlayPowerUpSound() { PlaySound(blockHit); }  // Gunakan efek suara block hit untuk power-up

// 🔹 Memainkan Musik Latar
void PlayBackgroundMusic()
{
    if (!musicPlaying) {
        PlayMusicStream(backgroundMusic);
        musicPlaying = true;
        musicPaused = false;
    }
}

// 🔹 Menghentikan Musik Latar
void StopBackgroundMusic()
{
    StopMusicStream(backgroundMusic);
    musicPlaying = false;
    musicPaused = false;
}

// 🔹 Pause/Resume Musik Latar
void PauseMusic()
{
    if (musicPlaying && !musicPaused) {
        PauseMusicStream(backgroundMusic);
        musicPaused = true;
    } else if (musicPaused) {
        ResumeMusicStream(backgroundMusic);
        musicPaused = false;
    }
}

// 🔹 Toggle Musik (Play/Pause)
void ToggleMusic()
{
    if (musicPlaying) {
        StopMusicStream(backgroundMusic);
        musicPlaying = false;
    } else {
        PlayMusicStream(backgroundMusic);
        musicPlaying = true;
    }
}

// 🔹 Mengganti Musik Latar Secara Dinamis
void ChangeMusic(const char *filename)
{
    StopMusicStream(backgroundMusic);
    UnloadMusicStream(backgroundMusic);

    backgroundMusic = LoadMusicStream(filename);
    SetMusicVolume(backgroundMusic, volume);
    PlayMusicStream(backgroundMusic);

    musicPlaying = true;
}

// 🔹 Perbarui Musik (Dipanggil Setiap Frame)
void UpdateMusic()
{
    if (!musicPaused) {
        UpdateMusicStream(backgroundMusic);
    }
}

// 🔹 Mengatur Volume Semua Efek Suara & Musik
void SetVolume(float newVolume)
{
    volume = newVolume;
    SetSoundVolume(buttonClick, volume);
    SetSoundVolume(paddleHit, volume);
    SetSoundVolume(blockHit, volume);
    SetSoundVolume(loseLife, volume);
    SetSoundVolume(gameOverSound, volume);
    SetSoundVolume(gameWinSound, volume);
    SetMusicVolume(backgroundMusic, volume);
}

// 🔹 Menaikkan Volume
void IncreaseVolume()
{
    if (volume < 1.0f)
    {
        volume += 0.1f;
        if (volume > 1.0f) volume = 1.0f;
        SetVolume(volume);
    }
}

// 🔹 Menurunkan Volume
void DecreaseVolume()
{
    if (volume > 0.0f)
    {
        volume -= 0.1f;
        if (volume < 0.0f) volume = 0.0f;
        SetVolume(volume);
    }
}
