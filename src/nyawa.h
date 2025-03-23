#ifndef NYAWA_H
#define NYAWA_H

#include <raylib.h>

#define NYAWA_BARIS 1
#define NYAWA_KOLOM 5  // Maksimum 5 nyawa yang bisa ditampilkan

#define DEFAULT_NYAWA_SIZE 20  // Ukuran default
#define NYAWA_SPACING 5  // Jarak antar nyawa

typedef struct
{
    Rectangle rect;
    bool aktif;
} Nyawa;

// 🔹 Fungsi dasar nyawa
void InitNyawa(Nyawa nyawa[NYAWA_BARIS][NYAWA_KOLOM], int totalNyawa);
void DrawNyawa(Nyawa nyawa[NYAWA_BARIS][NYAWA_KOLOM]);
void KurangiNyawa(Nyawa nyawa[NYAWA_BARIS][NYAWA_KOLOM]);
bool AnyLivesLeft(Nyawa nyawa[NYAWA_BARIS][NYAWA_KOLOM]);

// 🔹 Fungsi gambar nyawa
void LoadNyawaTexture();
void UnloadNyawaTexture();

// 🔹 Fungsi untuk mengatur posisi dan ukuran nyawa
void SetNyawaPosition(float x, float y);
void SetNyawaSize(float size);

#endif
