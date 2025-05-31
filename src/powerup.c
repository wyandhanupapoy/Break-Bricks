#include "powerup.h"
#include "paddle.h"  // For PaddleNode, ActivePowerUp, PADDLE_WIDTH_DEFAULT, MAX_PADDLE_WIDTH, PADDLE_GAME_AREA_WIDTH
#include "bola.h"    // For BolaList, AddBola, MIN_BALL_SPEED (jika digunakan di sini, pastikan BOLA.h menyediakannya)
#include "sound.h"   // For PlaySfx
#include <stdlib.h>  // For malloc, free
#include <raymath.h> // For fminf, fmaxf
#include <stdio.h>   // Untuk TraceLog (via raylib.h) atau sprintf

// Kecepatan jatuh power-up (unit per detik jika dikali deltaTime, atau per frame jika tidak)
#define POWERUP_FALL_SPEED 120.0f // Contoh: 120 piksel per detik
#define POWERUP_ITEM_WIDTH 30
#define POWERUP_ITEM_HEIGHT 30

// PADDLE_GAME_AREA_WIDTH dan MAX_PADDLE_WIDTH diambil dari paddle.h
// LONG_PADDLE_INCREMENT_VALUE dan POWERUP_DEFAULT_DURATION dari powerup.h

void InitPowerUp(PowerUpList *list) {
    if (!list) return;
    list->head = NULL;
}

void AddPowerUp(PowerUpList *list, PowerUpType type, Vector2 position) {
    if (!list) return;
    PowerUpNode *newNode = (PowerUpNode*)malloc(sizeof(PowerUpNode));
    if (!newNode) {
        TraceLog(LOG_WARNING, "POWERUP: Failed to allocate memory for new falling item.");
        return;
    }

    newNode->rect = (Rectangle){position.x - POWERUP_ITEM_WIDTH/2.0f, position.y, POWERUP_ITEM_WIDTH, POWERUP_ITEM_HEIGHT};
    newNode->type = type;
    newNode->active = true;
    newNode->next = list->head;
    list->head = newNode;
    // TraceLog(LOG_DEBUG, "POWERUP: Added new falling item type %d at %.1f, %.1f", type, position.x, position.y);
}

void ActivatePowerUp(PowerUpType type, struct PaddleNode *paddle_node, struct BolaList *bolaList) {
    if (!paddle_node) return;

    PlaySfx("power_up");

    // Logika untuk Triple Ball: Tambah bola, refresh timer jika sudah ada, atau tambah timer baru.
    if (type == POWERUP_TRIPLE_BALL) {
        if (bolaList) { // Pastikan bolaList valid
            Vector2 spawnPos = {paddle_node->rect.x + paddle_node->rect.width / 2.0f, paddle_node->rect.y - 15.0f};
            // Kecepatan bola baru bisa lebih bervariasi atau tetap
            AddBola(bolaList, spawnPos, (Vector2){(float)GetRandomValue(-5, -3), -MIN_BALL_SPEED});
            AddBola(bolaList, spawnPos, (Vector2){(float)GetRandomValue(3, 5), -MIN_BALL_SPEED});
        }

        // Untuk Triple Ball, kita bisa tetap refresh timer jika sudah ada, atau tambah baru.
        // Ini tidak "stack" efek visualnya, hanya durasi "mode" jika ada.
        ActivePowerUp* existingEffect = paddle_node->activePowerUps;
        bool foundInList = false;
        while(existingEffect != NULL) {
            if (existingEffect->type == type) {
                existingEffect->remainingTime = POWERUP_DEFAULT_DURATION; // Perbarui/reset durasi
                foundInList = true;
                // TraceLog(LOG_DEBUG, "POWERUP: Refreshed Triple Ball timer.");
                break;
            }
            existingEffect = existingEffect->next;
        }
        if (!foundInList) {
            ActivePowerUp *newEffect = (ActivePowerUp*)malloc(sizeof(ActivePowerUp));
            if (!newEffect) {
                TraceLog(LOG_WARNING, "POWERUP: Failed to allocate memory for Triple Ball active effect.");
                return;
            }
            newEffect->type = type;
            newEffect->remainingTime = POWERUP_DEFAULT_DURATION;
            newEffect->next = paddle_node->activePowerUps;
            paddle_node->activePowerUps = newEffect;
            // TraceLog(LOG_DEBUG, "POWERUP: Activated new Triple Ball effect.");
        }
    }
    // Logika untuk Long Paddle: Selalu tambah node timer baru, dan perpanjang paddle jika belum maks.
    else if (type == POWERUP_LONG_PADDLE) {
        // Perpanjang paddle jika belum mencapai batas maksimal
        if (paddle_node->rect.width < MAX_PADDLE_WIDTH) {
            paddle_node->rect.width += LONG_PADDLE_INCREMENT_VALUE;
            if (paddle_node->rect.width > MAX_PADDLE_WIDTH) {
                paddle_node->rect.width = MAX_PADDLE_WIDTH;
            }
            // Pastikan paddle tidak keluar batas setelah lebar diubah
            if (paddle_node->rect.x + paddle_node->rect.width > PADDLE_GAME_AREA_WIDTH) {
                paddle_node->rect.x = PADDLE_GAME_AREA_WIDTH - paddle_node->rect.width;
            }
            if (paddle_node->rect.x < 0) { // Jika penambahan membuat x < 0 (jarang terjadi jika di tengah)
                paddle_node->rect.x = 0;
            }
            // TraceLog(LOG_DEBUG, "POWERUP: Paddle lengthened. New width: %.1f", paddle_node->rect.width);
        } else {
            // TraceLog(LOG_DEBUG, "POWERUP: Paddle at max width, only adding timer for Long Paddle.");
        }

        // Selalu tambahkan instance timer baru untuk Long Paddle
        ActivePowerUp *newEffect = (ActivePowerUp*)malloc(sizeof(ActivePowerUp));
        if (!newEffect) {
            TraceLog(LOG_WARNING, "POWERUP: Failed to allocate memory for new Long Paddle active effect.");
            return;
        }
        newEffect->type = type;
        newEffect->remainingTime = POWERUP_DEFAULT_DURATION;
        newEffect->next = paddle_node->activePowerUps; // Tambahkan ke depan list
        paddle_node->activePowerUps = newEffect;
        // TraceLog(LOG_DEBUG, "POWERUP: Added new Long Paddle timer instance.");
    }
}

void UpdateActivePowerUps(struct PaddleNode *paddle_node, float deltaTime) {
    if (!paddle_node) return;

    ActivePowerUp *curr = paddle_node->activePowerUps;
    ActivePowerUp *prev = NULL;

    while (curr != NULL) {
        ActivePowerUp *nextEffect = curr->next;
        curr->remainingTime -= deltaTime;

        if (curr->remainingTime <= 0) {
            // TraceLog(LOG_DEBUG, "POWERUP: Effect type %d expired.", curr->type);
            if (curr->type == POWERUP_LONG_PADDLE) {
                // Kurangi lebar paddle sebesar satu increment
                paddle_node->rect.width -= LONG_PADDLE_INCREMENT_VALUE;
                if (paddle_node->rect.width < PADDLE_WIDTH_DEFAULT) {
                    paddle_node->rect.width = PADDLE_WIDTH_DEFAULT;
                }
                // Pastikan paddle tetap dalam batas setelah lebar dikurangi
                if (paddle_node->rect.x + paddle_node->rect.width > PADDLE_GAME_AREA_WIDTH) {
                    paddle_node->rect.x = PADDLE_GAME_AREA_WIDTH - paddle_node->rect.width;
                }
                if (paddle_node->rect.x < 0) {
                    paddle_node->rect.x = 0;
                }
                // TraceLog(LOG_DEBUG, "POWERUP: Long Paddle segment expired. New width: %.1f", paddle_node->rect.width);
            }

            // Hapus efek dari daftar
            if (prev == NULL) { // Jika node yang dihapus adalah head
                paddle_node->activePowerUps = nextEffect;
            } else {
                prev->next = nextEffect;
            }
            free(curr);
            curr = nextEffect; // Lanjutkan iterasi dengan node berikutnya
        } else {
            prev = curr; // Hanya majukan prev jika curr tidak dihapus
            curr = nextEffect;
        }
    }
}

void UpdatePowerUp(PowerUpList *fallingPowerUpList, struct PaddleList *paddleList, struct BolaList *bolaList, float deltaTime) {
    if (!fallingPowerUpList) return;

    PowerUpNode *prev = NULL;
    PowerUpNode *curr = fallingPowerUpList->head;

    while (curr != NULL) {
        PowerUpNode *nextNode = curr->next;

        if (!curr->active) {
            if (prev == NULL) {
                fallingPowerUpList->head = nextNode;
            } else {
                prev->next = nextNode;
            }
            free(curr);
            curr = nextNode;
            continue;
        }

        curr->rect.y += POWERUP_FALL_SPEED * deltaTime; // Kecepatan jatuh per detik

        bool collected = false;
        if (paddleList && paddleList->head) {
            PaddleNode *playerPaddle = paddleList->head; // Asumsi single player
            if (CheckCollisionRecs(curr->rect, playerPaddle->rect)) {
                ActivatePowerUp(curr->type, playerPaddle, bolaList);
                curr->active = false;
                collected = true;
            }
        }

        // Despawn jika jatuh keluar layar (beri sedikit buffer)
        if (curr->rect.y > GetScreenHeight() + curr->rect.height) {
            curr->active = false;
        }

        if (curr && curr->active) { // Jika curr tidak dihapus (collected atau despawned)
            prev = curr;
        }
        curr = nextNode;
    }
}

void DrawPowerUp(PowerUpList *list) {
    if (!list) return;
    PowerUpNode *curr = list->head;
    while (curr != NULL) {
        if (curr->active) {
            Color color;
            const char *symbol;
            switch (curr->type) {
                case POWERUP_TRIPLE_BALL:
                    color = RED;
                    symbol = "3X";
                    break;
                case POWERUP_LONG_PADDLE:
                    color = BLUE;
                    symbol = "LP";
                    break;
                default:
                    color = GRAY;
                    symbol = "?";
                    break;
            }
            DrawRectangleRec(curr->rect, color);
            int fontSize = (POWERUP_ITEM_HEIGHT < 25) ? 10 : 18;
            int textWidth = MeasureText(symbol, fontSize);
            DrawText(symbol, (int)(curr->rect.x + (curr->rect.width - textWidth) / 2.0f), (int)(curr->rect.y + (curr->rect.height - fontSize) / 2.0f), fontSize, WHITE);
        }
        curr = curr->next;
    }
}

void FreePowerUp(PowerUpList *list) { // Membersihkan list power-up yang jatuh
    if (!list) return;
    PowerUpNode *curr = list->head;
    while (curr != NULL) {
        PowerUpNode *next = curr->next;
        free(curr);
        curr = next;
    }
    list->head = NULL;
}
