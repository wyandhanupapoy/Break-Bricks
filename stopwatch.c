// Nama : Muhammad Raihan Abubakar
// Nama fitur : stopwatch
// deskripsi fitur : stopwatch berguna untuk menampilkan waktu yang terus bertambah dan akan terhenti saat permainan selesai

#include "stopwatch.h"
#include <stdio.h>
#include <raylib.h>

// Inisialisasi stopwatch
void InitStopwatch(Stopwatch sw[STOPWATCH_ROWS][STOPWATCH_COLS]) {
    for (int i = 0; i < STOPWATCH_ROWS; i++) { // looping untuk setiap baris
        for (int j = 0; j < STOPWATCH_COLS; j++) { // looping untuk setiap kolom 
            sw[i][j].time = 0.0f; // set waktu awal ke 0
            sw[i][j].running = true; // Stopwatch mulai berjalan
        }
    }
}

// Update waktu stopwatch jika berjalan
void UpdateStopwatch(Stopwatch sw[STOPWATCH_ROWS][STOPWATCH_COLS]) {
    for (int i = 0; i < STOPWATCH_ROWS; i++) { 
        for (int j = 0; j < STOPWATCH_COLS; j++) { // untuk mengecek apakah stopwatch sedang berjalan atau tidak 
            if (sw[i][j].running) { // jika stopwatch berjalan 
                sw[i][j].time += GetFrameTime(); // Tambahkan waktu setiap frame
            }
        }
    }
}

// Menampilkan stopwatch di layar
void DrawStopwatch(Stopwatch sw[STOPWATCH_ROWS][STOPWATCH_COLS]) { 
    char timeText[20]; // variabel untuk menyimpan teks waktu 

    for (int i = 0; i < STOPWATCH_ROWS; i++) { 
        for (int j = 0; j < STOPWATCH_COLS; j++) { 
            sprintf(timeText, "Time: %.2f", sw[i][j].time); //untuk menyimpan waktu ke dalam format teks
            DrawText(timeText, 870, 80, 20, WHITE); // koordinat x,y, ukuran font, dan warna teks yang ditampilkan 
        }
    }
}
