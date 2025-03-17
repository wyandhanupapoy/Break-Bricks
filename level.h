#ifndef LEVEL_H
#define LEVEL_H

#include "raylib.h"
#include "block.h"

void InitLevelBlocks(Block blocks[BLOCK_ROWS][BLOCK_COLS]);
void UpdateBlockState(Block *block);

#endif
