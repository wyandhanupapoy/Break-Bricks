#include "BOLA.h"
#include "block.h"
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

void InitBola(Bola bola[BOLA_ROWS][BOLA_COLS])
{
    for (int i = 0; i < BOLA_ROWS; i++)
    {
        bola[i][0].position = (Vector2){SCREEN_W / 2, SCREEN_H / 2};
        bola[i][0].speed = (Vector2){6, -6}; // Speed awal
        bola[i][0].radius = 10;
        bola[i][0].color = RED;
        bola[i][0].active = true;
    }
}

void UpdateBola(Bola bola[BOLA_ROWS][BOLA_COLS], Paddle paddles[PADDLE_ROWS][PADDLE_COLS], Block blocks[BLOCK_ROWS][BLOCK_COLS], GameState *state, Skor *skor, Stopwatch sw[STOPWATCH_ROWS][STOPWATCH_COLS])
{
    for (int i = 0; i < BOLA_ROWS; i++)
    {
        if (!bola[i][0].active)
            continue;

        if (*state == GAME_PLAY || *state == GAME_START)
        {
            // 🔹 Pergerakan bola
            bola[i][0].position.x += bola[i][0].speed.x;
            bola[i][0].position.y += bola[i][0].speed.y;

            // 🔹 Batasi kecepatan bola
            float speedMagnitude = sqrtf(bola[i][0].speed.x * bola[i][0].speed.x + bola[i][0].speed.y * bola[i][0].speed.y);
            if (speedMagnitude < MIN_BALL_SPEED)
            {
                bola[i][0].speed.x *= (MIN_BALL_SPEED / speedMagnitude);
                bola[i][0].speed.y *= (MIN_BALL_SPEED / speedMagnitude);
            }
            if (speedMagnitude > MAX_BALL_SPEED)
            {
                bola[i][0].speed.x *= (MAX_BALL_SPEED / speedMagnitude);
                bola[i][0].speed.y *= (MAX_BALL_SPEED / speedMagnitude);
            }

            // 🔹 Pantulan dinding
            if (bola[i][0].position.x < bola[i][0].radius)
            {
                bola[i][0].speed.x *= -1;
                bola[i][0].position.x = bola[i][0].radius;
            }
            if (bola[i][0].position.x > SCREEN_W - bola[i][0].radius)
            {
                bola[i][0].speed.x *= -1;
                bola[i][0].position.x = SCREEN_W - bola[i][0].radius;
            }
            if (bola[i][0].position.y < bola[i][0].radius)
            {
                bola[i][0].speed.y *= -1;
                bola[i][0].position.y = bola[i][0].radius;
            }

            // 🔹 Pantulan dengan paddle
            for (int j = 0; j < PADDLE_ROWS; j++)
            {
                for (int k = 0; k < PADDLE_COLS; k++)
                {
                    if (CheckCollisionCircleRec(bola[i][0].position, bola[i][0].radius, paddles[j][k].rect))
                    {
                        float paddleCenter = paddles[j][k].rect.x + PADDLE_WIDTH / 2;
                        float hitPos = bola[i][0].position.x - paddleCenter;
                        float normalizedHit = hitPos / (PADDLE_WIDTH / 2);

                        bola[i][0].speed.x = normalizedHit * 7.0f; // Pantulan ke kiri-kanan
                        bola[i][0].speed.y *= -1;                  // Pantulan vertikal
                        PlayPaddleHit();

                        // Boost sedikit setelah kena paddle
                        bola[i][0].speed.x *= 1.05f;
                        bola[i][0].speed.y *= 1.05f;

                        // Reset posisi supaya nggak stuck
                        bola[i][0].position.y = paddles[j][k].rect.y - bola[i][0].radius - 1;
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

                    if (block->active && CheckCollisionCircleRec(bola[i][0].position, bola[i][0].radius, block->rect))
                    {
                        // 🔹 Hitung jarak bola ke pusat blok
                        float distance = sqrtf(pow(bola[i][0].position.x - (block->rect.x + block->rect.width / 2), 2) +
                                               pow(bola[i][0].position.y - (block->rect.y + block->rect.height / 2), 2));

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

                if (closestBlock->hitPoints <= 0)
                {
                    PlayBlockHit();
                    closestBlock->active = false;
                }
                else
                {
                    if (closestBlock->hitPoints == 2) closestBlock->color = BROWN;
                    if (closestBlock->hitPoints == 1) closestBlock->color = BEIGE;
                }

                // 🔹 Tentukan sisi tabrakan
                float overlapLeft = fabs((bola[i][0].position.x + bola[i][0].radius) - closestBlock->rect.x);
                float overlapRight = fabs((closestBlock->rect.x + closestBlock->rect.width) - (bola[i][0].position.x - bola[i][0].radius));
                float overlapTop = fabs((bola[i][0].position.y + bola[i][0].radius) - closestBlock->rect.y);
                float overlapBottom = fabs((closestBlock->rect.y + closestBlock->rect.height) - (bola[i][0].position.y - bola[i][0].radius));

                if (overlapLeft < overlapRight && overlapLeft < overlapTop && overlapLeft < overlapBottom)
                {
                    bola[i][0].speed.x *= -1; // Tabrak sisi kiri blok
                    bola[i][0].position.x = closestBlock->rect.x - bola[i][0].radius; 
                }
                else if (overlapRight < overlapLeft && overlapRight < overlapTop && overlapRight < overlapBottom)
                {
                    bola[i][0].speed.x *= -1; // Tabrak sisi kanan blok
                    bola[i][0].position.x = closestBlock->rect.x + closestBlock->rect.width + bola[i][0].radius;
                }
                else if (overlapTop < overlapBottom)
                {
                    bola[i][0].speed.y *= -1; // Tabrak sisi atas blok
                    bola[i][0].position.y = closestBlock->rect.y - bola[i][0].radius;
                }
                else
                {
                    bola[i][0].speed.y *= -1; // Tabrak sisi bawah blok
                    bola[i][0].position.y = closestBlock->rect.y + closestBlock->rect.height + bola[i][0].radius;
                }

                // 🔹 Tambah skor
                TambahSkor(skor, 50);
            }

            // 🔹 Jika semua blok hancur
            if (AllBlocksDestroyed(blocks))
            {
                *state = GAME_WIN;
            }

            // 🔹 Cek jika bola jatuh ke bawah
            if (bola[i][0].position.y > SCREEN_H)
            {
                bola[i][0].active = false;
            }
        }
    }
}


void DrawBola(Bola bola[BOLA_ROWS][BOLA_COLS])
{
    for (int i = 0; i < BOLA_ROWS; i++)
    {
        if (bola[i][0].active)
        {
            DrawCircleV(bola[i][0].position, bola[i][0].radius, bola[i][0].color);
        }
    }
}

void ResetBola(Bola bola[BOLA_ROWS][BOLA_COLS])
{
    for (int i = 0; i < BOLA_ROWS; i++)
    {
        bola[i][0].position = (Vector2){SCREEN_W / 2, SCREEN_H / 2};

        // Diam dulu, nanti diatur lagi saat mulai game
        bola[i][0].speed = (Vector2){6, -6};
        bola[i][0].active = true;
    }
}
