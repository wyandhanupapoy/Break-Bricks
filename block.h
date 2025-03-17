#ifndef BLOCK_H
#define BLOCK_H

#include <raylib.h>

#define BLOCK_ROWS 5
#define BLOCK_COLS 10
#define BLOCK_WIDTH 75
#define BLOCK_HEIGHT 25
#define BLOCK_SPACING 5

typedef struct {
    Rectangle rect;
    bool active;
    Color color;
    int durability;
} Block;

void InitBlocks(Block blocks[BLOCK_ROWS][BLOCK_COLS], int level);
void DrawBlocks(Block blocks[BLOCK_ROWS][BLOCK_COLS]);
bool CheckBallBlockCollision(Vector2 ballPosition, float ballRadius, Block *block);
void UpdateBlockState(Block *block);
bool AllBlocksDestroyed(Block blocks[BLOCK_ROWS][BLOCK_COLS]);

#endif // BLOCK_H