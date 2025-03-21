#include "level.h"
#include "raylib.h"
#include <stdlib.h> // Untuk fungsi rand()
#include <time.h>   // Untuk seeding angka acak

void InitLevelBlocks(Block blocks[BLOCK_ROWS][BLOCK_COLS], int level)
{
    srand(time(NULL));

    Color colors[3] = {DARKGRAY, BROWN, BEIGE};

    for (int i = 0; i < BLOCK_ROWS; i++)
    {
        for (int j = 0; j < BLOCK_COLS; j++)
        {
            blocks[i][j].rect.x = j * (BLOCK_WIDTH + BLOCK_SPACING) + 15;
            blocks[i][j].rect.y = i * (BLOCK_HEIGHT + BLOCK_SPACING) + 70;
            blocks[i][j].rect.width = BLOCK_WIDTH;
            blocks[i][j].rect.height = BLOCK_HEIGHT;
            blocks[i][j].active = true;

            if (level == 1)
            {
                blocks[i][j].hitPoints = 1;
                blocks[i][j].color = BEIGE;
            }
            else if (level == 2)
            {
                int randomType = rand() % 2; // 0 atau 1
                if (randomType == 0)
                {
                    blocks[i][j].hitPoints = 1;
                    blocks[i][j].color = BEIGE;
                }
                else
                {
                    blocks[i][j].hitPoints = 2;
                    blocks[i][j].color = BROWN;
                }
            }
            else if (level == 3)
            {
                int randomType = rand() % 2; // 0 atau 1
                if (randomType == 0)
                {
                    blocks[i][j].hitPoints = 1;
                    blocks[i][j].color = BEIGE;
                }
                else
                {
                    blocks[i][j].hitPoints = 3;
                    blocks[i][j].color = DARKGRAY;
                }
            }
        }
    }
}

void UpdateBlockState(Block *block)
{
    if (!block->active)
        return;

    block->hitPoints--;

    if (block->hitPoints <= 0)
    {
        block->active = false;
    }
    else
    {
        // Update warna blok sesuai sisa hitPoints
        if (block->hitPoints == 2)
        {
            block->color = BROWN;
        }
        else if (block->hitPoints == 1)
        {
            block->color = BEIGE;
        }
    }
}

// **Implementasi SetLevel**
void SetLevel(Block blocks[BLOCK_ROWS][BLOCK_COLS], int level)
{
    InitLevelBlocks(blocks, level);
}
