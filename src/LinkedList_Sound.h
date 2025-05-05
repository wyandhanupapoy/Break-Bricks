//Nama Pembuat: Siti Soviyyah
//Nama Fitur: Header sound.h
//Deskripsi: File ini berguna untuk memanggil fungsi dari file sound.c

#ifndef LINKEDLIST_SOUND_H
#define LINKEDLIST_SOUND_H

#include "raylib.h"

// -------------------------
// Struktur Data
// -------------------------

// Node untuk Single Linked List Sound
typedef struct SoundNode {
    char name[32];
    Sound sound;
    struct SoundNode *next;
} SoundNode;

// Node untuk Circular Linked List Music
typedef struct MusicNode {
    char filename[64];
    Music music;
    struct MusicNode *next;
} MusicNode;

// -------------------------
// Fungsi Sound Effect
// -------------------------

void InitSoundEffects();
void AddSound(const char *name, const char *filepath);
Sound GetSoundByName(const char *name);
void PlaySoundEffect(const char *name);
void UnloadSoundEffects();

// -------------------------
// Fungsi Background Music
// -------------------------

void InitBackgroundMusic();
void AddBackgroundMusic(const char *filepath);
void PlayBackgroundMusic();
void SetCurrentMusicToHead();
void UpdateMusic();
void NextMusic();
void ToggleMusic();
void StopBackgroundMusic();
void UnloadBackgroundMusic();

// -------------------------
// Volume Control
// -------------------------

void SetVolume(float newVolume);
void IncreaseVolume();
void DecreaseVolume();

#endif // SOUND_H
