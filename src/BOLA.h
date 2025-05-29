#ifndef BOLA_H
#define BOLA_H

#include <raylib.h>
// #include "paddle.h" // No, forward declare PaddleList
#include "LinkedList-Block.h"
#include "skor.h"
#include "stopwatch.h"
#include "game_state.h"
// #include "powerup.h" // No, forward declare PowerUpList

// Forward declarations
struct PaddleList; // Defined in paddle.h
struct PowerUpList; // Defined in powerup.h

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
// UpdateBola now takes PaddleList
void UpdateBola(BolaList *list, struct PaddleList *paddleList, LinkedList* blockList,
                GameState *state, Skor *skor, Stopwatch* stopwatchList, struct PowerUpList *powerUpList);
bool SemuaBolaMati(BolaList *list);
void DrawBola(BolaList *list);
void ResetBola(BolaList *list);
void FreeBola(BolaList *list);

#endif //BOLA_H