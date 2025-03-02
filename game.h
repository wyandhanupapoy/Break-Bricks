// game.h - File berisi fungsi-fungsi utama game
#ifndef GAME_H
#define GAME_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <conio.h>
#include <windows.h>

#include "definisi.h"
#include "tampilan.h"
#include "paddle.h"
#include "bola.h"
#include "blok.h"

// Mulai level baru
void mulaiLevelBaru(DataPermainan *data, Paddle *paddle, Bola *bola, Blok blok[JUMLAH_BLOK_BARIS][JUMLAH_BLOK_KOLOM]) {
    data->level++;
    data->kecepatan = data->kecepatan > 10 ? data->kecepatan - 10 : 10;
    data->blok_tersisa = TOTAL_BLOK;
    
    // Reset posisi paddle dan bola
    inisialisasiPaddle(paddle);
    inisialisasiBola(bola, *paddle);
    
    // Setup blok baru
    inisialisasiBlok(blok);
}

// Proses input pemain
void prosesInput(char input, Paddle *paddle, Bola *bola, int *bolaBergerak, int *gameSelesai) {
    switch (input) {
        case 'a': case 'A':
            gerakkanPaddleKiri(paddle);
            break;
        case 'd': case 'D':
            gerakkanPaddleKanan(paddle);
            break;
        case ' ': // Spasi untuk mulai bola bergerak
            if (!(*bolaBergerak)) {
                mulaiBola(bola);
                *bolaBergerak = 1;
            }
            break;
        case 'q': case 'Q':
            *gameSelesai = 1;
            break;
    }
}

// Fungsi utama game
void mainkanGame() {
    char layar[BARIS][LEBAR_LAYAR];
    DataPermainan data = {0, 1, 100, "Player", 0, 3, TOTAL_BLOK};
    Paddle paddle;
    Bola bola;
    Blok blok[JUMLAH_BLOK_BARIS][JUMLAH_BLOK_KOLOM];
    time_t waktuMulai, waktuSekarang;
    char input;
    int gameSelesai = 0;
    int bolaBergerak = 0;
    
    // Sembunyikan kursor
    sembunyikanKursor();
    
    // Setup awal permainan
    printf("Masukkan nama Anda: ");
    scanf("%s", data.nama);
    
    inisialisasiLayar(layar);
    inisialisasiPaddle(&paddle);
    inisialisasiBola(&bola, paddle);
    inisialisasiBlok(blok);
    
    waktuMulai = time(NULL);
    
    // Loop utama game
    while (!gameSelesai) {
        // Perbarui waktu
        waktuSekarang = time(NULL);
        data.waktu_bermain = (int)(waktuSekarang - waktuMulai);
        
        // Kosongkan layar untuk diperbarui
        inisialisasiLayar(layar);
        
        // Tampilkan informasi di sisi kiri
        tampilkanInfoSisiKiri(layar, data);
        
        // Tampilkan objek game di sisi kanan
        tampilkanPaddle(layar, paddle);
        tampilkanBola(layar, bola);
        tampilkanBlok(layar, blok);
        
        // Tampilkan layar
        tampilkanLayar(layar, data);
        
        // Cek input pengguna
        if (kbhit()) {
            input = getch();
            prosesInput(input, &paddle, &bola, &bolaBergerak, &gameSelesai);
        }
        
        // Gerakan bola dan deteksi tabrakan
        int hasilGerakan = gerakkanBola(&bola, paddle, blok, &data);
        
        // Cek hasil gerakan bola
        if (hasilGerakan == 1) {
            // Game over
            gameSelesai = 1;
        } else if (hasilGerakan == 2) {
            // Level selesai
            tampilkanLevelSelesai(data.level);
            mulaiLevelBaru(&data, &paddle, &bola, blok);
            bolaBergerak = 0;
        }
        
        // Delay
        Sleep(data.kecepatan);
    }
    
    // Tampilkan pesan akhir permainan
    tampilkanGameOver(data);
}

#endif // GAME_H