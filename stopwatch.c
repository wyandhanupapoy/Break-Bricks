#include "stopwatch.h"
#include <stdio.h>

// Inisialisasi stopwatch
void InitStopwatch(Stopwatch sw[ROWS][COLS]) {
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            sw[i][j].time = 0.0f;
            sw[i][j].running = true; // Stopwatch mulai berjalan
        }
    }
}

// Update waktu stopwatch jika berjalan
void UpdateStopwatch(Stopwatch sw[ROWS][COLS]) {
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            if (sw[i][j].running) {
                sw[i][j].time += GetFrameTime(); // Tambahkan waktu setiap frame
            }
        }
    }
}

// Menampilkan stopwatch di layar
void DrawStopwatch(Stopwatch sw[ROWS][COLS]) {
    char timeText[20];

    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            sprintf(timeText, "Time: %.2f", sw[i][j].time);
            DrawText(timeText, 600, 200, 30, BLACK); // Posisi tengah layar
        }
    }
}
