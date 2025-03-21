#include "BOLA.h"
#include "block.h"
#include "stopwatch.h"
#include "game_state.h"
#include "sound.h"
#include <math.h>

#define SCREEN_WIDTH 830
#define SCREEN_HEIGHT 600

#define MIN_BALL_SPEED 6.0f
#define MAX_BALL_SPEED 9.0f

void InitBola(Bola bola[BOLA_ROWS][BOLA_COLS])
{
    for (int i = 0; i < BOLA_ROWS; i++)
    {
        bola[i][0].position = (Vector2){SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2};
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
            // Gerakkan bola
            bola[i][0].position.x += bola[i][0].speed.x;
            bola[i][0].position.y += bola[i][0].speed.y;

            // Batas kecepatan bola
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

            // Pantulan dengan paddle
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

            // Pantulan dinding
            if (bola[i][0].position.x < bola[i][0].radius)
            {
                bola[i][0].speed.x *= -1;
                bola[i][0].position.x = bola[i][0].radius;
            }
            if (bola[i][0].position.x > SCREEN_WIDTH - bola[i][0].radius)
            {
                bola[i][0].speed.x *= -1;
                bola[i][0].position.x = SCREEN_WIDTH - bola[i][0].radius;
            }
            if (bola[i][0].position.y < bola[i][0].radius)
            {
                bola[i][0].speed.y *= -1;
                bola[i][0].position.y = bola[i][0].radius;
            }

            // Cek blok
            bool hasHitBlock = false;
            for (int blockRow = 0; blockRow < BLOCK_ROWS && !hasHitBlock; blockRow++)
            {
                for (int blockCol = 0; blockCol < BLOCK_COLS; blockCol++)
                {
                    Block *block = &blocks[blockRow][blockCol];

                    if (block->active && CheckCollisionCircleRec(bola[i][0].position, bola[i][0].radius, block->rect))
                    {
                        block->hitPoints--;

                        if (block->hitPoints <= 0)
                        {
                            PlayBlockHit();
                            block->active = false;
                        }
                        else
                        {
                            if (block->hitPoints == 2)
                            {
                                PlayBlockHit();
                                block->color = BROWN;
                            }
                            else if (block->hitPoints == 1)
                            {
                                PlayBlockHit();
                                block->color = BEIGE;
                            }
                        }

                        // Tambah skor
                        TambahSkor(skor, 50);

                        // Pantulan setelah kena blok
                        bola[i][0].speed.y *= -1;
                        hasHitBlock = true;

                        break;
                    }
                }
            }

            // Jika semua blok hancur
            if (AllBlocksDestroyed(blocks))
            {
                *state = GAME_WIN;
            }

            // Cek jatuh ke bawah
            if (bola[i][0].position.y > SCREEN_HEIGHT)
            {
                bola[i][0].active = false; // Matikan bola, tunggu reset di luar fungsi
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
        bola[i][0].position = (Vector2){SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2};

        // Diam dulu, nanti diatur lagi saat mulai game
        bola[i][0].speed = (Vector2){6, -6};
        bola[i][0].active = true;
    }
}
