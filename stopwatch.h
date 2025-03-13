#ifndef STOPWATCH_H
#define STOPWATCH_H

#include "raylib.h"

// Renamed to avoid conflicts with other headers
#define STOPWATCH_ROWS 1  // Bisa ditambah jika ingin lebih dari satu stopwatch
#define STOPWATCH_COLS 1

// Struktur Stopwatch
typedef struct {
    float time;   // Waktu berjalan dalam detik
    bool running; // Status apakah stopwatch berjalan atau tidak
} Stopwatch;

// Deklarasi fungsi
void InitStopwatch(Stopwatch sw[STOPWATCH_ROWS][STOPWATCH_COLS]);
void UpdateStopwatch(Stopwatch sw[STOPWATCH_ROWS][STOPWATCH_COLS]);
void DrawStopwatch(Stopwatch sw[STOPWATCH_ROWS][STOPWATCH_COLS]);

#endif