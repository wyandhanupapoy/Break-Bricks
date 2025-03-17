#include "level.h"
#include "block.h"
#include <raylib.h>

int main(){
    void InitGameLevel(Block blocks[BLOCK_ROWS][BLOCK_COLS], int level) {
    SetLevel(blocks, level);
    }
}
