#ifndef BOLA_H
#define BOLA_H

#include "raylib.h"

typedef struct {
    Vector2 position;
    Vector2 speed;
    float radius;
    bool active;
} Bola;

void InitBola(Bola *bola, Vector2 startPosition, Vector2 startSpeed, float radius);
void UpdateBola(Bola *bola, int screenWidth, int screenHeight);
void DrawBola(Bola *bola);

#endif
