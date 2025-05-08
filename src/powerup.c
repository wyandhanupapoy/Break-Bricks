#include "powerup.h"
#include "BOLA.h"
#include "paddle.h"
#include "sound.h"
#include <stdlib.h>

#define POWERUP_SPEED 3.0f
#define POWERUP_WIDTH 30
#define POWERUP_HEIGHT 30

void InitPowerUp(PowerUpList *list) {
    list->head = NULL;
}

void AddPowerUp(PowerUpList *list, PowerUpType type, Vector2 position, Texture2D texture) {
    PowerUpNode *newNode = (PowerUpNode*)malloc(sizeof(PowerUpNode));
    if (!newNode) return;

    newNode->rect = (Rectangle){position.x, position.y, POWERUP_WIDTH, POWERUP_HEIGHT};
    newNode->type = type;
    newNode->texture = texture;
    newNode->active = true;
    newNode->duration = 10.0f; // Durasi 10 detik
    newNode->next = list->head;
    list->head = newNode;
}

void UpdatePowerUp(PowerUpList *list, Paddle *paddle, BolaList *bolaList, float deltaTime) {
    PowerUpNode *prev = NULL;
    PowerUpNode *curr = list->head;

    while (curr != NULL) {
        if (!curr->active) {
            // Hapus node jika tidak aktif
            PowerUpNode *toDelete = curr;
            if (prev == NULL) list->head = curr->next;
            else prev->next = curr->next;
            
            curr = curr->next;
            free(toDelete);
            continue;
        }

        // Gerakkan power-up ke bawah
        curr->rect.y += POWERUP_SPEED;

        // Cek tabrakan dengan paddle
        if (CheckCollisionRecs(curr->rect, paddle->rect)) {
            ActivatePowerUp(curr->type, paddle, bolaList, curr->duration);
            curr->active = false;
        }

        // Hapus jika jatuh keluar layar
        if (curr->rect.y > GetScreenHeight()) {
            curr->active = false;
        }

        prev = curr;
        curr = curr->next;
    }
}

void DrawPowerUp(PowerUpList *list) {
    PowerUpNode *curr = list->head;
    while (curr != NULL) {
        if (curr->active) {
            DrawTexturePro(
                curr->texture,
                (Rectangle){0, 0, curr->texture.width, curr->texture.height},
                curr->rect,
                (Vector2){0, 0},
                0.0f,
                WHITE
            );
        }
        curr = curr->next;
    }
}

void ActivatePowerUp(PowerUpType type, Paddle *paddle, BolaList *bolaList, float duration) {
    PlayPowerUp();
    paddle->activePowerUp = type;  // Set jenis power-up aktif
    paddle->powerUpTimer = duration;  // Gunakan durasi dari power-up

    switch (type) {
        case POWERUP_TRIPLE_BALL:
            // Tambah 2 bola baru
            AddBola(bolaList, (Vector2){paddle->rect.x + paddle->rect.width/2, paddle->rect.y - 20}, (Vector2){-4, -6});
            AddBola(bolaList, (Vector2){paddle->rect.x + paddle->rect.width/2, paddle->rect.y - 20}, (Vector2){4, -6});
            break;

        case POWERUP_LONG_PADDLE:
            float newWidth = paddle->rect.width * 1.5f;
            float maxWidth = SCREEN_WIDTH - paddle->rect.x;  // Sesuaikan dengan batas layar
            paddle->rect.width = (newWidth > maxWidth) ? maxWidth : newWidth;
            break;
    }
}

void FreePowerUp(PowerUpList *list) {
    PowerUpNode *curr = list->head;
    while (curr != NULL) {
        PowerUpNode *next = curr->next;
        UnloadTexture(curr->texture);
        free(curr);
        curr = next;
    }
    list->head = NULL;
}