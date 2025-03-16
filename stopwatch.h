#ifndef STOPWATCH_H
#define STOPWATCH_H

#include "raylib.h"

#define STOPWATCH_ROWS 1  // Bisa ditambah jika ingin lebih dari satu stopwatch
#define STOPWATCH_COLS 1

typedef struct {
    float time;
    bool running;
} Stopwatch;

void InitStopwatch(Stopwatch sw[STOPWATCH_ROWS][STOPWATCH_COLS]);
void UpdateStopwatch(Stopwatch sw[STOPWATCH_ROWS][STOPWATCH_COLS]);
void DrawStopwatch(Stopwatch sw[STOPWATCH_ROWS][STOPWATCH_COLS]);

#endif
