#ifndef BOLA_H
#define BOLA_H

#include <raylib.h>
#include "paddle.h"
#include "block.h"
#include "skor.h"
#include "stopwatch.h"
#include "game_state.h"
#include "powerup.h"

typedef struct BolaNode {
    Vector2 position;
    Vector2 speed;
    float radius;
    Color color;
    bool active;
    struct BolaNode *next;
} BolaNode;

typedef struct BolaList {
    BolaNode *head;
} BolaList;

// Fungsi
void InitBola(BolaList *list);
void AddBola(BolaList *list, Vector2 position, Vector2 speed);
void UpdateBola(BolaList *list, Paddle paddles[PADDLE_ROWS][PADDLE_COLS], Block blocks[BLOCK_ROWS][BLOCK_COLS], 
               GameState *state, Skor *skor, Stopwatch sw[STOPWATCH_ROWS][STOPWATCH_COLS], PowerUpList *powerUpList);
bool SemuaBolaMati(BolaList *list);
void DrawBola(BolaList *list);
void ResetBola(BolaList *list);
void FreeBola(BolaList *list);

#endif