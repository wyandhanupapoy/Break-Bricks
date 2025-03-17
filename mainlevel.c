#include "raylib.h"
#include "level.h"

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600

int main() {
    // Inisialisasi window
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Breakout - Level System");
    SetTargetFPS(60);

    // Inisialisasi blok
    Block blocks[BLOCK_ROWS][BLOCK_COLS];
    InitLevelBlocks(blocks);

    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(RAYWHITE);

        // Gambar blok
        DrawBlocks(blocks);

        EndDrawing();
    }

    CloseWindow();
    return 0;
}
