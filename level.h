#ifndef LEVEL_H
#define LEVEL_H

#include "block.h"

void InitLevelBlocks(Block blocks[BLOCK_ROWS][BLOCK_COLS], int level);
void SetLevel(Block blocks[BLOCK_ROWS][BLOCK_COLS], int level);  // Sekarang sudah diimplementasikan!
void UpdateBlockState(Block *block);

#endif // LEVEL_H
