// Nama Pembuat: Muhammad Brata Hadinata
// Nama Fitur: nyawa.h
// Deskripsi: Header file untuk modul sistem nyawa pemain.
//            Nyawa dikelola sebagai hitungan integer, dengan dukungan tampilan visual.

#ifndef NYAWA_H
#define NYAWA_H

#include <raylib.h>
#include <stdbool.h> // Untuk bool

#define MAX_DISPLAY_LIVES 5   // Jumlah maksimum ikon nyawa yang akan ditampilkan.
                              // Sesuaikan jika Anda ingin menampilkan lebih banyak atau lebih sedikit ikon.
#define DEFAULT_LIFE_ICON_SIZE 20 // Ukuran default ikon nyawa
#define LIFE_ICON_SPACING 5     // Jarak antar ikon nyawa

// 🔹 Fungsi untuk inisialisasi dan manajemen status nyawa
void InitLivesSystem(int initialLives);
void DecreaseLife(void);
bool HasLivesLeft(void); // Menggantikan AnyLivesLeft

// 🔹 Fungsi untuk tampilan nyawa
void LoadLifeTexture(void); // Menggantikan LoadNyawaTexture
void UnloadLifeTexture(void); // Menggantikan UnloadNyawaTexture
void SetLivesDisplayPosition(float x, float y); // Menggantikan SetNyawaPosition
void SetLifeIconSize(float size); // Menggantikan SetNyawaSize
void DrawLives(void); // Menggantikan DrawNyawa

#endif // NYAWA_H