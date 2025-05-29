// Nama Pembuat: Siti Soviyyah
// Nama Fitur: Header sound.h
// Deskripsi: File ini berguna untuk memanggil fungsi dari file sound.c (versi dinamis)

#ifndef SOUND_H
#define SOUND_H

#include <raylib.h>

// 🔹 Inisialisasi & Pembersihan Sistem Suara
void InitSoundSystem();    // Menggantikan InitSoundEffects
void UnloadSoundSystem();  // Menggantikan UnloadSoundEffects

// 🔹 Memainkan Efek Suara berdasarkan ID
void PlaySfx(const char* soundId); // Menggantikan semua PlayButtonClick(), PlayPaddleHit(), dll.

// 🔹 Musik Latar (fungsi tetap sama)
void PlayBackgroundMusic();
void StopBackgroundMusic();
void PauseMusic();
void ToggleMusic();
void ChangeMusic(const char *filename);
void UpdateMusic();

// 🔹 Kontrol Volume (fungsi tetap sama, implementasi di .c akan disesuaikan)
void SetVolume(float volume);
void IncreaseVolume();
void DecreaseVolume();

#endif