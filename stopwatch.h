// Nama : Muhammad Raihan Abubakar
// Nama fitur : stopwatch
// deskripsi fitur : stopwatch berguna untuk menampilkan waktu yang terus bertambah dan akan terhenti saat permainan selesai

#ifndef STOPWATCH_H
#define STOPWATCH_H

#include <stdbool.h>

#define STOPWATCH_ROWS 1
#define STOPWATCH_COLS 1

typedef struct {
    float time;
    bool running;
} Stopwatch;

void InitStopwatch(Stopwatch sw[][STOPWATCH_COLS]);
void UpdateStopwatch(Stopwatch sw[][STOPWATCH_COLS]);
void DrawStopwatch(Stopwatch sw[][STOPWATCH_COLS]);

#endif
