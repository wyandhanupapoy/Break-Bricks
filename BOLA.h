#ifndef BOLA_H
#define BOLA_H

#include <raylib.h>
#include "paddle.h"
#include "block.h"
#include "skor.h"
#include "stopwatch.h"
#include "game_state.h"

#define BOLA_ROWS 1
#define BOLA_COLS 1

typedef struct
{
    Vector2 position;
    Vector2 speed;
    float radius;
    Color color;
    bool active;
} Bola;

void InitBola(Bola bola[BOLA_ROWS][BOLA_COLS]);
void UpdateBola(Bola bola[BOLA_ROWS][BOLA_COLS], Paddle paddles[PADDLE_ROWS][PADDLE_COLS], Block blocks[BLOCK_ROWS][BLOCK_COLS], GameState *state, Skor *skor, Stopwatch sw[STOPWATCH_ROWS][STOPWATCH_COLS]);
void DrawBola(Bola bola[BOLA_ROWS][BOLA_COLS]);
void ResetBola(Bola bola[BOLA_ROWS][BOLA_COLS]);

#endif // BOLA_H