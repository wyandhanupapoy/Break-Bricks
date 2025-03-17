#include <stdio.h>  // Pastikan ini ada
#include "raylib.h"
#include "block.h"
#include "paddle.h"
#include "bola.h"
#include "layout.h"
#include "stopwatch.h"
#include "nyawa.h"  

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600

int main() {
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Breakout Game");
    SetTargetFPS(60);

    Block blocks[BLOCK_ROWS][BLOCK_COLS];
    Paddle paddles[PADDLE_ROWS][PADDLE_COLS];
    Bola bola[BOLA_ROWS][BOLA_COLS];
    Stopwatch stopwatch[STOPWATCH_ROWS][STOPWATCH_COLS];
    Nyawa nyawa[NYAWA_BARIS][NYAWA_KOLOM];

    GameState state = GAME_PLAY;

    InitBlocks(blocks);
    InitPaddles(paddles);
    InitBola(bola);
    InitStopwatch(stopwatch);
    InitNyawa(nyawa, NYAWA_KOLOM); // Mulai dengan jumlah nyawa penuh

    printf("Game mulai...\n");
    fflush(stdout);

    while (!WindowShouldClose()) {
        if (state == GAME_PLAY) {
            UpdatePaddles(paddles);
            UpdateBola(bola, paddles, blocks, &state, nyawa, stopwatch);
            UpdateStopwatch(stopwatch);

            // Cek apakah nyawa habis
            if (!AnyLivesLeft(nyawa)) {
                state = GAME_OVER;
            }
        }

        BeginDrawing();
        ClearBackground(RAYWHITE);

        if (state == GAME_PLAY) {
            DrawGameLayout(blocks, paddles, bola, stopwatch, nyawa);
        } else if (state == GAME_OVER) {
            DrawText("Game Over", SCREEN_WIDTH / 2 - 50, SCREEN_HEIGHT / 2, 30, RED);
            DrawText("Tekan ESC untuk keluar", SCREEN_WIDTH / 2 - 100, SCREEN_HEIGHT / 2 + 40, 20, DARKGRAY);
        }

        EndDrawing();

        if (state == GAME_OVER && IsKeyPressed(KEY_ESCAPE)) {
            break;  // Keluar dari loop jika pemain menekan ESC
        }
    }

    CloseWindow();
    return 0;
}
