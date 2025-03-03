#include <stdio.h>
#include <conio.h>
#include <windows.h>

#define WIDTH 10
#define HEIGHT 10

char board[HEIGHT][WIDTH];

// Posisi bola
int ballX = 5, ballY = 8;
int dirX = 1, dirY = -2; // Arah bola

// Inisialisasi papan dengan blok dan ruang kosong
void initBoard() {
    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++) {
            if (i < 3)
                board[i][j] = '#'; // Blok
            else
                board[i][j] = ' '; // Ruang kosong
        }
    }
    board[ballY][ballX] = 'O'; // Bola
}

// Menampilkan papan permainan
void drawBoard() {
    system("cls"); // Membersihkan layar (Windows)
    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++) {
            printf("%c ", board[i][j]);
        }
        printf("\n");
    }
}

// Menggerakkan bola
void moveBall() {
    // Hapus posisi bola sebelumnya
    board[ballY][ballX] = ' ';

    // Hitung posisi baru
    int newX = ballX + dirX;
    int newY = ballY + dirY;

    // Deteksi tabrakan dengan dinding
    if (newX < 0 || newX >= WIDTH) {
        dirX *= -1; // Pantulan horizontal
        newX = ballX + dirX;
    }
    if (newY < 0) {
        dirY *= -1; // Pantulan vertikal
        newY = ballY + dirY;
    }

    // Deteksi tabrakan dengan blok
    if (board[newY][newX] == '#') {
        board[newY][newX] = ' '; // Hancurkan blok
        dirY *= -1; // Bola memantul
        newY = ballY + dirY;
    }

    // Perbarui posisi bola
    ballX = newX;
    ballY = newY;
    board[ballY][ballX] = 'O';
}

int main() {
    initBoard();

    while (1) {
        drawBoard();
        moveBall();
        Sleep(200);
    }

    return 0;
}
