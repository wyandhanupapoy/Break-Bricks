//Nama Pembuat: Nezya Zulfa Fauziah  
//Nama Fitur: Layout  
//Deskripsi: Fitur layout mengatur tampilan elemen-elemen dalam game **Break Bricks** agar lebih rapi dan intuitif. Arena permainan menampilkan paddle, bola, dan blok, sementara panel di sisi kanan menampilkan skor, nyawa, dan stopwatch. Instruksi kontrol juga ditampilkan untuk memudahkan pemain. Dengan tata letak yang terorganisir, permainan menjadi lebih nyaman dan interaktif.

#ifndef LAYOUT_H
#define LAYOUT_H

#include <raylib.h>
#include "skor.h"
#include "nyawa.h"
#include "block.h"
#include "BOLA.h"

// Definisi posisi dan ukuran elemen
#define SCORE_X 870
#define SCORE_Y 50
#define NYAWA_X 870
#define NYAWA_Y 10
#define STOPWATCH_X 870
#define STOPWATCH_Y 80

// Fungsi untuk menggambar layout permainan
void DrawGameLayout(Block blocks[BLOCK_ROWS][BLOCK_COLS], Paddle paddles[PADDLE_ROWS][PADDLE_COLS], Bola bola[BOLA_ROWS][BOLA_COLS], Stopwatch stopwatch[STOPWATCH_ROWS][STOPWATCH_COLS], Nyawa nyawa[NYAWA_BARIS][NYAWA_KOLOM], Skor skor[MAX_PLAYERS]);

#endif // LAYOUT_H
