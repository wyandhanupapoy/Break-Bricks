#include <stdio.h>
#include "level.h"
#include "block.h"
#include <raylib.h>

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600
#define BLOCK_WIDTH 70
#define BLOCK_HEIGHT 30
#define PADDING 5
#define START_X 60  // Posisi awal dari sisi kiri
#define START_Y 50  // Posisi awal dari atas

Block blocks[BLOCK_ROWS][BLOCK_COLS];

void InitGameLevel(int level) {
    SetLevel(blocks, level);
}

int main() {
    InitGameLevel(1);

    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Breakout - Level Test");
    SetTargetFPS(60);

    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(BLACK);  // Sesuai dengan gambar referensi

        // Gambar blok dengan margin agar lebih rapih
        for (int i = 0; i < BLOCK_ROWS; i++) {
            for (int j = 0; j < BLOCK_COLS; j++) {
                if (blocks[i][j].active) {
                    int x = START_X + j * (BLOCK_WIDTH + PADDING);
                    int y = START_Y + i * (BLOCK_HEIGHT + PADDING);
                    DrawRectangle(x, y, BLOCK_WIDTH, BLOCK_HEIGHT, blocks[i][j].color);
                    DrawRectangleLines(x, y, BLOCK_WIDTH, BLOCK_HEIGHT, BLACK);
                }
            }
        }

        DrawText("Tekan ESC untuk keluar", 10, 10, 20, RAYWHITE);
        EndDrawing();
    }

    CloseWindow();
    return 0;
}
