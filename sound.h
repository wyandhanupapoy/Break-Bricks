#ifndef SOUND_H
#define SOUND_H

#include <raylib.h>

// 🔹 Inisialisasi & Pembersihan Efek Suara
void InitSoundEffects();
void UnloadSoundEffects();

// 🔹 Efek Suara
void PlayButtonClick();
void PlayPaddleHit();
void PlayBlockHit();
void PlayLoseLife();
void PlayGameOver();
void PlayGameWin();

// 🔹 Musik Latar
void PlayBackgroundMusic();
void StopBackgroundMusic();
void PauseMusic();
void ToggleMusic();
void ChangeMusic(const char *filename);
void UpdateMusic();

// 🔹 Kontrol Volume
void SetVolume(float volume);
void IncreaseVolume();
void DecreaseVolume();

#endif
