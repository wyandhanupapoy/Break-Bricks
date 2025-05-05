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
    }
}

void InitPaddles(Paddle** head) {
    // Di awal, buat 1 paddle di tengah layar
    float startX = (SCREEN_WIDTH - PADDLE_WIDTH) / 2;
    float startY = SCREEN_HEIGHT - PADDLE_HEIGHT - 10;
    AddPaddle(head, startX, startY);
}

void UpdatePaddles(Paddle* head) {
    Paddle* current = head;
    while (current != NULL) {
        if (IsKeyDown(KEY_LEFT) && current->rect.x > 0) {
            current->rect.x -= current->speed.x;
        }
        if (IsKeyDown(KEY_RIGHT) && current->rect.x < SCREEN_WIDTH - PADDLE_WIDTH) {
            current->rect.x += current->speed.x;
        }
        if (IsKeyDown(KEY_UP) && current->rect.y > 0) {
            current->rect.y -= current->speed.y;
        }
        if (IsKeyDown(KEY_DOWN) && current->rect.y < SCREEN_HEIGHT - PADDLE_HEIGHT) {
            current->rect.y += current->speed.y;
        }
        current = current->next;
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