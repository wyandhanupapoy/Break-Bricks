// Nama : Muhammad Raihan Abubakar
// Nama fitur : paddle (pakai linked list)
// Deskripsi : paddle berfungsi untuk memantulkan dan mengarahkan bola agar bisa menghancurkan block

#include "linkedlistpaddle.h"
#include <stdlib.h>

#define SCREEN_WIDTH 830
#define SCREEN_HEIGHT 600

Paddle* CreatePaddle(float x, float y) {
    Paddle* newPaddle = (Paddle*)malloc(sizeof(Paddle));
    if (newPaddle != NULL) {
        newPaddle->rect = (Rectangle){x, y, PADDLE_WIDTH, PADDLE_HEIGHT};
        newPaddle->speed = (Vector2){PADDLE_SPEED, PADDLE_SPEED};
        newPaddle->next = NULL;
        newPaddle->prev = NULL; // Inisialisasi prev ke NULL
    }
    return newPaddle;
}

void AddPaddle(Paddle** head, float x, float y) {
    Paddle* newPaddle = CreatePaddle(x, y);
    if (*head == NULL) {
        *head = newPaddle;
    } else {
        Paddle* current = *head;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = newPaddle;
        newPaddle->prev = current;   // <<-- hubungkan pointer prev ke node sebelumnya
    }
}

void InitPaddles(Paddle** head) {
    // Di awal, buat 1 paddle di tengah layar
    float startX = (SCREEN_WIDTH - PADDLE_WIDTH) / 2;
    float startY = SCREEN_HEIGHT - PADDLE_HEIGHT - 10;
    AddPaddle(head, startX, startY);
}

void UpdatePaddles(Paddle* activePaddle) {
    if (activePaddle == NULL) return;

    if (IsKeyDown(KEY_LEFT) && activePaddle->rect.x > 0) {
        activePaddle->rect.x -= activePaddle->speed.x;
    }
        if (IsKeyDown(KEY_RIGHT) && activePaddle->rect.x < SCREEN_WIDTH - PADDLE_WIDTH) {
            activePaddle->rect.x += activePaddle->speed.x;
        }
    }
   

void DrawPaddles(Paddle* head) {
    Paddle* current = head;
    while (current != NULL) {
        DrawRectangleRec(current->rect, (Color){0, 255, 255, 255});
        current = current->next;
    }
}

void FreePaddles(Paddle* head) {
    Paddle* current = head;
    while (current != NULL) {
        Paddle* next = current->next;
        free(current);
        current = next;
    }
}