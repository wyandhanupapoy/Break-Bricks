// setup.h
#ifndef SETUP_H
#define SETUP_H

#include "game.h"

void setup()
{
    ballX = 10;
    ballY = 5;
    ballDirX = 1;
    ballDirY = 1;
    paddleX = 20;
    paddleWidth = 10;
    score = 0;

    for (int i = 0; i < 5; i++)
    {
        for (int j = 0; j < 5; j++)
        {
            block[i][j] = 1; 
        }
    }
}

#endif