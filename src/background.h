/*
Nama Pembuat:   Wyandhanu Maulidan Nugraha
Nama Fitur:     Background
Deskripsi:      Fitur background untuk menampilkan efek latar belakang
                Dimodifikasi menggunakan linked list
*/

#ifndef BACKGROUND_H
#define BACKGROUND_H

#include <raylib.h>

// Struktur untuk bintang menggunakan linked list
typedef struct StarNode {
    Vector2 position;
    float speed;
    float brightness;  // 0.0f - 1.0f untuk kecerahan bintang
    struct StarNode* next;
} StarNode;

// Fungsi inisialisasi dan update background
void InitBackground();
void UpdateBackground();
void DrawBackground();

// Fungsi tambahan untuk linked list
void AddStar();
void RemoveStar();
void CleanupBackground();

#endif // BACKGROUND_H