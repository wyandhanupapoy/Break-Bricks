// src/BOLA.h
#ifndef BOLA_H
#define BOLA_H

#include <raylib.h>
#include "LinkedList-Block.h"
#include "skor.h"
#include "stopwatch.h"
#include "game_state.h"

// Pindahkan definisi konstanta bola ke sini
#define GAME_AREA_WIDTH_BOLA 830 // Nama yang lebih spesifik, sebelumnya SCREEN_W
#define GAME_AREA_HEIGHT_BOLA 600 // Nama yang lebih spesifik, sebelumnya SCREEN_H
#define MIN_BALL_SPEED 6.0f
#define MAX_BALL_SPEED 9.0f

// Forward declarations
struct PaddleList;
struct PowerUpList;

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

void InitBola(BolaList *list);
void AddBola(BolaList *list, Vector2 position, Vector2 speed);
void UpdateBola(BolaList *list, struct PaddleList *paddleList, LinkedList* blockList,
                GameState *state, Skor *skor, Stopwatch* stopwatchList, struct PowerUpList *powerUpList);
bool SemuaBolaMati(BolaList *list);
void DrawBola(BolaList *list);
void ResetBola(BolaList *list);
void FreeBola(BolaList *list);

#endif //BOLA_H