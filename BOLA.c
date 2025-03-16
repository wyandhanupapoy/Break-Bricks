#include "BOLA.h"

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600

void InitBola(Bola bola[BOLA_ROWS][BOLA_COLS]) {
    for (int i = 0; i < BOLA_ROWS; i++) {
        for (int j = 0; j < BOLA_COLS; j++) {
            bola[i][j].position = (Vector2){SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2};
            bola[i][j].speed = (Vector2){0, 0};
            bola[i][j].radius = 10;
            bola[i][j].color = RED;
            bola[i][j].active = true;
        }
    }
}

void UpdateBola(Bola bola[BOLA_ROWS][BOLA_COLS], Paddle paddles[PADDLE_ROWS][PADDLE_COLS], GameState *state) {
    for (int i = 0; i < BOLA_ROWS; i++) {
        if (bola[i][0].active) {
            bola[i][0].position.x += bola[i][0].speed.x;
            bola[i][0].position.y += bola[i][0].speed.y;

            // Collision with paddles
            for (int j = 0; j < PADDLE_ROWS; j++) {
                for (int k = 0; k < PADDLE_COLS; k++) {
                    if (CheckCollisionCircleRec(bola[i][0].position, bola[i][0].radius, paddles[j][k].rect)) {
                        bola[i][0].speed.y *= -1; // Bounce back
                    }
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
        bola[i][0].speed = (Vector2){0, 0};
        bola[i][0].active = true;
    }
}