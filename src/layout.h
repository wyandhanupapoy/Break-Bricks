// Nama Pembuat: Nezya Zulfa Fauziah
// Nama Fitur: Layout
// Deskripsi: Fitur layout mengatur tampilan elemen-elemen dalam game **Break Bricks** agar lebih rapi dan intuitif. Arena permainan menampilkan paddle, bola, dan blok, sementara panel di sisi kanan menampilkan skor, nyawa, dan stopwatch. Instruksi kontrol juga ditampilkan untuk memudahkan pemain. Dengan tata letak yang terorganisir, permainan menjadi lebih nyaman dan interaktif.

#ifndef LAYOUT_H // Mencegah penggandaan header jika sudah didefinisikan sebelumnya
#define LAYOUT_H

#include <raylib.h> // Library utama untuk grafis dan input
#include "skor.h"
#include "linkedlist_nyawa.h"
#include "block.h"
#include "BOLA.h"
#include "stopwatch.h"
#include "game_state.h"

// Definisi posisi dan ukuran elemen UI di panel kanan
#define SCORE_X 870
#define SCORE_Y 50
#define NYAWA_X 940
#define NYAWA_Y 5
#define STOPWATCH_X 870
#define STOPWATCH_Y 80

// Fungsi untuk menggambar berbagai tampilan dalam game
void DrawPauseScreen();
void DrawGameOverScreen();
void DrawWinScreen();
void DrawControlInfo();
void DrawInfo();

#endif // LAYOUT_H
