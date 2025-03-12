// paddle.h - File berisi fungsi-fungsi terkait paddle
#ifndef PADDLE_H
#define PADDLE_H

#include "definisi.h"

// Inisialisasi paddle
void inisialisasiPaddle(Paddle *paddle) {
    paddle->x = AREA_GAME_MULAI + (LEBAR_LAYAR - AREA_GAME_MULAI) / 2 - PADDLE_PANJANG / 2;
    paddle->y = BARIS - 3;
    paddle->panjang = PADDLE_PANJANG;
    paddle->bentuk = '=';
}

// Menampilkan paddle di layar
void tampilkanPaddle(char layar[BARIS][LEBAR_LAYAR], Paddle paddle) {
    for (int i = 0; i < paddle.panjang; i++) {
        layar[paddle.y][paddle.x + i] = paddle.bentuk;
    }
}

// Menggerakkan paddle ke kiri
void gerakkanPaddleKiri(Paddle *paddle) {
    if (paddle->x > AREA_GAME_MULAI) {
        paddle->x--;
    }
}

// Menggerakkan paddle ke kanan
void gerakkanPaddleKanan(Paddle *paddle) {
    if (paddle->x + paddle->panjang < LEBAR_LAYAR - 2) {
        paddle->x++;
    }
}

#endif // PADDLE_H