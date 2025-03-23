#ifndef LAYOUT_H
#define LAYOUT_H

#include <raylib.h>
#include "skor.h"
#include "nyawa.h"
#include "block.h"
#include "BOLA.h"
#include "stopwatch.h"
#include "game_state.h"

// Definisi posisi dan ukuran elemen
#define SCORE_X 870
#define SCORE_Y 50
#define NYAWA_X 940
#define NYAWA_Y 5
#define STOPWATCH_X 870
#define STOPWATCH_Y 80

void DrawPauseScreen();
void DrawGameOverScreen();
void DrawWinScreen();
void DrawControlInfo();

#endif // LAYOUT_H
