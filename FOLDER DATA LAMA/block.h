// blok.h - File berisi fungsi-fungsi terkait blok
#ifndef BLOCK_H
#define BLOCK_H

#include "definisi.h"

// Inisialisasi blok
void inisialisasiBlok(Blok blok[JUMLAH_BLOK_BARIS][JUMLAH_BLOK_KOLOM]) {
    int nilai_baris[JUMLAH_BLOK_BARIS] = {30, 20, 10}; // Nilai blok berdasarkan baris
    char bentuk_baris[JUMLAH_BLOK_BARIS] = {'#', '%', '&'}; // Bentuk blok berdasarkan baris
    
    for (int i = 0; i < JUMLAH_BLOK_BARIS; i++) {
        for (int j = 0; j < JUMLAH_BLOK_KOLOM; j++) {
            blok[i][j].x = AREA_GAME_MULAI + 2 + j * 4; // Spasi 4 karakter antar blok
            blok[i][j].y = 3 + i * 2; // Spasi 2 baris antar baris blok
            blok[i][j].aktif = 1;
            blok[i][j].bentuk = bentuk_baris[i];
            blok[i][j].nilai = nilai_baris[i];
        }
    }
}

// Menampilkan blok di layar
void tampilkanBlok(char layar[BARIS][LEBAR_LAYAR], Blok blok[JUMLAH_BLOK_BARIS][JUMLAH_BLOK_KOLOM]) {
    for (int i = 0; i < JUMLAH_BLOK_BARIS; i++) {
        for (int j = 0; j < JUMLAH_BLOK_KOLOM; j++) {
            if (blok[i][j].aktif) {
                layar[blok[i][j].y][blok[i][j].x] = blok[i][j].bentuk;
                layar[blok[i][j].y][blok[i][j].x + 1] = blok[i][j].bentuk;
                layar[blok[i][j].y][blok[i][j].x + 2] = blok[i][j].bentuk;
            }
        }
    }
}

// Memeriksa tabrakan bola dengan blok
int cekTabrakanBlok(Bola *bola, Blok blok[JUMLAH_BLOK_BARIS][JUMLAH_BLOK_KOLOM], DataPermainan *data) {
    for (int i = 0; i < JUMLAH_BLOK_BARIS; i++) {
        for (int j = 0; j < JUMLAH_BLOK_KOLOM; j++) {
            if (blok[i][j].aktif) {
                // Cek apakah bola akan mengenai blok pada langkah berikutnya
                if ((bola->y + bola->dy == blok[i][j].y) && 
                    (bola->x + bola->dx >= blok[i][j].x && bola->x + bola->dx <= blok[i][j].x + 2)) {
                    // Blok terkena!
                    blok[i][j].aktif = 0;
                    data->skor += blok[i][j].nilai;
                    data->blok_tersisa--;
                    
                    // Pantulan bola
                    bola->dy = -bola->dy;
                    
                    // Cek jika semua blok sudah hancur
                    if (data->blok_tersisa <= 0) {
                        return 1; // Level selesai
                    }
                    break;
                }
            }
        }
    }
    return 0;
}

#endif // BLOK_H