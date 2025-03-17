#include "stopwatch.h"
#include "layout.h"
#include <stdio.h>
#include "raylib.h"

void InitStopwatch(Stopwatch sw[STOPWATCH_ROWS][STOPWATCH_COLS]) {
    for (int i = 0; i < STOPWATCH_ROWS; i++) {
        for (int j = 0; j < STOPWATCH_COLS; j++) {
            sw[i][j].time = 0.0f;
            sw[i][j].running = true;
        }
    }
}

void UpdateStopwatch(Stopwatch sw[STOPWATCH_ROWS][STOPWATCH_COLS]) {
    for (int i = 0; i < STOPWATCH_ROWS; i++) {
        for (int j = 0; j < STOPWATCH_COLS; j++) {
            if (sw[i][j].running) {
                sw[i][j].time += GetFrameTime();
            }
        }
    }
}

void DrawStopwatch(Stopwatch sw[STOPWATCH_ROWS][STOPWATCH_COLS]) {
    char timeText[20];
    sprintf(timeText, "Time: %.2f", sw[0][0].time);
    DrawText(timeText, SCREEN_WIDTH - 190, 10, 20, BLACK); // Pindahkan ke pojok kanan atas panel kanan
}

void ResetStopwatch(Stopwatch sw[STOPWATCH_ROWS][STOPWATCH_COLS]) {
    sw[0][0].time = 0.0f;
    sw[0][0].running = true;
}
