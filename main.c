#include "paddle.h"
#include "block.h"
#include "BOLA.h"
#include "nyawa.h"

#include <stdio.h>
#include <raylib.h>

// Ukuran layar
#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600

int main() {
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Breakout Game");
    SetTargetFPS(60);

    // Inisialisasi paddle
    Paddle paddles[PADDLE_ROWS][PADDLE_COLS];
    InitPaddles(paddles);

    // Inisialisasi blok
    Block blocks[BLOCK_ROWS][BLOCK_COLS];
    InitBlocks(blocks);

    // Inisialisasi bola
    Bola bola[BOLA_ROWS][BOLA_COLS];
    InitBola(bola);

    // Inisialisasi nyawa
    Nyawa nyawa[NYAWA_BARIS][NYAWA_KOLOM];
    InitNyawa(nyawa, 3);  // Mulai dengan 3 nyawa

    GameState gameState = GAME_START;
    bool isPaused = false;

    while (!WindowShouldClose()) {
        // Pause Game
        if (IsKeyPressed(KEY_P)) isPaused = !isPaused;

        if (!isPaused) {
            switch (gameState) {
                case GAME_START:
                    UpdatePaddles(paddles);
                    UpdateBola(bola, paddles, &gameState);
                    
                    if (IsKeyPressed(KEY_SPACE)) {
                        gameState = GAME_PLAY;
                    }
                    break;

                case GAME_PLAY:
                    UpdatePaddles(paddles);
                    UpdateBola(bola, paddles, &gameState);

                    // Cek tabrakan bola dengan blok
                    for (int ballRow = 0; ballRow < BOLA_ROWS; ballRow++) {
                        for (int ballCol = 0; ballCol < BOLA_COLS; ballCol++) {
                            if (!bola[ballRow][ballCol].active) continue;

                            for (int blockRow = 0; blockRow < BLOCK_ROWS; blockRow++) {
                                for (int blockCol = 0; blockCol < BLOCK_COLS; blockCol++) {
                                    if (blocks[blockRow][blockCol].active && 
                                        CheckBallBlockCollision(
                                            bola[ballRow][ballCol].position,
                                            bola[ballRow][ballCol].radius,
                                            blocks[blockRow][blockCol].rect)) 
                                    {
                                        blocks[blockRow][blockCol].active = false;
                                        bola[ballRow][ballCol].speed.y *= -1;

                                        if (AllBlocksDestroyed(blocks)) {
                                            gameState = GAME_WIN;
                                        }
                                        break;
                                    }
                                }
                            }

                            // Jika bola jatuh ke bawah layar
                            if (bola[ballRow][ballCol].position.y + bola[ballRow][ballCol].radius > SCREEN_HEIGHT) {
                                KurangiNyawa(nyawa);
                                if (!AnyLivesLeft(nyawa)) {
                                    gameState = GAME_OVER;
                                } else {
                                    ResetBola(bola);
                                    gameState = GAME_START;
                                }
                            }
                        }
                    }
                    break;

                case GAME_OVER:
                    if (IsKeyPressed(KEY_R)) {
                        InitBlocks(blocks);
                        InitNyawa(nyawa, 3);
                        InitBola(bola);
                        gameState = GAME_START;
                    }
                    break;

                case GAME_WIN:
                    if (IsKeyPressed(KEY_R)) {
                        InitBlocks(blocks);
                        InitBola(bola);
                        gameState = GAME_START;
                    }
                    break;
            }
        }

        // Drawing
        BeginDrawing();
        ClearBackground(RAYWHITE);

        DrawPaddles(paddles);
        DrawBlocks(blocks);
        DrawBola(bola);
        DrawNyawa(nyawa);

        switch (gameState) {
            case GAME_START:
                DrawText("PRESS SPACE TO START", SCREEN_WIDTH / 2 - MeasureText("PRESS SPACE TO START", 30) / 2, SCREEN_HEIGHT / 2, 30, GRAY);
                break;
            case GAME_OVER:
                DrawText("GAME OVER", SCREEN_WIDTH / 2 - MeasureText("GAME OVER", 40) / 2, SCREEN_HEIGHT / 2 - 40, 40, RED);
                DrawText("PRESS R TO RESTART", SCREEN_WIDTH / 2 - MeasureText("PRESS R TO RESTART", 20) / 2, SCREEN_HEIGHT / 2 + 20, 20, DARKGRAY);
                break;
            case GAME_WIN:
                DrawText("YOU WIN!", SCREEN_WIDTH / 2 - MeasureText("YOU WIN!", 40) / 2, SCREEN_HEIGHT / 2 - 40, 40, GREEN);
                DrawText("PRESS R TO RESTART", SCREEN_WIDTH / 2 - MeasureText("PRESS R TO RESTART", 20) / 2, SCREEN_HEIGHT / 2 + 20, 20, DARKGRAY);
                break;
        }

        if (isPaused) {
            DrawRectangle(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, Fade(BLACK, 0.7f));
            DrawText("GAME PAUSED", SCREEN_WIDTH / 2 - MeasureText("GAME PAUSED", 40) / 2, SCREEN_HEIGHT / 2 - 40, 40, WHITE);
            DrawText("PRESS P TO CONTINUE", SCREEN_WIDTH / 2 - MeasureText("PRESS P TO CONTINUE", 20) / 2, SCREEN_HEIGHT / 2 + 20, 20, WHITE);
        }

        EndDrawing();
    }

    CloseWindow();
    return 0;
}