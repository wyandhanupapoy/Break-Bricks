#include "powerup.h"
#include "paddle.h"  // Untuk PaddleNode, ActivePowerUp, PADDLE_WIDTH_DEFAULT, dll.
#include "BOLA.h"    // Untuk BolaList dan AddBola
#include "sound.h"   // Untuk PlaySfx
#include <stdlib.h>  // Untuk malloc, free
#include <raymath.h> // Untuk fminf, fmaxf

#define POWERUP_FALL_SPEED 2.0f // Kecepatan jatuh power-up (unit per detik jika dikali deltaTime)
#define POWERUP_ITEM_WIDTH 30
#define POWERUP_ITEM_HEIGHT 30

#define LONG_PADDLE_INCREMENT_VALUE 40.0f


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

    newNode->rect = (Rectangle){position.x - POWERUP_ITEM_WIDTH/2, position.y, POWERUP_ITEM_WIDTH, POWERUP_ITEM_HEIGHT};
    newNode->type = type;
    newNode->active = true;
    // newNode->duration tidak ada lagi di PowerUpNode, durasi dikelola oleh ActivePowerUp
    newNode->next = list->head;
    list->head = newNode;
    TraceLog(LOG_INFO, "POWERUP: Added new falling item type %d", type);
}

// Fungsi untuk mengaktifkan efek power-up pada paddle
void ActivatePowerUp(PowerUpType type, struct PaddleNode *paddle_node, struct BolaList *bolaList) {
    if (!paddle_node) return;

    PlaySfx("power_up"); // Mainkan suara sekali saat power-up diambil

    // Cek apakah efek dengan tipe ini sudah ada di paddle
    ActivePowerUp* existingEffect = paddle_node->activePowerUps;
    bool foundInList = false;
    while(existingEffect != NULL) {
        if (existingEffect->type == type) {
            existingEffect->remainingTime = POWERUP_DEFAULT_DURATION; // Perbarui/reset durasi jika sudah ada
            foundInList = true;
            // Untuk Long Paddle, kita tetap ingin efek penambahan panjangnya terjadi
            // jadi jangan langsung return di sini jika hanya me-refresh timer.
            break; 
        }
        existingEffect = existingEffect->next;
    }

    // Terapkan efek langsung dari power-up
    if (type == POWERUP_TRIPLE_BALL && bolaList) {
        Vector2 spawnPos = {paddle_node->rect.x + paddle_node->rect.width / 2, paddle_node->rect.y - 15};
        // Sekarang MIN_BALL_SPEED seharusnya terdefinisi
        AddBola(bolaList, spawnPos, (Vector2){GetRandomValue(-5, -3), -MIN_BALL_SPEED});
        AddBola(bolaList, spawnPos, (Vector2){GetRandomValue(3, 5), -MIN_BALL_SPEED});
    }
    if (type == POWERUP_LONG_PADDLE) {
        paddle_node->rect.width += LONG_PADDLE_INCREMENT_VALUE; // Tambah panjang paddle

        // Batasi lebar maksimum paddle
        if (paddle_node->rect.width > MAX_PADDLE_WIDTH) {
            paddle_node->rect.width = MAX_PADDLE_WIDTH;
        }

        // Setelah lebar diubah, pastikan paddle tidak keluar batas kiri atau kanan
        // dan tetap berada dalam area permainan paddle
        if (paddle_node->rect.x < 0) {
            paddle_node->rect.x = 0;
        }
        // Jika paddle keluar ke kanan setelah memanjang dari sisi kiri
        if (paddle_node->rect.x + paddle_node->rect.width > PADDLE_GAME_AREA_WIDTH) {
            paddle_node->rect.x = PADDLE_GAME_AREA_WIDTH - paddle_node->rect.width;
        }
    }

    // Jika belum ada dalam daftar efek aktif, tambahkan sebagai node baru
    if (!foundInList) {
        ActivePowerUp *newEffect = (ActivePowerUp*)malloc(sizeof(ActivePowerUp));
        if (!newEffect) {
            TraceLog(LOG_WARNING, "POWERUP: Failed to allocate memory for new active effect.");
            return;
        }
        newEffect->type = type;
        newEffect->remainingTime = POWERUP_DEFAULT_DURATION;
        newEffect->next = paddle_node->activePowerUps; // Tambahkan ke depan list
        paddle_node->activePowerUps = newEffect;
        TraceLog(LOG_INFO, "POWERUP: Activated new effect type %d on paddle.", type);
    } else {
        // Jika sudah ada di list (foundInList == true), timer-nya sudah di-refresh di loop atas.
        TraceLog(LOG_INFO, "POWERUP: Refreshed duration for active effect type %d on paddle.", type);
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
            TraceLog(LOG_INFO, "POWERUP: Effect type %d expired.", curr->type);
            if (curr->type == POWERUP_LONG_PADDLE) {
                // Saat Long Paddle berakhir, reset ke lebar default.
                // Jika ada beberapa "stack" Long Paddle, ini akan langsung reset.
                // Jika ingin pengurangan bertahap, logikanya akan lebih kompleks.
                // Untuk sekarang, kita reset ke default saat timer habis.
                paddle_node->rect.width = PADDLE_WIDTH_DEFAULT;

                // Pastikan paddle tetap dalam batas setelah reset lebar
                if (paddle_node->rect.x + paddle_node->rect.width > PADDLE_GAME_AREA_WIDTH) {
                    paddle_node->rect.x = PADDLE_GAME_AREA_WIDTH - paddle_node->rect.width;
                }
                if (paddle_node->rect.x < 0) { // Seharusnya tidak terjadi jika width default > 0
                    paddle_node->rect.x = 0;
                }
            }
            // Untuk POWERUP_TRIPLE_BALL, efeknya instan, tidak ada yang perlu dikembalikan saat timer habis.
            // Timer hanya menandakan "efek ini pernah aktif".

            // Hapus efek dari daftar
            if (prev == NULL) {
                paddle_node->activePowerUps = nextEffect;
            } else {
                prev->next = nextEffect;
            }
            free(curr);
            curr = nextEffect; 
        } else {
            prev = curr;
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

        curr->rect.y += POWERUP_FALL_SPEED * deltaTime * 60.0f; // Kecepatan konsisten (asumsi 60FPS basis jika speed kecil)
                                                              // Atau jika POWERUP_FALL_SPEED per detik: curr->rect.y += POWERUP_FALL_SPEED * deltaTime;

        bool collected = false;
        if (paddleList && paddleList->head) { // Cek paddleList->head untuk validitas
            // Untuk game single player, kita hanya cek paddle pertama
            PaddleNode *playerPaddle = paddleList->head;
            if (CheckCollisionRecs(curr->rect, playerPaddle->rect)) {
                ActivatePowerUp(curr->type, playerPaddle, bolaList); // Durasi diambil dari konstanta
                curr->active = false; // Tandai untuk dihapus dari list item jatuh
                collected = true;
                // Tidak perlu break karena hanya ada satu paddle yang dicek
            }
        }

        if (curr->rect.y > GetScreenHeight() + curr->rect.height) { // Tambahkan height agar benar-benar hilang
            curr->active = false; 
        }

        if (!collected && curr->active) { 
            prev = curr;
        }
        curr = nextNode;
    }
}


void DrawPowerUp(PowerUpList *list) {
    if (!list) return;
    PowerUpNode *curr = list->head;
    while (curr != NULL) {
        if (curr->active) { // Hanya gambar item power-up yang masih jatuh
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
            int fontSize = (POWERUP_ITEM_HEIGHT < 25) ? 10 : 18; // Ukuran font disesuaikan
            int textWidth = MeasureText(symbol, fontSize);
            DrawText(symbol, curr->rect.x + (curr->rect.width - textWidth) / 2, curr->rect.y + (curr->rect.height - fontSize) / 2, fontSize, WHITE);
        }
        curr = curr->next;
    }
}

void FreePowerUp(PowerUpList *list) {
    if (!list) return;
    PowerUpNode *curr = list->head;
    while (curr != NULL) {
        PowerUpNode *next = curr->next;
        free(curr);
        curr = next;
    }
    list->head = NULL;
}