#ifndef STOPWATCH_H
#define STOPWATCH_H

#include "raylib.h"

// Konstanta untuk stopwatch
#define ROWS 1  // Bisa ditambah jika ingin lebih dari satu stopwatch
#define COLS 1

// Struktur Stopwatch
typedef struct {
    float time;   // Waktu berjalan dalam detik
    bool running; // Status apakah stopwatch berjalan atau tidak
} Stopwatch;

// Deklarasi fungsi
void InitStopwatch(Stopwatch sw[ROWS][COLS]);
void UpdateStopwatch(Stopwatch sw[ROWS][COLS]);
void DrawStopwatch(Stopwatch sw[ROWS][COLS]);

#endif
