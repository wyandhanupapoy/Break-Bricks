#ifndef BOLA_H
#define BOLA_H

#include <raylib.h>
#include "paddle.h"
#include "block.h"
#include "skor.h"
#include "stopwatch.h"
#include "game_state.h"

// Struktur untuk node bola dalam linked list
typedef struct BolaNode {
    Vector2 position;
    Vector2 speed;
    float radius;
    Color color;
    bool active;
    struct BolaNode* next; // Pointer ke bola berikutnya
} BolaNode;

// Fungsi untuk mengelola bola
void InitBola(BolaNode** head);
void UpdateBola(BolaNode* head, Paddle paddles[PADDLE_ROWS][PADDLE_COLS], Block blocks[BLOCK_ROWS][BLOCK_COLS], GameState *state, Skor *skor, Stopwatch sw[STOPWATCH_ROWS][STOPWATCH_COLS]);
void DrawBola(BolaNode* head);
void ResetBola(BolaNode** head);

#endif // BOLA_H
