// tampilan.h - File berisi fungsi-fungsi untuk menampilkan dan memanipulasi layar
#ifndef TAMPILAN_H
#define TAMPILAN_H

#include <stdio.h>
#include <string.h>
#include <windows.h>
#include "definisi.h"

// Fungsi untuk mengatur posisi kursor
void gotoxy(int x, int y) {
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

// Fungsi untuk menyembunyikan kursor
void sembunyikanKursor() {
    CONSOLE_CURSOR_INFO info;
    info.dwSize = 100;
    info.bVisible = FALSE;
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &info);
}

// Fungsi untuk menampilkan layar
void tampilkanLayar(char layar[BARIS][LEBAR_LAYAR], DataPermainan data) {
    system("cls"); // Membersihkan layar
    
    // Tampilkan bingkai atas
    printf("+");
    for (int i = 0; i < LEBAR_LAYAR - 2; i++) {
        printf("-");
    }
    printf("+\n");
    
    // Tampilkan isi layar
    for (int i = 0; i < BARIS; i++) {
        printf("|");
        for (int j = 0; j < LEBAR_LAYAR - 2; j++) {
            printf("%c", layar[i][j]);
        }
        printf("|\n");
    }
    
    // Tampilkan bingkai bawah
    printf("+");
    for (int i = 0; i < LEBAR_LAYAR - 2; i++) {
        printf("-");
    }
    printf("+\n");
    
    // Tampilkan informasi permainan di bagian bawah layar
    printf("Nama: %s | Skor: %d | Nyawa: %d | Level: %d\n", 
           data.nama, data.skor, data.nyawa, data.level);
}

// Fungsi untuk menginisialisasi layar
void inisialisasiLayar(char layar[BARIS][LEBAR_LAYAR]) {
    // Kosongkan seluruh layar
    for (int i = 0; i < BARIS; i++) {
        for (int j = 0; j < LEBAR_LAYAR - 2; j++) {
            layar[i][j] = ' ';
        }
    }
    
    // Buat garis pemisah antara sisi kiri (informasi) dan sisi kanan (game)
    for (int i = 0; i < BARIS; i++) {
        layar[i][AREA_GAME_MULAI - 1] = '|';
    }
}

// Fungsi untuk menampilkan informasi di sisi kiri
void tampilkanInfoSisiKiri(char layar[BARIS][LEBAR_LAYAR], DataPermainan data) {
    // Judul
    char judul[] = "BREAKOUT";
    int posJudul = (AREA_GAME_MULAI - strlen(judul)) / 2;
    for (int i = 0; i < strlen(judul); i++) {
        layar[2][posJudul + i] = judul[i];
    }
    
    // Informasi skor
    char skorStr[20];
    sprintf(skorStr, "SKOR: %d", data.skor);
    int posSkor = 2;
    for (int i = 0; i < strlen(skorStr); i++) {
        layar[5][posSkor + i] = skorStr[i];
    }
    
    // Informasi nyawa
    char nyawaStr[20];
    sprintf(nyawaStr, "NYAWA: %d", data.nyawa);
    int posNyawa = 2;
    for (int i = 0; i < strlen(nyawaStr); i++) {
        layar[7][posNyawa + i] = nyawaStr[i];
    }
    
    // Informasi level
    char levelStr[20];
    sprintf(levelStr, "LEVEL: %d", data.level);
    int posLevel = 2;
    for (int i = 0; i < strlen(levelStr); i++) {
        layar[9][posLevel + i] = levelStr[i];
    }
    
    // Informasi blok tersisa
    char blokStr[20];
    sprintf(blokStr, "BLOK: %d", data.blok_tersisa);
    int posBlok = 2;
    for (int i = 0; i < strlen(blokStr); i++) {
        layar[11][posBlok + i] = blokStr[i];
    }
    
    // Instruksi kontrol
    char instruksi1[] = "KONTROL:";
    int posInstruksi1 = 2;
    for (int i = 0; i < strlen(instruksi1); i++) {
        layar[14][posInstruksi1 + i] = instruksi1[i];
    }
    
    char instruksi2[] = "A - Kiri";
    int posInstruksi2 = 2;
    for (int i = 0; i < strlen(instruksi2); i++) {
        layar[15][posInstruksi2 + i] = instruksi2[i];
    }
    
    char instruksi3[] = "D - Kanan";
    int posInstruksi3 = 2;
    for (int i = 0; i < strlen(instruksi3); i++) {
        layar[16][posInstruksi3 + i] = instruksi3[i];
    }
    
    char instruksi4[] = "SPACE - Mulai";
    int posInstruksi4 = 2;
    for (int i = 0; i < strlen(instruksi4); i++) {
        layar[17][posInstruksi4 + i] = instruksi4[i];
    }
    
    char instruksi5[] = "Q - Keluar";
    int posInstruksi5 = 2;
    for (int i = 0; i < strlen(instruksi5); i++) {
        layar[18][posInstruksi5 + i] = instruksi5[i];
    }
}

// Tampilkan pesan level selesai
void tampilkanLevelSelesai(int level) {
    system("cls");
    printf("\n\n\n");
    printf("\t\tLEVEL %d SELESAI!\n\n", level);
    printf("\t\tTekan tombol apa saja untuk melanjutkan ke level berikutnya...");
    getch();
}

// Tampilkan pesan game over
void tampilkanGameOver(DataPermainan data) {
    system("cls");
    printf("\n\n\n");
    printf("\t\tGAME OVER\n\n");
    printf("\t\tNama: %s\n", data.nama);
    printf("\t\tSkor Akhir: %d\n", data.skor);
    printf("\t\tLevel Dicapai: %d\n", data.level);
    printf("\t\tWaktu Bermain: %d detik\n\n", data.waktu_bermain);
    printf("\t\tTekan tombol apa saja untuk keluar...");
    getch();
}

#endif // TAMPILAN_H