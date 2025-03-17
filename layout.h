#ifndef LAYOUT_H
#define LAYOUT_H

#define SCREEN_WIDTH 800  
#define SCREEN_HEIGHT 600 
#define GAME_AREA_WIDTH (SCREEN_WIDTH - 200)  // 200 px untuk panel kanan

#include "block.h"
#include "paddle.h"
#include "bola.h"
#include "stopwatch.h"
#include "nyawa.h"  // Tambahkan nyawa di layout

void DrawGameLayout(Block blocks[][BLOCK_COLS], Paddle paddles[][PADDLE_COLS], Bola bola[][BOLA_COLS], Stopwatch sw[][STOPWATCH_COLS], Nyawa nyawa[][NYAWA_KOLOM]);

#endif
