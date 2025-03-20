#include <stdio.h>
#include "level.h"
#include "block.h"
#include <raylib.h>

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600
#define BLOCK_WIDTH 75
#define BLOCK_HEIGHT 25
#define PADDING 5
#define START_X 60  // Posisi awal dari sisi kiri
#define START_Y 50  // Posisi awal dari atas

Block blocks[BLOCK_ROWS][BLOCK_COLS];

// Variabel untuk bola
Vector2 ballPosition;
Vector2 ballSpeed = {4, -4};  // Kecepatan awal bola
float ballRadius = 8;

void InitGameLevel(int level) {
    SetLevel(blocks, level);
    ballPosition = (Vector2){SCREEN_WIDTH / 2, SCREEN_HEIGHT - 50}; // Posisi awal bola
}

int main() {
    InitGameLevel(1);

    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Breakout - Level Test");
    SetTargetFPS(60);

    while (!WindowShouldClose()) {
        // Pergerakan bola
        ballPosition.x += ballSpeed.x;
        ballPosition.y += ballSpeed.y;

        // Pantulan dari dinding kiri & kanan
        if (ballPosition.x - ballRadius <= 0 || ballPosition.x + ballRadius >= SCREEN_WIDTH)
            ballSpeed.x *= -1;

        // Pantulan dari atas
        if (ballPosition.y - ballRadius <= 0)
            ballSpeed.y *= -1;

        // Cek kolisi bola dengan blok
        for (int i = 0; i < BLOCK_ROWS; i++) {
            for (int j = 0; j < BLOCK_COLS; j++) {
                if (blocks[i][j].active && CheckBallBlockCollision(ballPosition, ballRadius, blocks[i][j].rect)) {
                    UpdateBlockState(&blocks[i][j]); // Kurangi durability blok
                    ballSpeed.y *= -1; // Pantulkan bola ke arah berlawanan
                }
            }
        }

        BeginDrawing();
        ClearBackground(BLACK);  // Sesuai dengan gambar referensi

        // Gambar blok dengan margin agar lebih rapi
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

        // Gambar bola
        DrawCircleV(ballPosition, ballRadius, RAYWHITE);

        DrawText("Tekan ESC untuk keluar", 10, 10, 20, RAYWHITE);
        EndDrawing();
    }

    CloseWindow();
    return 0;
}