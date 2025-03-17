#ifndef LAYOUT_H
#define LAYOUT_H

#include <raylib.h>
#include "block.h"
#include "paddle.h"
#include "BOLA.h"
#include "nyawa.h"
#include "stopwatch.h"

// Tambahkan definisi untuk ukuran layar
#define DEFAULT_SCREEN_WIDTH 1000
#define DEFAULT_SCREEN_HEIGHT 650

void DrawGameLayout(Block blocks[][BLOCK_COLS], Paddle paddles[][PADDLE_COLS], Bola bola[][BOLA_COLS], Stopwatch sw[][STOPWATCH_COLS], Nyawa nyawa[][NYAWA_KOLOM]);
void SetScreenSize(int width, int height); // Fungsi untuk mengatur ukuran layar

void layout();

 
#endif // LAYOUT_H