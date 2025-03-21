#ifndef LAYOUT_H
#define LAYOUT_H

#include "block.h"
#include "paddle.h"
#include "BOLA.h"
#include "nyawa.h" // <--- Tambahin ini!
#include "skor.h"
#include "stopwatch.h"

#define SCORE_X 870
#define SCORE_Y 50

#define STOPWATCH_X 870
#define STOPWATCH_Y 80

#define NYAWA_X 850
#define NYAWA_Y 20

void DrawGameLayout(Block blocks[BLOCK_ROWS][BLOCK_COLS],
                    Paddle paddles[PADDLE_ROWS][PADDLE_COLS],
                    Bola bola[BOLA_ROWS][BOLA_COLS],
                    Stopwatch stopwatch[STOPWATCH_ROWS][STOPWATCH_COLS],
                    Nyawa nyawa[NYAWA_BARIS][NYAWA_KOLOM],
                    Skor skor[MAX_PLAYERS]);

#endif
