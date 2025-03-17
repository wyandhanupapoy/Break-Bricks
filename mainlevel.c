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
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Breakout - Level Test");
    SetTargetFPS(60);

    InitGameLevel(1);  // Pastikan level diinisialisasi setelah window dibuat

    // Debugging: Cetak informasi blok
    printf("=== DEBUGGING BLOCKS ===\n");
    for (int i = 0; i < BLOCK_ROWS; i++) {
        for (int j = 0; j < BLOCK_COLS; j++) {
            printf("Blok[%d][%d] -> Active: %d, Color: (%d, %d, %d, %d), Durability: %d\n",
                   i, j, blocks[i][j].active, 
                   blocks[i][j].color.r, blocks[i][j].color.g, blocks[i][j].color.b, blocks[i][j].color.a,
                   blocks[i][j].durability);
        }
    }

    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(RAYWHITE);

        for (int i = 0; i < BLOCK_ROWS; i++) {
            for (int j = 0; j < BLOCK_COLS; j++) {
                if (blocks[i][j].active) { // Pastikan hanya menggambar blok aktif
                    DrawRectangle(j * 50 + 15, i * 30 + 70, 48, 28, blocks[i][j].color);
                    DrawRectangleLines(j * 50 + 15, i * 30 + 70, 48, 28, BLACK);
                }
            }
        }

        DrawText("Tekan ESC untuk keluar", 10, 10, 20, DARKGRAY);
        EndDrawing();
    }

    CloseWindow();
    return 0;
}
