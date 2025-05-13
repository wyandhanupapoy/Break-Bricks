#include "BOLA.h"
#include "LinkedList-Block.h"
#include "stopwatch.h"
#include "game_state.h"
#include "sound.h"
#include "powerup.h"
#include <math.h>
#include <float.h>
#include <stddef.h>

#define SCREEN_W 830
#define SCREEN_H 600

#define MIN_BALL_SPEED 3.0f
#define MAX_BALL_SPEED 4.0f

extern bool IsBallStrong(void);

// 🔹 Inisialisasi bola di tengah layar
void InitBola(Bola bola[BOLA_ROWS][BOLA_COLS]) {
    for (int i = 0; i < BOLA_ROWS; i++) {
        bola[i][0].position = (Vector2){SCREEN_W / 2, SCREEN_H / 2};
        bola[i][0].speed = (Vector2){6, -6};
        bola[i][0].radius = 10;
        bola[i][0].color = RED;
        bola[i][0].active = true;
    }
}

// 🔹 Memperbarui posisi, tabrakan, dan status bola
void UpdateBola(Bola bola[BOLA_ROWS][BOLA_COLS], Paddle paddles[PADDLE_ROWS][PADDLE_COLS], LinkedList *blocks, GameState *state, Skor *skor, Stopwatch* next) {

    for (int i = 0; i < BOLA_ROWS; i++) {
        Bola *b = &bola[i][0];
        if (!b->active) continue;

        if (*state == GAME_PLAY || *state == GAME_START) {
            // 🔹 Pergerakan
            b->position.x += b->speed.x;
            b->position.y += b->speed.y;

            // 🔹 Batasi kecepatan
            float speedMag = sqrtf(b->speed.x * b->speed.x + b->speed.y * b->speed.y);
            if (speedMag < MIN_BALL_SPEED || speedMag > MAX_BALL_SPEED) {
                float clamped = fminf(fmaxf(speedMag, MIN_BALL_SPEED), MAX_BALL_SPEED);
                b->speed.x *= (clamped / speedMag);
                b->speed.y *= (clamped / speedMag);
            }

            // 🔹 Pantulan dinding
            if (b->position.x < b->radius) {
                b->speed.x *= -1;
                b->position.x = b->radius;
            }
            if (b->position.x > SCREEN_W - b->radius) {
                b->speed.x *= -1;
                b->position.x = SCREEN_W - b->radius;
            }
            if (b->position.y < b->radius) {
                b->speed.y *= -1;
                b->position.y = b->radius;
            }

            // 🔹 Pantulan paddle
            for (int j = 0; j < PADDLE_ROWS; j++) {
                for (int k = 0; k < PADDLE_COLS; k++) {
                    Paddle *p = &paddles[j][k];
                    if (CheckCollisionCircleRec(b->position, b->radius, p->rect)) {
                        float paddleCenter = p->rect.x + PADDLE_WIDTH / 2;
                        float hitOffset = (b->position.x - paddleCenter) / (PADDLE_WIDTH / 2);
                        b->speed.x = hitOffset * 7.0f;
                        b->speed.y *= -1;
                        b->speed.x *= 1.05f;
                        b->speed.y *= 1.05f;
                        b->position.y = p->rect.y - b->radius - 1;
                        PlayPaddleHit();
                    }
                }
            }

            // 🔹 Cek tabrakan dengan blok (hanya satu blok terdekat)
            Block *closestBlock = NULL;
            float closestDistance = FLT_MAX;
            
            // Iterasi melalui linked list blok
            NodeBlock *current = blocks->head;
            while (current != NULL) {
                Block *block = &current->data;
                
                if (block->active && CheckCollisionCircleRec(bola[i][0].position, bola[i][0].radius, block->rect)) {
                    // 🔹 Hitung jarak bola ke pusat blok
                    float distance = sqrtf(pow(bola[i][0].position.x - (block->rect.x + block->rect.width / 2), 2) +
                                          pow(bola[i][0].position.y - (block->rect.y + block->rect.height / 2), 2));

                    // 🔹 Simpan blok yang paling dekat
                    if (distance < closestDistance) {
                        closestDistance = distance;
                        closestBlock = block;
                    }
                }
                current = current->next;
            }

            // 🔹 Jika ada blok yang kena, proses tabrakan
            if (closestBlock != NULL) {
                closestBlock->hitPoints--; // Kurangi hit points blok
                Stopwatch* swList = next; // Assign the passed stopwatch pointer to swList
                float elapsedTime = swList->time; // Ambil waktu dari stopwatch yang sudah diupdate

                // 🔹 Jika block hancur
                if (closestBlock->hitPoints <= 0) {
                    closestBlock->active = false; // Set block menjadi tidak aktif
                    PlayBlockHit();
                    TambahSkorDenganWaktu(skor, elapsedTime);

                     SpawnPowerUp(closestBlock->rect.x + closestBlock->rect.width/2, 
                closestBlock->rect.y + closestBlock->rect.height/2);
                } else {
                    switch (closestBlock->hitPoints) {
                        case 2:
                            closestBlock->color = (Color){255, 140, 26, 255}; break;
                        case 1:
                            closestBlock->color = (Color){255, 204, 77, 255}; break;
                    }
                }

                // 🔹 Deteksi sisi tabrakan
                float left = fabs((b->position.x + b->radius) - closestBlock->rect.x);
                float right = fabs((closestBlock->rect.x + closestBlock->rect.width) - (b->position.x - b->radius));
                float top = fabs((b->position.y + b->radius) - closestBlock->rect.y);
                float bottom = fabs((closestBlock->rect.y + closestBlock->rect.height) - (b->position.y - b->radius));

                if (left < right && left < top && left < bottom) {
                    b->speed.x *= -1;
                    b->position.x = closestBlock->rect.x - b->radius;
                } else if (right < left && right < top && right < bottom) {
                    b->speed.x *= -1;
                    b->position.x = closestBlock->rect.x + closestBlock->rect.width + b->radius;
                } else if (top < bottom) {
                    b->speed.y *= -1;
                    b->position.y = closestBlock->rect.y - b->radius;
                } else {
                    b->speed.y *= -1;
                    b->position.y = closestBlock->rect.y + closestBlock->rect.height + b->radius;
                }
            }

            // 🔹 Menang jika semua blok hancur
            if (AllBlocksDestroyed(blocks)) {
                *state = GAME_WIN;
            }

            // 🔹 Bola jatuh ke bawah
            if (b->position.y > SCREEN_H) {
                b->active = false;
            }
        }
    }
}

// 🔹 Menggambar bola ke layar
void DrawBola(Bola bola[BOLA_ROWS][BOLA_COLS]) {
    for (int i = 0; i < BOLA_ROWS; i++) {
        if (bola[i][0].active) {
            DrawCircleV(bola[i][0].position, bola[i][0].radius, bola[i][0].color);
        }
    }
}

// 🔹 Reset posisi bola ke tengah
void ResetBola(Bola bola[BOLA_ROWS][BOLA_COLS]) {
    for (int i = 0; i < BOLA_ROWS; i++) {
        bola[i][0].position = (Vector2){SCREEN_W / 2, SCREEN_H / 2};
        bola[i][0].speed = (Vector2){6, -6};
        bola[i][0].active = true;
    }
}