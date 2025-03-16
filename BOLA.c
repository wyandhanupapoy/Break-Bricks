#include "BOLA.h"
#include "block.h"
#include "stopwatch.h"

#define SCREEN_WIDTH 830
#define SCREEN_HEIGHT 600

void InitBola(Bola bola[BOLA_ROWS][BOLA_COLS])
{
    for (int i = 0; i < BOLA_ROWS; i++)
    {
        bola[i][0].position = (Vector2){SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2};
        bola[i][0].speed = (Vector2){0, 0}; // Set kecepatan awal bola menjadi 0
        bola[i][0].radius = 10;
        bola[i][0].color = RED;
        bola[i][0].active = true;
    }
}

void UpdateBola(Bola bola[BOLA_ROWS][BOLA_COLS], Paddle paddles[PADDLE_ROWS][PADDLE_COLS], Block blocks[BLOCK_ROWS][BLOCK_COLS], GameState *state, Skor *skor, Stopwatch sw[STOPWATCH_ROWS][STOPWATCH_COLS]) {
    for (int i = 0; i < BOLA_ROWS; i++) {
        if (bola[i][0].active) {
            if (*state == GAME_PLAY) {
                bola[i][0].position.x += bola[i][0].speed.x;
                bola[i][0].position.y += bola[i][0].speed.y;

                bool hasHitBlock = false;

                // Cek tabrakan dengan paddle
                for (int j = 0; j < PADDLE_ROWS; j++) {
                    for (int k = 0; k < PADDLE_COLS; k++) {
                        if (CheckCollisionCircleRec(bola[i][0].position, bola[i][0].radius, paddles[j][k].rect)) {
                            // Hit pada paddle
                            float paddleCenter = paddles[j][k].rect.x + PADDLE_WIDTH / 2;
                            float hitPosition = bola[i][0].position.x - paddleCenter;
                            float normalizedHitPosition = hitPosition / (PADDLE_WIDTH / 2);

                            bola[i][0].speed.x = normalizedHitPosition * 5;
                            bola[i][0].speed.y *= -1;

                            bola[i][0].position.y = paddles[j][k].rect.y - bola[i][0].radius;
                        }
                    }
                }

                // Cek tabrakan dengan dinding
                if (bola[i][0].position.x < bola[i][0].radius) {
                    bola[i][0].speed.x *= -1;
                    bola[i][0].position.x = bola[i][0].radius;
                }
                if (bola[i][0].position.x > SCREEN_WIDTH - bola[i][0].radius) {
                    bola[i][0].speed.x *= -1;
                    bola[i][0].position.x = SCREEN_WIDTH - bola[i][0].radius;
                }
                if (bola[i][0].position.y < bola[i][0].radius) {
                    bola[i][0].speed.y *= -1;
                    bola[i][0].position.y = bola[i][0].radius;
                }

                // Cek tabrakan dengan blok
                for (int blockRow = 0; blockRow < BLOCK_ROWS; blockRow++) {
                    for (int blockCol = 0; blockCol < BLOCK_COLS; blockCol++) {
                        if (blocks[blockRow][blockCol].active &&
                            CheckBallBlockCollision(bola[i][0].position, bola[i][0].radius, blocks[blockRow][blockCol].rect) && !hasHitBlock) {
                            blocks[blockRow][blockCol].active = false;
                            hasHitBlock = true;

                            // Tambah skor
                            int timeElapsed = (int)sw[0][0].time; // Use the passed stopwatch
                            int scoreToAdd = 50 - timeElapsed;           
                            if (scoreToAdd < 5) scoreToAdd = 5;          
                            if (scoreToAdd > 50) scoreToAdd = 50;        
                            TambahSkor(skor, scoreToAdd);                 

                            bola[i][0].speed.y *= -1;
                            break; // Keluar dari loop setelah memecahkan satu blok
                        }
                    }
                    if (hasHitBlock) break; // Keluar dari loop jika sudah memecahkan satu blok
                }

                // Cek apakah semua blok telah dihancurkan
                if (AllBlocksDestroyed(blocks)) {
                    *state = GAME_WIN; // Ubah status permainan menjadi menang
                }
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
        bola[i][0].speed = (Vector2){5, -5}; // Set kecepatan awal bola saat reset
        bola[i][0].active = true;
    }
}