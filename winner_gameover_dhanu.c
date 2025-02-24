#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <string.h>

#define WIDTH 50
#define HEIGHT 10

// Struktur untuk mendefinisikan tombol
typedef struct {
    int x, y;
    char label[10];
} Button;

// Fungsi untuk menggambar tombol menggunakan ANSI escape codes
void drawButton(Button btn) {
    printf("\033[%d;%dH[ %s ]", btn.y, btn.x, btn.label);  // Pindahkan kursor ke posisi (y, x)
}

// Fungsi untuk memeriksa apakah klik mouse terjadi di atas tombol
int isButtonClicked(Button btn, int mouseX, int mouseY) {
    if (mouseX >= btn.x && mouseX < btn.x + strlen(btn.label) + 4 && mouseY == btn.y) {
        return 1; // Tombol diklik
    }
    return 0; // Tombol tidak diklik
}

// Fungsi untuk mendapatkan posisi mouse
void getMousePosition(int *x, int *y) {
    POINT p;
    if (GetCursorPos(&p)) {
        *x = p.x / 8;  // Sesuaikan dengan ukuran terminal
        *y = p.y / 16; // Sesuaikan dengan ukuran terminal
    }
}

int main() {
    // Membuat dua tombol dengan posisi dan label
    Button buttons[2] = {
        {10, 5, "Start"},
        {30, 5, "Exit"}
    };

    int mouseX, mouseY;
    int quit = 0;

    // Loop utama game
    while (!quit) {
        system("cls"); // Bersihkan layar
        for (int i = 0; i < 2; i++) {
            drawButton(buttons[i]); // Gambar semua tombol
        }

        getMousePosition(&mouseX, &mouseY); // Dapatkan posisi mouse

        // Cek jika tombol Start diklik
        if (isButtonClicked(buttons[0], mouseX, mouseY)) {
            printf("\033[1;1H"); // Pindahkan kursor ke atas kiri
            printf("Tombol Start Diklik!\n");
        }

        // Cek jika tombol Exit diklik
        if (isButtonClicked(buttons[1], mouseX, mouseY)) {
            printf("\033[1;1H"); // Pindahkan kursor ke atas kiri
            printf("Tombol Exit Diklik! Program Selesai.\n");
            quit = 1;
        }

        Sleep(100); // Tunggu sebentar sebelum refresh layar
    }

    return 0;
}
