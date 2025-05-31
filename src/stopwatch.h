#ifndef STOPWATCH_H
#define STOPWATCH_H

#include <stdbool.h>

// Struktur stopwatch
typedef struct Stopwatch {
    float time;
    bool running;
    struct Stopwatch* next; // Pointer ke stopwatch berikutnya (linked list)
} Stopwatch;

// Fungsi-fungsi yang diperbarui
void InitStopwatch(Stopwatch** head, int count); // inisialisasi dengan jumlah stopwatch
void UpdateStopwatch(Stopwatch* head);
void DrawStopwatch(Stopwatch* head);

#endif
