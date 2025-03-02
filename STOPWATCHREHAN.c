#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <windows.h>

int main() {
    char input;
    clock_t start, current;
    double elapsed_time;
    int score;

    printf("=== Stopwatch Game ===\n");
    printf("Tekan ENTER untuk memulai stopwatch...\n");
    getchar(); // Menunggu input untuk mulai

    start = clock(); // Mulai stopwatch

    printf("Stopwatch berjalan... Tekan ENTER untuk berhenti!\n");

    while (!_kbhit()) { // Loop sampai ada input keyboard
        current = clock();
        elapsed_time = ((double)(current - start)) / CLOCKS_PER_SEC;
        printf("\rWaktu: %.2f detik", elapsed_time);
        fflush(stdout);
        Sleep(100); // Tunggu 100 ms biar tampilan lebih stabil
    }

    getchar(); // Mengambil input untuk berhenti
    
    current = clock(); // Waktu berhenti akhir
    elapsed_time = ((double)(current - start)) / CLOCKS_PER_SEC;

    // Hitung skor (semakin cepat waktu, skor lebih tinggi)
    score = (int)(1000 / elapsed_time);

    printf("\n\nWaktu akhir: %.2f detik\n", elapsed_time);
    printf("Skor: %d\n", score);

    printf("\nTekan ENTER untuk keluar...\n");
    getchar();

    return 0;
}

// Dengan ini, kamu bisa lihat waktu berjalan secara real-time!
// Jangan lupa compile jadi .exe pakai GCC atau compiler favoritmu 🚀
