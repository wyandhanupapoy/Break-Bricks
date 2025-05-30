/*
Nama Pembuat:   Wyandhanu Maulidan Nugraha
NIM:abort       241511092
Nama Fitur:     Background
Deskripsi:      Fitur background untuk menampilkan efek latar belakang
                Dimodifikasi menggunakan linked list
*/

#include "background.h"
#include <math.h>
#include <stdlib.h>

static StarNode* starHead = NULL;
static int starCount = 0;
static const int MAX_STARS = 100;

static Color gradientTop = {10, 10, 50, 255};     // Warna atas (gelap)
static Color gradientBottom = {30, 30, 100, 255}; // Warna bawah (lebih terang)
static float gradientOffset = 0;                  // Perubahan warna untuk animasi

// 🔹 Inisialisasi efek background
void InitBackground() {
    // Memastikan tidak ada memory leak jika InitBackground dipanggil lebih dari sekali
    CleanupBackground();
    
    // Membuat bintang awal
    for (int i = 0; i < MAX_STARS; i++) {
        AddStar();
    }
}

// 🔹 Menambahkan bintang baru ke linked list
void AddStar() {
    if (starCount >= MAX_STARS) return;
    
    StarNode* newStar = (StarNode*)malloc(sizeof(StarNode));
    if (!newStar) return; // Gagal alokasi memori
    
    // Inisialisasi data bintang baru
    newStar->position = (Vector2){GetRandomValue(0, 1000), GetRandomValue(0, 650)};
    newStar->speed = GetRandomValue(1, 3);
    newStar->brightness = GetRandomValue(50, 100) / 100.0f;
    newStar->next = NULL;
    
    // Menyambungkan ke linked list
    if (starHead == NULL) {
        starHead = newStar;
    } else {
        // Menambahkan di awal list (lebih efisien)
        newStar->next = starHead;
        starHead = newStar;
    }
    
    starCount++;
}

// 🔹 Menghapus bintang dari linked list
void RemoveStar() {
    if (starHead == NULL) return;
    
    StarNode* temp = starHead;
    starHead = starHead->next;
    free(temp);
    starCount--;
}

// 🔹 Membersihkan semua bintang (untuk cleanup sebelum program berakhir)
void CleanupBackground() {
    while (starHead != NULL) {
        StarNode* temp = starHead;
        starHead = starHead->next;
        free(temp);
    }
    starCount = 0;
}

// 🔹 Update animasi background (gradasi + bintang jatuh)
void UpdateBackground() {
    // Gradasi warna bergerak
    gradientOffset += 0.005f;
    gradientTop.r = (int)(20 + sin(gradientOffset) * 20);
    gradientTop.g = (int)(20 + cos(gradientOffset) * 20);
    gradientBottom.b = (int)(100 + sin(gradientOffset) * 30);

    // Gerakan bintang jatuh menggunakan linked list
    StarNode* current = starHead;
    StarNode* prev = NULL;
    
    while (current != NULL) {
        current->position.y += current->speed;
        
        // Bintang keluar dari layar, reset posisi
        if (current->position.y > 650) {
            current->position.y = 0;
            current->position.x = GetRandomValue(0, 1000);
            current->brightness = GetRandomValue(50, 100) / 100.0f; // Kecerahan acak baru
        }
        
        prev = current;
        current = current->next;
    }
    
    // Acak menambah bintang baru (untuk variasi)
    if (GetRandomValue(0, 100) < 2 && starCount < MAX_STARS) {
        AddStar();
    }
}

// 🔹 Gambar animasi background
void DrawBackground() {
    // Gradasi background
    DrawRectangleGradientV(0, 0, 1000, 650, gradientTop, gradientBottom);

    // Efek bintang jatuh menggunakan linked list
    StarNode* current = starHead;
    
    while (current != NULL) {
        Color starColor = {
            (unsigned char)(255 * current->brightness),
            (unsigned char)(255 * current->brightness),
            (unsigned char)(255 * current->brightness),
            255
        };
        DrawCircleV(current->position, 1 + current->brightness, starColor);
        current = current->next;
    }
}