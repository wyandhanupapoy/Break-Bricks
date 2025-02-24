#include <stdio.h>
#include <conio.h>  // Untuk fungsi getch() (khusus Windows)
#include <stdlib.h> // Untuk system("cls")

#define WIDTH 20  // Lebar area permainan
#define HEIGHT 10 // Tinggi area permainan

char gameBoard[HEIGHT][WIDTH]; // Array 2D untuk arena permainan
int paddleX = WIDTH / 2 - 2;   // Posisi awal papan pemantul (tengah)

void initGame()
{
    // Mengisi array 2D dengan spasi (kosong)
    for (int i = 0; i < HEIGHT; i++)
    {
        for (int j = 0; j < WIDTH; j++)
        {
            gameBoard[i][j] = ' ';
        }
    }
}

void drawPaddle()
{
    // Menghapus baris paddle terlebih dahulu
    for (int j = 0; j < WIDTH; j++)
    {
        gameBoard[HEIGHT - 1][j] = ' ';
    }
    // Menggambar paddle (panjang 5 karakter)
    for (int j = 0; j < 5; j++)
    {
        gameBoard[HEIGHT - 1][paddleX + j] = '=';
    }
}

void renderGame()
{
    system("cls"); // Membersihkan layar (Gunakan "clear" di Linux/Mac)
    for (int i = 0; i < HEIGHT; i++)
    {
        for (int j = 0; j < WIDTH; j++)
        {
            printf("%c", gameBoard[i][j]);
        }
        printf("\n");
    }
}

void movePaddle(char input)
{
    if (input == 'a' && paddleX > 0)
    {
        paddleX--; // Geser ke kiri
    }
    else if (input == 'd' && paddleX < WIDTH - 5)
    {
        paddleX++; // Geser ke kanan
    }
}

int main()
{
    char input;
    initGame();

    while (1)
    {
        drawPaddle(); // Perbarui posisi paddle
        renderGame(); // Tampilkan arena

        if (_kbhit())
        { // Cek jika ada input dari keyboard
            input = _getch();
            if (input == 'q')
                break; // Keluar dari permainan
            movePaddle(input);
        }
    }

    return 0;
}
