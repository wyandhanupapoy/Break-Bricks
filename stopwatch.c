#include "stopwatch.h"
#include <stdio.h>
#include <math.h>

// Inisialisasi stopwatch
void InitStopwatch(Stopwatch sw[STOPWATCH_ROWS][STOPWATCH_COLS]) {
    for (int i = 0; i < STOPWATCH_ROWS; i++) {
        for (int j = 0; j < STOPWATCH_COLS; j++) {
            sw[i][j].time = 0.0f;
            sw[i][j].running = true; // Stopwatch mulai berjalan
        }
    }
}

// Update waktu stopwatch jika berjalan
void UpdateStopwatch(Stopwatch sw[STOPWATCH_ROWS][STOPWATCH_COLS]) {
    for (int i = 0; i < STOPWATCH_ROWS; i++) {
        for (int j = 0; j < STOPWATCH_COLS; j++) {
            if (sw[i][j].running) {
                sw[i][j].time += GetFrameTime(); // Tambahkan waktu setiap frame
            }
        }
    }
}

// Menampilkan stopwatch di layar
void DrawStopwatch(Stopwatch sw[STOPWATCH_ROWS][STOPWATCH_COLS]) {
    char timeText[20];

    for (int i = 0; i < STOPWATCH_ROWS; i++) {
        for (int j = 0; j < STOPWATCH_COLS; j++) {
            sprintf(timeText, "Time: %.2f", sw[i][j].time);
            DrawText(timeText, 600, 50, 30, BLACK); // Posisi atas layar
        }
    }
}

// Reset stopwatch ke 0
void ResetStopwatch(Stopwatch sw[STOPWATCH_ROWS][STOPWATCH_COLS]) {
    for (int i = 0; i < STOPWATCH_ROWS; i++) {
        for (int j = 0; j < STOPWATCH_COLS; j++) {
            sw[i][j].time = 0.0f;
            sw[i][j].running = true;
        }
    }
}
