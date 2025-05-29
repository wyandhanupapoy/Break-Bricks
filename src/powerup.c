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

void AddPowerUp(PowerUpList *list, PowerUpType type, Vector2 position) {
    PowerUpNode *newNode = (PowerUpNode*)malloc(sizeof(PowerUpNode));
    if (!newNode) return;

    newNode->rect = (Rectangle){position.x, position.y, POWERUP_WIDTH, POWERUP_HEIGHT};
    newNode->type = type;
    // newNode->texture = texture;
    newNode->active = true;
    newNode->duration = 5.0f; // Durasi 10 detik
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
            Color color;
            const char *symbol;

            switch (curr->type) {
                case POWERUP_TRIPLE_BALL:
                    color = RED;
                    symbol = "B";  // B untuk "Ball" (3 bola)
                    break;
                case POWERUP_LONG_PADDLE:
                    color = BLUE;
                    symbol = "P";  // P untuk "Paddle"
                    break;
                default:
                    color = GRAY;
                    symbol = "?";
                    break;
            }

            // Gambar persegi
            DrawRectangleRec(curr->rect, color);

            // Hitung posisi teks agar huruf di tengah persegi
            int fontSize = 20;
            int textWidth = MeasureText(symbol, fontSize);
            int textX = curr->rect.x + (curr->rect.width - textWidth) / 2;
            int textY = curr->rect.y + (curr->rect.height - fontSize) / 2;

            // Gambar huruf di tengah
            DrawText(symbol, textX, textY, fontSize, WHITE);
        }

        curr = curr->next;
    }
}

void ActivatePowerUp(PowerUpType type, Paddle *paddle, BolaList *bolaList, float duration) {
    PlayPowerUp();

    if (type == POWERUP_TRIPLE_BALL) {
        AddBola(bolaList, (Vector2){paddle->rect.x + paddle->rect.width/2, paddle->rect.y - 20}, (Vector2){-4, -6});
        AddBola(bolaList, (Vector2){paddle->rect.x + paddle->rect.width/2, paddle->rect.y - 20}, (Vector2){4, -6});
    }

    if (type == POWERUP_LONG_PADDLE) {
        // Tambah panjang paddle
        float newWidth = paddle->rect.width * 1.2f; // Tambah 20%
        float maxWidth = SCREEN_WIDTH - paddle->rect.x;
        paddle->rect.width = (newWidth > maxWidth) ? maxWidth : newWidth;
    }

    // Tambah ke daftar power-up aktif
    ActivePowerUp *newPower = (ActivePowerUp *)malloc(sizeof(ActivePowerUp));
    newPower->type = type;
    newPower->remainingTime = duration;
    newPower->next = paddle->activePowerUps;
    paddle->activePowerUps = newPower;
}

void UpdateActivePowerUps(Paddle *paddle, float deltaTime) {
    ActivePowerUp *curr = paddle->activePowerUps;
    ActivePowerUp *prev = NULL;

    while (curr != NULL) {
        curr->remainingTime -= deltaTime;

        if (curr->remainingTime <= 0) {
            // Efek habis, kurangi efeknya
            if (curr->type == POWERUP_LONG_PADDLE) {
                // Kembalikan sebagian panjang paddle (20%)
                paddle->rect.width *= 1.0f / 1.2f; // Balik dari pertambahan
            }

            // Hapus dari list
            if (prev == NULL) {
                paddle->activePowerUps = curr->next;
                free(curr);
                curr = paddle->activePowerUps;
            } else {
                prev->next = curr->next;
                free(curr);
                curr = prev->next;
            }
        } else {
            prev = curr;
            curr = curr->next;
        }
    }
}

void FreePowerUp(PowerUpList *list) {
    PowerUpNode *curr = list->head;
    while (curr != NULL) {
        PowerUpNode *next = curr->next;
        // UnloadTexture(curr->texture);
        free(curr);
        curr = next;
    }
    list->head = NULL;
}