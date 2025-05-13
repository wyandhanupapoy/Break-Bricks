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
        for (int j = 0; j < BOLA_COLS; j++) {
            bola[i][j].position = (Vector2){SCREEN_W / 2, SCREEN_H / 2};
            bola[i][j].speed = (Vector2){6, -6};
            bola[i][j].radius = 10;
            bola[i][j].color = (j == 0) ? RED : PURPLE;  // Bola pertama merah, sisanya ungu
            bola[i][j].active = (j == 0);  // Hanya bola pertama yang aktif di awal
        }
    }
}

// 🔹 Memperbarui posisi, tabrakan, dan status bola
void UpdateBola(Bola bola[BOLA_ROWS][BOLA_COLS], Paddle paddles[PADDLE_ROWS][PADDLE_COLS], LinkedList *blocks, GameState *state, Skor *skor, Stopwatch* next) {
    bool anyActiveBolaLeft = false;
    
    for (int i = 0; i < BOLA_ROWS; i++) {
        for (int j = 0; j < BOLA_COLS; j++) {
            Bola *b = &bola[i][j];
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
                for (int p = 0; p < PADDLE_ROWS; p++) {
                    for (int k = 0; k < PADDLE_COLS; k++) {
                        Paddle *paddle = &paddles[p][k];
                        if (CheckCollisionCircleRec(b->position, b->radius, paddle->rect)) {
                            float paddleCenter = paddle->rect.x + PADDLE_WIDTH / 2;
                            float hitOffset = (b->position.x - paddleCenter) / (PADDLE_WIDTH / 2);
                            b->speed.x = hitOffset * 7.0f;
                            b->speed.y *= -1;
                            b->speed.x *= 1.05f;
                            b->speed.y *= 1.05f;
                            b->position.y = paddle->rect.y - b->radius - 1;
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
                    
                    if (block->active && CheckCollisionCircleRec(b->position, b->radius, block->rect)) {
                        // 🔹 Hitung jarak bola ke pusat blok
                        float distance = sqrtf(pow(b->position.x - (block->rect.x + block->rect.width / 2), 2) +
                                              pow(b->position.y - (block->rect.y + block->rect.height / 2), 2));

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
                } else {
                    // Jika bola masih aktif setelah semua pemrosesan
                    anyActiveBolaLeft = true;
                }
            }
        }
    }
    
    // Cek jika tidak ada bola aktif yang tersisa, dan update game state
    if (!anyActiveBolaLeft && (*state == GAME_PLAY || *state == GAME_START)) {
        // Semua bola hilang, perlu reset atau kurangi nyawa
        *state = GAME_OVER;
    }
}

void DrawBola(Bola bola[BOLA_ROWS][BOLA_COLS]) {
    for (int i = 0; i < BOLA_ROWS; i++) {
        for (int j = 0; j < BOLA_COLS; j++) {
            if (bola[i][j].active) {
                DrawCircleV(bola[i][j].position, bola[i][j].radius, bola[i][j].color);
            }
        }
    }
}

void AddNewBall(Bola bola[BOLA_ROWS][BOLA_COLS]) {
    for (int i = 0; i < BOLA_ROWS; i++) {
        for (int j = 1; j < BOLA_COLS; j++) {  // Mulai dari indeks 1 (bola kedua)
            if (!bola[i][j].active) {
                // Cari bola aktif untuk referensi posisi
                Bola *refBall = NULL;
                for (int k = 0; k < BOLA_COLS; k++) {
                    if (bola[i][k].active) {
                        refBall = &bola[i][k];
                        break;
                    }
                }
                
                // Hanya tambahkan bola baru jika ada bola aktif lain sebagai referensi
                if (refBall == NULL) return;
                
                // Aktifkan bola baru dengan posisi sama dengan bola referensi
                bola[i][j].position = refBall->position;
                
                // Berikan kecepatan sedikit berbeda dari bola referensi
                float angle = GetRandomValue(0, 360) * (PI / 180.0f);
                float speed = sqrtf(refBall->speed.x * refBall->speed.x + 
                                   refBall->speed.y * refBall->speed.y);
                
                bola[i][j].speed.x = cosf(angle) * speed;
                bola[i][j].speed.y = sinf(angle) * speed;
                
                // Pastikan bola bergerak ke arah yang masuk akal
                if (bola[i][j].speed.y > 0) bola[i][j].speed.y *= -1;
                
                bola[i][j].radius = refBall->radius;
                bola[i][j].color = PURPLE;  // Warna berbeda untuk membedakan
                bola[i][j].active = true;
                
                // Hanya aktifkan satu bola baru per pemanggilan
                return;
            }
        }
    }
}

// 🔹 Reset posisi bola ke tengah
void ResetBola(Bola bola[BOLA_ROWS][BOLA_COLS]) {
    for (int i = 0; i < BOLA_ROWS; i++) {
        bola[i][0].position = (Vector2){SCREEN_W / 2, SCREEN_H / 2};
        bola[i][0].speed = (Vector2){6, -6};
        bola[i][0].active = true;
        
        // Non-aktifkan bola tambahan saat reset
        for (int j = 1; j < BOLA_COLS; j++) {
            bola[i][j].active = false;
        }
    }
}

// 🔹 Function untuk menghitung jumlah bola aktif
int CountActiveBalls(Bola bola[BOLA_ROWS][BOLA_COLS]) {
    int count = 0;
    for (int i = 0; i < BOLA_ROWS; i++) {
        for (int j = 0; j < BOLA_COLS; j++) {
            if (bola[i][j].active) count++;
        }
    }
    return count;
}