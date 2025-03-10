#ifndef BALL_H
#define BALL_H

#include <SDL2/SDL.h>

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600
#define GRAVITY 0.5f
#define BOUNCE_DAMPING 0.7f

typedef struct {
    float x, y;
    float velocityX, velocityY;
    int radius;
} Ball;

void initBall(Ball *ball, float x, float y, int radius);
void updateBall(Ball *ball);
void renderBall(SDL_Renderer *renderer, Ball *ball);

#endif
