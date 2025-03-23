// Nama : Muhammad Raihan Abubakar
// Nama fitur : stopwatch
// deskripsi fitur : stopwatch berguna untuk menampilkan waktu yang terus bertambah dan akan terhenti saat permainan selesai

#ifndef STOPWATCH_H //mengecek apakah stopwatch_h sudah didefinisikan 
#define STOPWATCH_H

#include <stdbool.h>

#define STOPWATCH_ROWS 1 // untuk mendefinisikan jumlah baris dalam stopwatch
#define STOPWATCH_COLS 1 // untuk mendefinisikan jumlah kolom dalam stopwatch 

typedef struct {
    float time; // variable untuk menyimpan waktu
    bool running; // variable untuk menyimpan status stopwatch
} Stopwatch;

void InitStopwatch(Stopwatch sw[][STOPWATCH_COLS]); // untuk menginisialisasi stopwatch
void UpdateStopwatch(Stopwatch sw[][STOPWATCH_COLS]); // untuk menambah waktu ke stopwatch
void DrawStopwatch(Stopwatch sw[][STOPWATCH_COLS]); // untuk menampilkan stopwatch ke layar 

#endif
