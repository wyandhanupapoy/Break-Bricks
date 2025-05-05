//Nama Pembuat: Siti Soviyyah
//Nama Fitur: Sound Effect (Dengan Linked List)
//Deskripsi: Mengelola efek suara menggunakan single linked list dan musik latar menggunakan circular linked list.

#include "LinkedList_Sound.h"
#include "raylib.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


SoundNode *soundList = NULL;
MusicNode *musicHead = NULL;
MusicNode *currentMusic = NULL;

static float volume = 0.5f;
static bool musicPaused = false;

// 🔹 Menambahkan Sound ke Linked List
void AddSound(const char *name, const char *filepath) {
    SoundNode *newNode = (SoundNode *)malloc(sizeof(SoundNode));
    strcpy(newNode->name, name);
    newNode->sound = LoadSound(filepath);
    newNode->next = soundList;
    soundList = newNode;
}

// 🔹 Cari Sound Berdasarkan Nama
Sound GetSoundByName(const char *name) {
    SoundNode *curr = soundList;
    while (curr != NULL) {
        if (strcmp(curr->name, name) == 0) return curr->sound;
        curr = curr->next;
    }
    return (Sound){0}; // Kosong jika tidak ditemukan
}

// 🔹 Inisialisasi Efek Suara
void InitSoundEffects() {
    InitAudioDevice();
    AddSound("buttonClick", "assets/sounds/click_button.mp3");
    AddSound("paddleHit", "assets/sounds/paddle_hit.wav");
    AddSound("blockHit", "assets/sounds/block_hit.wav");
    AddSound("loseLife", "assets/sounds/lose_life.wav");
    AddSound("gameOver", "assets/sounds/game_over.wav");
    AddSound("gameWin", "assets/sounds/game_win.wav");
}

// 🔹 Mainkan Efek Suara Berdasarkan Nama
void PlaySoundEffect(const char *name) {
    Sound s = GetSoundByName(name);
    if (s.frameCount > 0) PlaySound(s);
}

// 🔹 Membersihkan Efek Suara
void UnloadSoundEffects() {
    SoundNode *curr = soundList;
    while (curr != NULL) {
        UnloadSound(curr->sound);
        SoundNode *temp = curr;
        curr = curr->next;
        free(temp);
    }
    soundList = NULL;
}

void InitBackgroundMusic() {
    AddBackgroundMusic("assets/sounds/background_music.mp3");
    AddBackgroundMusic("assets/sounds/gameplay_music.mp3");
}

// 🔹 Tambahkan Musik ke Circular Linked List
void AddBackgroundMusic(const char *filepath) {
    MusicNode *newNode = (MusicNode *)malloc(sizeof(MusicNode));
    strcpy(newNode->filename, filepath);
    newNode->music = LoadMusicStream(filepath);
    SetMusicVolume(newNode->music, volume);
    
    if (!musicHead) {
        musicHead = newNode;
        newNode->next = newNode;
    } else {
        MusicNode *temp = musicHead;
        while (temp->next != musicHead) temp = temp->next;
        temp->next = newNode;
        newNode->next = musicHead;
    }
}

// 🔹 Mainkan Musik Saat Ini
void PlayBackgroundMusic() {
    if (currentMusic) {
        PlayMusicStream(currentMusic->music);
        musicPaused = false;
    }
}

void SetCurrentMusicToHead() {
    currentMusic = musicHead;
}

// 🔹 Update Musik (Dipanggil Tiap Frame)
void UpdateMusic() {
    if (!musicPaused && currentMusic) {
        UpdateMusicStream(currentMusic->music);
    }
}

// 🔹 Ganti ke Musik Berikutnya
void NextMusic() {
    if (currentMusic) {
        StopMusicStream(currentMusic->music);
        currentMusic = currentMusic->next;
        PlayBackgroundMusic();
    }
}

// 🔹 Pause / Resume Musik
void ToggleMusic() {
    if (currentMusic) {
        if (musicPaused) {
            ResumeMusicStream(currentMusic->music);
            musicPaused = false;
        } else {
            PauseMusicStream(currentMusic->music);
            musicPaused = true;
        }
    }
}

// 🔹 Hentikan Semua Musik
void StopBackgroundMusic() {
    if (currentMusic) {
        StopMusicStream(currentMusic->music);
    }
}

// 🔹 Bersihkan Musik
void UnloadBackgroundMusic() {
    if (!musicHead) return;

    MusicNode *curr = musicHead;
    do {
        MusicNode *temp = curr;
        UnloadMusicStream(curr->music);
        curr = curr->next;
        free(temp);
    } while (curr != musicHead);

    musicHead = NULL;
    currentMusic = NULL;
}

// 🔹 Atur Volume Global (Efek Suara + Musik)
void SetVolume(float newVolume)
{
    volume = newVolume;

    // 🔸 Atur volume semua efek suara
    SoundNode *currSound = soundList;
    while (currSound != NULL) {
        SetSoundVolume(currSound->sound, volume);
        currSound = currSound->next;
    }

    // 🔸 Atur volume semua musik di circular linked list
    if (musicHead) {
        MusicNode *currMusic = musicHead;
        do {
            SetMusicVolume(currMusic->music, volume);
            currMusic = currMusic->next;
        } while (currMusic != musicHead);
    }
}

// 🔹 Naikkan Volume (maks 1.0)
void IncreaseVolume()
{
    if (volume < 1.0f) {
        volume += 0.1f;
        if (volume > 1.0f) volume = 1.0f;
        SetVolume(volume);
    }
}

// 🔹 Turunkan Volume (min 0.0)
void DecreaseVolume()
{
    if (volume > 0.0f) {
        volume -= 0.1f;
        if (volume < 0.0f) volume = 0.0f;
        SetVolume(volume);
    }
}
