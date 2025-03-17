#include "bola.h"
#include "block.h"
#include "stopwatch.h"
#include "nyawa.h"

#define SCREEN_WIDTH 830
#define SCREEN_HEIGHT 600
#define GAME_AREA_WIDTH 600  // Batas area permainan

void InitBola(Bola bola[BOLA_ROWS][BOLA_COLS]) {
    for (int i = 0; i < BOLA_ROWS; i++) {
        bola[i][0].position = (Vector2){GAME_AREA_WIDTH / 2, SCREEN_HEIGHT / 2};
        bola[i][0].speed = (Vector2){5, -5}; // Kecepatan awal
        bola[i][0].radius = 10;
        bola[i][0].color = RED;
        bola[i][0].active = true;
    }
}

void UpdateBola(Bola bola[BOLA_ROWS][BOLA_COLS], Paddle paddles[PADDLE_ROWS][PADDLE_COLS], 
                Block blocks[BLOCK_ROWS][BLOCK_COLS], GameState *state, 
                Nyawa nyawa[NYAWA_BARIS][NYAWA_KOLOM], Stopwatch stopwatch[STOPWATCH_ROWS][STOPWATCH_COLS]) {
    for (int i = 0; i < BOLA_ROWS; i++) {
        for (int j = 0; j < BOLA_COLS; j++) {
            bola[i][j].position.x += bola[i][j].speed.x;
            bola[i][j].position.y += bola[i][j].speed.y;

            // Pantulan dari dinding kiri dan kanan
            if (bola[i][j].position.x <= 0 || bola[i][j].position.x >= GAME_AREA_WIDTH) {
                bola[i][j].speed.x *= -1;
            }

            // Pantulan dari langit-langit
            if (bola[i][j].position.y <= 0) {
                bola[i][j].speed.y *= -1;
            }

            // Jika bola jatuh ke bawah, kurangi nyawa
            if (bola[i][j].position.y > SCREEN_HEIGHT) {
                KurangiNyawa(nyawa);
                
                // Jika nyawa habis, ubah state jadi GAME_OVER
                if (!AnyLivesLeft(nyawa)) {
                    *state = GAME_OVER;
                } else {
                    // Reset bola ke posisi awal
                    bola[i][j].position.x = GAME_AREA_WIDTH / 2;
                    bola[i][j].position.y = SCREEN_HEIGHT - 50;
                    bola[i][j].speed.x = 3;
                    bola[i][j].speed.y = -3;
                }
            }
        }
    }
}

void DrawBola(Bola bola[BOLA_ROWS][BOLA_COLS]) {
    for (int i = 0; i < BOLA_ROWS; i++) {
        if (bola[i][0].active) {
            DrawCircleV(bola[i][0].position, bola[i][0].radius, bola[i][0].color);
        }
    }
}

void ResetBola(Bola bola[BOLA_ROWS][BOLA_COLS]) {
    for (int i = 0; i < BOLA_ROWS; i++) {
        bola[i][0].position = (Vector2){GAME_AREA_WIDTH / 2, SCREEN_HEIGHT / 2};
        bola[i][0].speed = (Vector2){5, -5}; // Kecepatan awal bola
        bola[i][0].active = true;
    }
}
