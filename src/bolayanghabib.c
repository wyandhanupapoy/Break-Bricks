#include "BOLA.h"
#include "block.h"
#include "stopwatch.h"
#include "game_state.h"
#include "sound.h"
#include <math.h>
#include <float.h>
#include <stddef.h>
#include <stdlib.h>

#define SCREEN_W 830
#define SCREEN_H 600

#define MIN_BALL_SPEED 6.0f
#define MAX_BALL_SPEED 9.0f

void InitBola(BolaNode** head)
{
    *head = (BolaNode*)malloc(sizeof(BolaNode)); // Alokasikan memori untuk bola pertama
    BolaNode* bola = *head;
    bola->position = (Vector2){SCREEN_W / 2, SCREEN_H / 2};
    bola->speed = (Vector2){6, -6}; // Speed awal
    bola->radius = 10;
    bola->color = RED;
    bola->active = true;
    bola->next = NULL; // Tidak ada bola berikutnya
}

void UpdateBola(BolaNode* head, Paddle paddles[PADDLE_ROWS][PADDLE_COLS], Block blocks[BLOCK_ROWS][BLOCK_COLS], GameState *state, Skor *skor, Stopwatch sw[STOPWATCH_ROWS][STOPWATCH_COLS])
{
    BolaNode* bola = head;
    while (bola != NULL) // Loop melalui semua bola
    {
        if (!bola->active)
        {
            bola = bola->next;
            continue;
        }

        if (*state == GAME_PLAY || *state == GAME_START)
        {
            // 🔹 Pergerakan bola
            bola->position.x += bola->speed.x;
            bola->position.y += bola->speed.y;

            // 🔹 Batasi kecepatan bola
            float speedMagnitude = sqrtf(bola->speed.x * bola->speed.x + bola->speed.y * bola->speed.y);
            if (speedMagnitude < MIN_BALL_SPEED)
            {
                bola->speed.x *= (MIN_BALL_SPEED / speedMagnitude);
                bola->speed.y *= (MIN_BALL_SPEED / speedMagnitude);
            }
            if (speedMagnitude > MAX_BALL_SPEED)
            {
                bola->speed.x *= (MAX_BALL_SPEED / speedMagnitude);
                bola->speed.y *= (MAX_BALL_SPEED / speedMagnitude);
            }

            // 🔹 Pantulan dinding
            if (bola->position.x < bola->radius)
            {
                bola->speed.x *= -1;
                bola->position.x = bola->radius;
            }
            if (bola->position.x > SCREEN_W - bola->radius)
            {
                bola->speed.x *= -1;
                bola->position.x = SCREEN_W - bola->radius;
            }
            if (bola->position.y < bola->radius)
            {
                bola->speed.y *= -1;
                bola->position.y = bola->radius;
            }

            // 🔹 Pantulan dengan paddle
            for (int j = 0; j < PADDLE_ROWS; j++)
            {
                for (int k = 0; k < PADDLE_COLS; k++)
                {
                    if (CheckCollisionCircleRec(bola->position, bola->radius, paddles[j][k].rect))
                    {
                        float paddleCenter = paddles[j][k].rect.x + PADDLE_WIDTH / 2;
                        float hitPos = bola->position.x - paddleCenter;
                        float normalizedHit = hitPos / (PADDLE_WIDTH / 2);

                        bola->speed.x = normalizedHit * 7.0f; // Pantulan ke kiri-kanan
                        bola->speed.y *= -1;                  // Pantulan vertikal
                        PlayPaddleHit();

                        // Boost sedikit setelah kena paddle
                        bola->speed.x *= 1.05f;
                        bola->speed.y *= 1.05f;

                        // Reset posisi supaya nggak stuck
                        bola->position.y = paddles[j][k].rect.y - bola->radius - 1;
                    }
                }
            }

            // 🔹 Cek tabrakan dengan blok (hanya satu blok terdekat)
            Block *closestBlock = NULL;
            float closestDistance = FLT_MAX;
            for (int blockRow = 0; blockRow < BLOCK_ROWS; blockRow++)
            {
                for (int blockCol = 0; blockCol < BLOCK_COLS; blockCol++)
                {
                    Block *block = &blocks[blockRow][blockCol];

                    if (block->active && CheckCollisionCircleRec(bola->position, bola->radius, block->rect))
                    {
                        // 🔹 Hitung jarak bola ke pusat blok
                        float distance = sqrtf(pow(bola->position.x - (block->rect.x + block->rect.width / 2), 2) +
                                               pow(bola->position.y - (block->rect.y + block->rect.height / 2), 2));

                        // 🔹 Simpan blok yang paling dekat
                        if (distance < closestDistance)
                        {
                            closestDistance = distance;
                            closestBlock = block;
                        }
                    }
                }
            }

            // 🔹 Jika ada blok yang kena, proses tabrakan
            if (closestBlock != NULL)
            {
                closestBlock->hitPoints--;
                float elapsedTime = sw[0][0].time;

                // 🔹 Jika block hancur
                if (closestBlock->hitPoints <= 0)
                {
                    PlayBlockHit();
                    closestBlock->active = false;
                    TambahSkorDenganWaktu(skor, elapsedTime); // ✅ Skor hanya ditambah jika block benar-benar hancur
                }
                else
                {
                    // Update warna sesuai hitPoints sisa
                    if (closestBlock->hitPoints == 2)
                        closestBlock->color = (Color){255, 140, 26, 255}; // Orange
                    if (closestBlock->hitPoints == 1)
                        closestBlock->color = (Color){255, 204, 77, 255}; // Kuning
                }

                // 🔹 Tentukan sisi tabrakan
                float overlapLeft = fabs((bola->position.x + bola->radius) - closestBlock->rect.x);
                float overlapRight = fabs((closestBlock->rect.x + closestBlock->rect.width) - (bola->position.x - bola->radius));
                float overlapTop = fabs((bola->position.y + bola->radius) - closestBlock->rect.y);
                float overlapBottom = fabs((closestBlock->rect.y + closestBlock->rect.height) - (bola->position.y - bola->radius));

                if (overlapLeft < overlapRight && overlapLeft < overlapTop && overlapLeft < overlapBottom)
                {
                    bola->speed.x *= -1;
                    bola->position.x = closestBlock->rect.x - bola->radius;
                }
                else if (overlapRight < overlapLeft && overlapRight < overlapTop && overlapRight < overlapBottom)
                {
                    bola->speed.x *= -1;
                    bola->position.x = closestBlock->rect.x + closestBlock->rect.width + bola->radius;
                }
                else if (overlapTop < overlapBottom)
                {
                    bola->speed.y *= -1;
                    bola->position.y = closestBlock->rect.y - bola->radius;
                }
                else
                {
                    bola->speed.y *= -1;
                    bola->position.y = closestBlock->rect.y + closestBlock->rect.height + bola->radius;
                }
            }

            // 🔹 Jika semua blok hancur
            if (AllBlocksDestroyed(blocks))
            {
                *state = GAME_WIN;
            }

            // 🔹 Cek jika bola jatuh ke bawah
            if (bola->position.y > SCREEN_H)
            {
                bola->active = false;
            }
        }

        bola = bola->next;
    }
}

void DrawBola(BolaNode* head)
{
    BolaNode* bola = head;
    while (bola != NULL)
    {
        if (bola->active)
        {
            DrawCircleV(bola->position, bola->radius, bola->color);
        }
        bola = bola->next;
    }
}

void ResetBola(BolaNode** head)
{
    BolaNode* bola = *head;
    while (bola != NULL)
    {
        bola->position = (Vector2){SCREEN_W / 2, SCREEN_H / 2};
        bola->speed = (Vector2){6, -6};
        bola->active = true;
        bola = bola->next;
    }
}
