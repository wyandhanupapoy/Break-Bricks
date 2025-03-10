#ifndef BLOCK_BRICKER_H
#define BLOCK_BRICKER_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// Struktur untuk bola
typedef struct {
    float x, y;       // Posisi bola
    float dx, dy;     // Kecepatan bola
    float radius;     // Ukuran bola
} Ball;

// Struktur untuk paddle
typedef struct {
    float x, width;   // Posisi dan lebar paddle
} Paddle;

// Struktur untuk blok
typedef struct {
    float x, y;       // Posisi blok
    float width, height; // Ukuran blok
    bool active;      // Status blok (masih ada atau sudah hancur)
} Block;

// Konstanta ukuran layar
#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600

// Fungsi untuk menginisialisasi bola
void initBall(Ball *ball);

// Fungsi untuk memperbarui posisi bola
void updateBall(Ball *ball, Paddle *paddle, Block blocks[], int blockCount);

// Fungsi untuk mendeteksi tabrakan bola dengan blok
bool checkCollision(Ball *ball, Block *block);

// Fungsi untuk mendeteksi tabrakan bola dengan paddle
void checkPaddleCollision(Ball *ball, Paddle *paddle);

// Fungsi untuk menggambar objek (bisa diimplementasikan di file .c)
void drawBall(Ball *ball);
void drawPaddle(Paddle *paddle);
void drawBlocks(Block blocks[], int blockCount);

#endif // BLOCK_BRICKER_H
