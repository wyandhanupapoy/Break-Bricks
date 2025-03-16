#ifndef NYAWA_H
#define NYAWA_H

#include "raylib.h"

// Konstanta jumlah baris dan kolom nyawa (contoh 1 baris, 5 nyawa)
#define NYAWA_BARIS 1
#define NYAWA_KOLOM 5

// Ukuran nyawa (misalnya persegi panjang kecil seperti icon hati)
#define NYAWA_WIDTH 30
#define NYAWA_HEIGHT 30
#define NYAWA_SPACING 10 // Jarak antar nyawa

// Struktur nyawa
typedef struct
{
    Rectangle rect; // Posisi dan ukuran nyawa
    bool aktif;     // Status nyawa (aktif atau hilang)
} Nyawa;

// Deklarasi fungsi
void InitNyawa(Nyawa nyawa[NYAWA_BARIS][NYAWA_KOLOM], int totalNyawa);
void DrawNyawa(Nyawa nyawa[NYAWA_BARIS][NYAWA_KOLOM]);
void KurangiNyawa(Nyawa nyawa[NYAWA_BARIS][NYAWA_KOLOM]);

#endif
