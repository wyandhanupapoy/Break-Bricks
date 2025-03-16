// stopwatch.h
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
void ResetStopwatch(Stopwatch sw[][STOPWATCH_COLS]);

#endif
