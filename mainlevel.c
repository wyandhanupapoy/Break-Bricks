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
                printf("Block[%d][%d]: Warna = %d, Durability = %d\n",
                       i, j, blocks[i][j].color, blocks[i][j].durability);
            }
        }

        DrawText("Tekan ESC untuk keluar", 10, 10, 20, DARKGRAY);
        EndDrawing();
    }

    CloseWindow();
    return 0;
}
