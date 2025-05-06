#include "stopwatch.h"
#include <stdio.h>
#include <stdlib.h>
#include <raylib.h>

// Inisialisasi linked list stopwatch sebanyak 'count' node
void InitStopwatch(Stopwatch** head, int count) {
    *head = NULL;
    for (int i = 0; i < count; i++) {
        Stopwatch* newNode = malloc(sizeof(Stopwatch));
        newNode->time = 0.0f;
        newNode->running = true;
        newNode->next = *head;
        *head = newNode;
    }
}


// Update waktu semua stopwatch jika berjalan
void UpdateStopwatch(Stopwatch* head) {
    Stopwatch* current = head;
    while (current != NULL) {
        if (current->running) {
            current->time += GetFrameTime();
        }
        current = current->next;
    }
}

// Menampilkan stopwatch di layar
void DrawStopwatch(Stopwatch* head) {
    Stopwatch* current = head;
    int y = 80;
    char timeText[20];

    while (current != NULL) {
        sprintf(timeText, "Time: %.2f", current->time);
        DrawText(timeText, 870, y, 20, WHITE);
        y += 30; // Geser ke bawah untuk tiap stopwatch
        current = current->next;
    }
}
