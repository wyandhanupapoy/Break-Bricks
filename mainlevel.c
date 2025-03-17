#include <stdio.h>
#include "level.h"
#include "block.h"
#include <raylib.h>

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600

Block blocks[BLOCK_ROWS][BLOCK_COLS];  // Deklarasi array blok

void InitGameLevel(int level) {
    SetLevel(blocks, level);
}

int main() {
    InitGameLevel(1);  // Set Level Awal

    // Inisialisasi Raylib
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Breakout - Level Test");
    SetTargetFPS(60);

    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(RAYWHITE);

        // Debugging: Cetak blok ke terminal
        for (int i = 0; i < BLOCK_ROWS; i++) {
            for (int j = 0; j < BLOCK_COLS; j++) {
                DrawRectangle(j * 50, i * 30, 48, 28, GetColor(blocks[i][j].color));
            }
        }

        DrawText("Tekan ESC untuk keluar", 10, 10, 20, DARKGRAY);
        EndDrawing();
    }

    CloseWindow();
    return 0;
}
