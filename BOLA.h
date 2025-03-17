#ifndef BOLA_H
#define BOLA_H

#include <raylib.h>
#include "paddle.h"
#include "block.h"
#include "nyawa.h"
#include "stopwatch.h"

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
void UpdateBola(Bola bola[BOLA_ROWS][BOLA_COLS], Paddle paddles[PADDLE_ROWS][PADDLE_COLS], 
                Block blocks[BLOCK_ROWS][BLOCK_COLS], GameState *state, 
                Nyawa nyawa[NYAWA_BARIS][NYAWA_KOLOM], Stopwatch stopwatch[STOPWATCH_ROWS][STOPWATCH_COLS]);
void DrawBola(Bola bola[BOLA_ROWS][BOLA_COLS]);
void ResetBola(Bola bola[BOLA_ROWS][BOLA_COLS]);

#endif // BOLA_H
