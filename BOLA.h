#ifndef BOLA_H
#define BOLA_H

#include "raylib.h"
#include "paddle.h"

#define BOLA_ROWS 1
#define BOLA_COLS 1

typedef enum {
    GAME_START,
    GAME_PLAY,
    GAME_OVER,
    GAME_WIN
} GameState;

typedef struct {
    Vector2 position;
    Vector2 speed;
    float radius;
    Color color;
    bool active;
} Bola;

void InitBola(Bola bola[BOLA_ROWS][BOLA_COLS]);
void UpdateBola(Bola bola[BOLA_ROWS][BOLA_COLS], Paddle paddles[PADDLE_ROWS][PADDLE_COLS], GameState *state);
void DrawBola(Bola bola[BOLA_ROWS][BOLA_COLS]);
void ResetBola(Bola bola[BOLA_ROWS][BOLA_COLS]);

#endif // BOLA_H
