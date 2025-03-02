// bola.h - File berisi fungsi-fungsi terkait bola
#ifndef BOLA_H
#define BOLA_H

#include <stdlib.h>
#include "definisi.h"
#include "paddle.h"
#include "blok.h"

// Inisialisasi bola
void inisialisasiBola(Bola *bola, Paddle paddle) {
    bola->x = paddle.x + paddle.panjang / 2;
    bola->y = paddle.y - 1;
    bola->dx = 0; // Bola diam sampai dimulai
    bola->dy = 0; // Bola diam sampai dimulai
    bola->bentuk = 'O';
}

// Mulai gerakan bola
void mulaiBola(Bola *bola) {
    // Berikan arah acak ke bola saat mulai
    bola->dx = (rand() % 2 == 0) ? 1 : -1;
    bola->dy = -1; // Bergerak ke atas pertama kali
}

// Menampilkan bola di layar
void tampilkanBola(char layar[BARIS][LEBAR_LAYAR], Bola bola) {
    layar[bola.y][bola.x] = bola.bentuk;
}

// Memeriksa tabrakan bola dengan dinding
void cekTabrakanDinding(Bola *bola) {
    // Cek tabrakan dengan dinding samping
    if (bola->x <= AREA_GAME_MULAI || bola->x >= LEBAR_LAYAR - 2) {
        bola->dx = -bola->dx; // Pantulan horizontal
    }
    
    // Cek tabrakan dengan dinding atas
    if (bola->y <= 0) {
        bola->dy = -bola->dy; // Pantulan atas
    }
}

// Memeriksa tabrakan bola dengan paddle
void cekTabrakanPaddle(Bola *bola, Paddle paddle) {
    if (bola->y == paddle.y - 1 && bola->x >= paddle.x && bola->x < paddle.x + paddle.panjang) {
        bola->dy = -bola->dy; // Pantulan vertikal
        
        // Atur arah horizontal berdasarkan posisi hit pada paddle untuk kontrol arah
        int hitPos = bola->x - paddle.x;
        if (hitPos < paddle.panjang / 3) {
            bola->dx = -1; // Hit di sebelah kiri paddle, bola ke kiri
        } else if (hitPos > (2 * paddle.panjang) / 3) {
            bola->dx = 1; // Hit di sebelah kanan paddle, bola ke kanan
        }
    }
}

// Gerakan bola dan deteksi tabrakan
int gerakkanBola(Bola *bola, Paddle paddle, Blok blok[JUMLAH_BLOK_BARIS][JUMLAH_BLOK_KOLOM], DataPermainan *data) {
    if (bola->dx == 0 && bola->dy == 0) {
        // Jika bola belum bergerak, ikuti paddle
        bola->x = paddle.x + paddle.panjang / 2;
        bola->y = paddle.y - 1;
        return 0;
    }
    
    // Cek tabrakan dengan dinding
    cekTabrakanDinding(bola);
    
    // Cek jika bola jatuh ke bawah (melewati paddle)
    if (bola->y + bola->dy >= BARIS) {
        // Kehilangan bola, kurangi nyawa
        data->nyawa--;
        if (data->nyawa <= 0) {
            return 1; // Game over
        }
        
        // Reset posisi bola
        inisialisasiBola(bola, paddle);
        return 0;
    }
    
    // Cek tabrakan dengan paddle
    cekTabrakanPaddle(bola, paddle);
    
    // Cek tabrakan dengan blok
    if (cekTabrakanBlok(bola, blok, data) == 1) {
        return 2; // Level selesai
    }
    
    // Perbarui posisi bola
    bola->x += bola->dx;
    bola->y += bola->dy;
    
    return 0;
}

#endif // BOLA_H