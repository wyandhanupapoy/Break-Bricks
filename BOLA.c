#include "BOLA.h"

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600

void InitBola(Bola bola[BOLA_ROWS][BOLA_COLS]) {
    for (int i = 0; i < BOLA_ROWS; i++) {
        bola[i][0].position = (Vector2){SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2};
        bola[i][0].speed = (Vector2){0, 0}; // Set kecepatan awal bola menjadi 0
        bola[i][0].radius = 10;
        bola[i][0].color = RED;
        bola[i][0].active = true;
    }
}

void UpdateBola(Bola bola[BOLA_ROWS][BOLA_COLS], Paddle paddles[PADDLE_ROWS][PADDLE_COLS], GameState *state) {
    for (int i = 0; i < BOLA_ROWS; i++) {
        if (bola[i][0].active) {
            // Update posisi bola hanya jika game dalam keadaan bermain
            if (*state == GAME_PLAY) {
                bola[i][0].position.x += bola[i][0].speed.x;
                bola[i][0].position.y += bola[i][0].speed.y;

                // Cek tabrakan dengan paddles
                for (int j = 0; j < PADDLE_ROWS; j++) {
                    for (int k = 0; k < PADDLE_COLS; k++) {
                        if (CheckCollisionCircleRec(bola[i][0].position, bola[i][0].radius, paddles[j][k].rect)) {
                            // Memindahkan bola sedikit ke atas dari paddle
                            bola[i][0].position.y = paddles[j][k].rect.y - bola[i][0].radius; // Atur posisi bola
                            bola[i][0].speed.y *= -1; // Bounce back
                        }
                    }
                }

                // Cek tabrakan dengan dinding
                if (bola[i][0].position.x < bola[i][0].radius || bola[i][0].position.x > SCREEN_WIDTH - bola[i][0].radius) {
                    bola[i][0].speed.x *= -1; // Bounce back dari dinding samping
                }
                if (bola[i][0].position.y < bola[i][0].radius) {
                    bola[i][0].speed.y *= -1; // Bounce back dari dinding atas
                }
            }
        }
    }
}

void DrawBola(Bola bola[BOLA_ROWS][BOLA_COLS]) {
    for (int i = 0; i < BOLA_ROWS; i++) {
        if (bola[i][0].active) {
            DrawCircleV(bola[i][0].position, bola[i][0].radius, bola[i][0].color);
        }
    }
}

void ResetBola(Bola bola[BOLA_ROWS][BOLA_COLS]) {
    for (int i = 0; i < BOLA_ROWS; i++) {
        bola[i][0].position = (Vector2){SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2};
        bola[i][0].speed = (Vector2){5, -5}; // Set kecepatan awal bola saat reset
        bola[i][0].active = true;
    }
}