//Nama Pembuat: Siti Soviyyah
//Nama Fitur: Header sound.h
//Deskripsi: File ini berguna untuk memanggil fungsi dari file sound.c


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
void PlayPowerUp();
void PlayGameOver();
void PlayGameWin();
void PlayPowerUpSound();

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
