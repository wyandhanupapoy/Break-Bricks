// draw.h
#ifndef DRAW_H
#define DRAW_H

#include "game.h"
#include <stdio.h>

void draw()
[
    for (int i = 0; i < 5; i++)
    {
        for (int j = 0; j < 5; j++)
        {
            if (block[i][j] == 1)
            {
                printf("X ");
            }else{
                printf("  ");
            }
        }
        printf("\n");
    }
    for (int i = 0; i < 40; i++)
    {
        if (i == paddleX)
        {
            for (int j = 0; j < paddleWidth; j++)
            {
                printf("-");
            }
        }else{
            printf(" ");
        }
    }
    printf ("\nBall Position: (%d,%d)\n", ballX, ballY);
    printf ("Scorer: %d\n", score);
]

#endif