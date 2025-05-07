#include "BOLA.h"
#include "LinkedList-Block.h"
#include "stopwatch.h"
#include "game_state.h"
#include "sound.h"
#include <math.h>
#include <float.h>
#include <stddef.h>

#define SCREEN_W 830
#define SCREEN_H 600

#define MIN_BALL_SPEED 6.0f
#define MAX_BALL_SPEED 9.0f

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
void UpdateBola(Bola bola[BOLA_ROWS][BOLA_COLS], Paddle paddles[PADDLE_ROWS][PADDLE_COLS], 
                LinkedList *blocks, GameState *state, Skor *skor, 
                Stopwatch sw[STOPWATCH_ROWS][STOPWATCH_COLS]) {

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

            // 🔹 Tabrakan dengan blok
            Block *closest = NULL;
            float closestDist = FLT_MAX;

            NodeBlock *current = blocks->head;  // Mengakses linked list blocks
            while (current != NULL) {
                Block *blk = &current->data;
                if (!blk->active) {
                    current = current->next;
                    continue;
                }

                if (CheckCollisionCircleRec(b->position, b->radius, blk->rect)) {
                    float dx = b->position.x - (blk->rect.x + blk->rect.width / 2);
                    float dy = b->position.y - (blk->rect.y + blk->rect.height / 2);
                    float dist = sqrtf(dx * dx + dy * dy);

                    if (dist < closestDist) {
                        closestDist = dist;
                        closest = blk;
                    }
                }

                current = current->next;
            }

            if (closest) {
                closest->hitPoints--;
                if (closest->hitPoints <= 0) {
                    closest->active = false;
                    PlayBlockHit();
                    TambahSkorDenganWaktu(skor, sw[0][0].time);
                } else {
                    switch (closest->hitPoints) {
                        case 2:
                            closest->color = (Color){255, 140, 26, 255}; break;
                        case 1:
                            closest->color = (Color){255, 204, 77, 255}; break;
                    }
                }

                // 🔹 Deteksi sisi tabrakan
                float left = fabs((b->position.x + b->radius) - closest->rect.x);
                float right = fabs((closest->rect.x + closest->rect.width) - (b->position.x - b->radius));
                float top = fabs((b->position.y + b->radius) - closest->rect.y);
                float bottom = fabs((closest->rect.y + closest->rect.height) - (b->position.y - b->radius));

                if (left < right && left < top && left < bottom) {
                    b->speed.x *= -1;
                    b->position.x = closest->rect.x - b->radius;
                } else if (right < left && right < top && right < bottom) {
                    b->speed.x *= -1;
                    b->position.x = closest->rect.x + closest->rect.width + b->radius;
                } else if (top < bottom) {
                    b->speed.y *= -1;
                    b->position.y = closest->rect.y - b->radius;
                } else {
                    b->speed.y *= -1;
                    b->position.y = closest->rect.y + closest->rect.height + b->radius;
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
