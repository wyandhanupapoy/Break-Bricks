#include "layout.h"
#include "raylib.h"

static int screenWidth = DEFAULT_SCREEN_WIDTH; // Variabel untuk menyimpan lebar layar
static int screenHeight = DEFAULT_SCREEN_HEIGHT; // Variabel untuk menyimpan tinggi layar

void SetScreenSize(int width, int height) {
    screenWidth = width;
    screenHeight = height;
    SetWindowSize(screenWidth, screenHeight); // Mengatur ukuran jendela
}

void DrawGameLayout(Block blocks[][BLOCK_COLS], Paddle paddles[][PADDLE_COLS], Bola bola[][BOLA_COLS], Stopwatch sw[][STOPWATCH_COLS], Nyawa nyawa[][NYAWA_KOLOM]) {
    ClearBackground(RAYWHITE);
    
    // Panel kanan (warna abu-abu muda)
    DrawRectangle(screenWidth - PANEL_WIDTH, 0, PANEL_WIDTH, screenHeight, LIGHTGRAY);
    
    // Gambar blok, paddle, dan bola di area utama
    DrawBlocks(blocks);
    DrawPaddles(paddles);
    DrawBola(bola);
    
    // Posisi awal untuk UI di panel kanan
    int uiX = screenWidth - PANEL_WIDTH + 20;  // Geser sedikit dari tepi
    int nyawaY = 20;  // Nyawa di bagian atas
    int stopwatchY = nyawaY + 40;  // Stopwatch di bawah nyawa dengan jarak 40px

    // Gambar nyawa di pojok kanan atas
    DrawNyawa(nyawa, uiX, nyawaY);

    // Gambar stopwatch di bawah nyawa
    DrawStopwatch(sw, uiX, stopwatchY);
}