// Nama : Muhammad Raihan Abubakar
// Nama fitur : paddle 
// Deskripsi : paddle berfungsi untuk memantulkan dan mengarahkan bola agar bisa menghancurkan block

#ifndef PADDLE_H
#define PADDLE_H

#include <raylib.h>

#define PADDLE_ROWS 1 
#define PADDLE_COLS 1 // jumlah baris dan kolom paddle 
#define PADDLE_WIDTH 100 // lebar paddle
#define PADDLE_HEIGHT 20 // tinggi paddle 
#define PADDLE_SPEED 8 // kecepatan paddle 

typedef struct {
    Rectangle rect; // posisi paddle 
    Vector2 speed; 
} Paddle;

void InitPaddles(Paddle paddles[PADDLE_ROWS][PADDLE_COLS]); // inisiasi paddle
void UpdatePaddles(Paddle paddles[PADDLE_ROWS][PADDLE_COLS]); // memperbarui posisi paddle berdasarkan input keyboard
void DrawPaddles(Paddle paddles[PADDLE_ROWS][PADDLE_COLS]); // menggambar paddle di layar

#endif // PADDLE_H
