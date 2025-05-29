// Nama Pembuat: Siti Soviyyah
// Nama Fitur: Sound Effect (versi dinamis)
// Deskripsi: Fitur ini menambahkan efek suara (dimuat sesuai kebutuhan) dan musik latar.

#include "sound.h"
#include "raylib.h"
#include <stdio.h>
#include <string.h> // Untuk strcmp

// Struktur untuk entri efek suara dalam registry
typedef struct {
    const char* id;       // ID unik untuk efek suara (misalnya, "button_click")
    const char* filePath; // Path ke file suara
    Sound sound;          // Objek Sound Raylib
    bool loaded;          // Status apakah suara sudah dimuat
} SoundEntry;

// Registry untuk semua efek suara yang diketahui
// Tambahkan entri baru di sini jika ada efek suara baru
#define MAX_SOUND_EFFECTS 10 // Sesuaikan dengan jumlah maksimum efek suara Anda
static SoundEntry soundRegistry[MAX_SOUND_EFFECTS];
static int soundCount = 0; // Jumlah efek suara yang terdaftar

// Variabel untuk musik latar dan volume (tetap sama)
static Music backgroundMusic;
static float volume = 0.5f;  // Default volume (0.0 - 1.0)
static bool musicPlaying = false;
static bool musicPaused = false;

// Fungsi helper internal untuk menambahkan entri ke registry
static void RegisterSound(const char* id, const char* filePath) {
    if (soundCount < MAX_SOUND_EFFECTS) {
        soundRegistry[soundCount].id = id;
        soundRegistry[soundCount].filePath = filePath;
        soundRegistry[soundCount].loaded = false;
        // soundRegistry[soundCount].sound diinisialisasi saat LoadSound
        soundCount++;
    } else {
        TraceLog(LOG_WARNING, "SOUND: Registry penuh, tidak dapat menambahkan: %s", id);
    }
}

// 🔹 Inisialisasi Sistem Suara
void InitSoundSystem() { // Menggantikan InitSoundEffects
    InitAudioDevice();

    // Daftarkan semua efek suara di sini (belum dimuat)
    RegisterSound("button_click", "assets/sounds/click_button.mp3");
    RegisterSound("paddle_hit", "assets/sounds/paddle_hit.wav");
    RegisterSound("block_hit", "assets/sounds/block_hit.wav");
    RegisterSound("lose_life", "assets/sounds/lose_life.wav");
    RegisterSound("power_up", "assets/sounds/powerup.wav"); // Asumsi ini adalah suara untuk power-up
    RegisterSound("game_over", "assets/sounds/game_over.wav");
    RegisterSound("game_win", "assets/sounds/game_win.wav");
    // Jika PlayPowerUpSound() sebelumnya memanggil PlaySound(blockHit), maka
    // di kode game, Anda akan memanggil PlaySfx("block_hit") atau PlaySfx("power_up")
    // tergantung suara mana yang diinginkan untuk event power-up.

    // Load background music (tetap sama)
    backgroundMusic = LoadMusicStream("assets/sounds/background_music.mp3");
    if (backgroundMusic.frameCount > 0) { // Cek apakah musik berhasil dimuat
         SetMusicVolume(backgroundMusic, volume);
    } else {
        TraceLog(LOG_WARNING, "SOUND: Gagal memuat background music.");
    }
}

// 🔹 Membersihkan Sistem Suara
void UnloadSoundSystem() { // Menggantikan UnloadSoundEffects
    // Unload semua efek suara yang sudah dimuat
    for (int i = 0; i < soundCount; i++) {
        if (soundRegistry[i].loaded) {
            UnloadSound(soundRegistry[i].sound);
            soundRegistry[i].loaded = false;
        }
    }

    if (backgroundMusic.frameCount > 0) {
        UnloadMusicStream(backgroundMusic);
    }
    CloseAudioDevice();
}

// 🔹 Memainkan Efek Suara berdasarkan ID
void PlaySfx(const char* soundId) {
    for (int i = 0; i < soundCount; i++) {
        if (strcmp(soundRegistry[i].id, soundId) == 0) {
            if (!soundRegistry[i].loaded) {
                // Muat suara jika belum dimuat
                soundRegistry[i].sound = LoadSound(soundRegistry[i].filePath);
                if (soundRegistry[i].sound.frameCount > 0) { // Cek apakah suara berhasil dimuat
                    soundRegistry[i].loaded = true;
                    SetSoundVolume(soundRegistry[i].sound, volume); // Terapkan volume saat ini
                    TraceLog(LOG_INFO, "SOUND: Dimuat '%s' dari '%s'", soundId, soundRegistry[i].filePath);
                } else {
                    TraceLog(LOG_WARNING, "SOUND: Gagal memuat efek suara ID: %s, Path: %s", soundId, soundRegistry[i].filePath);
                    return; // Gagal memuat, jangan coba mainkan
                }
            }
            // Mainkan suara jika sudah dimuat (atau baru saja berhasil dimuat)
            if (soundRegistry[i].loaded) {
                 PlaySound(soundRegistry[i].sound);
            }
            return;
        }
    }
    TraceLog(LOG_WARNING, "SOUND: Efek suara tidak ditemukan untuk ID: %s", soundId);
}

// --- Musik Latar & Kontrol Volume (Implementasi sebagian besar tetap sama) ---

// 🔹 Memainkan Musik Latar
void PlayBackgroundMusic() {
    if (backgroundMusic.frameCount == 0) {
        TraceLog(LOG_WARNING, "SOUND: Tidak ada background music untuk dimainkan.");
        return;
    }
    if (!musicPlaying) {
        PlayMusicStream(backgroundMusic);
        musicPlaying = true;
        musicPaused = false;
    }
}

// 🔹 Menghentikan Musik Latar
void StopBackgroundMusic() {
    if (backgroundMusic.frameCount == 0) return;
    StopMusicStream(backgroundMusic);
    musicPlaying = false;
    musicPaused = false;
}

// 🔹 Pause/Resume Musik Latar
void PauseMusic() {
    if (backgroundMusic.frameCount == 0) return;
    if (musicPlaying && !musicPaused) {
        PauseMusicStream(backgroundMusic);
        musicPaused = true;
    } else if (musicPaused) {
        ResumeMusicStream(backgroundMusic);
        musicPaused = false;
    }
}

// 🔹 Toggle Musik (Play/Stop)
void ToggleMusic() {
    if (backgroundMusic.frameCount == 0) {
        TraceLog(LOG_WARNING, "SOUND: Tidak ada background music untuk di-toggle.");
        return;
    }
    if (musicPlaying) {
        StopMusicStream(backgroundMusic); // Menggunakan Stop agar mulai dari awal jika diputar lagi
        musicPlaying = false;
        musicPaused = false; // Pastikan status pause juga reset
    } else {
        PlayMusicStream(backgroundMusic);
        musicPlaying = true;
        musicPaused = false;
    }
}

// 🔹 Mengganti Musik Latar Secara Dinamis
void ChangeMusic(const char *filename) {
    if (backgroundMusic.frameCount > 0) {
        StopMusicStream(backgroundMusic);
        UnloadMusicStream(backgroundMusic);
    }

    backgroundMusic = LoadMusicStream(filename);
    if (backgroundMusic.frameCount > 0) {
        SetMusicVolume(backgroundMusic, volume);
        PlayMusicStream(backgroundMusic);
        musicPlaying = true;
        musicPaused = false; // Reset status pause
    } else {
        TraceLog(LOG_WARNING, "SOUND: Gagal memuat musik baru dari: %s", filename);
        musicPlaying = false; // Pastikan status playing false jika gagal load
    }
}

// 🔹 Perbarui Musik (Dipanggil Setiap Frame)
void UpdateMusic() {
    if (musicPlaying && !musicPaused && backgroundMusic.frameCount > 0) {
        UpdateMusicStream(backgroundMusic);
    }
}

// 🔹 Mengatur Volume Semua Efek Suara & Musik
void SetVolume(float newVolume) {
    volume = newVolume;
    if (volume < 0.0f) volume = 0.0f;
    if (volume > 1.0f) volume = 1.0f;

    // Terapkan volume ke semua efek suara yang sudah dimuat
    for (int i = 0; i < soundCount; i++) {
        if (soundRegistry[i].loaded) {
            SetSoundVolume(soundRegistry[i].sound, volume);
        }
    }
    // Terapkan volume ke musik
    if (backgroundMusic.frameCount > 0) {
        SetMusicVolume(backgroundMusic, volume);
    }
}

// 🔹 Menaikkan Volume
void IncreaseVolume() {
    float newVolume = volume + 0.1f;
    if (newVolume > 1.0f) newVolume = 1.0f;
    SetVolume(newVolume); // Panggil SetVolume agar semua suara terupdate
}

// 🔹 Menurunkan Volume
void DecreaseVolume() {
    float newVolume = volume - 0.1f;
    if (newVolume < 0.0f) newVolume = 0.0f;
    SetVolume(newVolume); // Panggil SetVolume agar semua suara terupdate
}