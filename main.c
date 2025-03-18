#include "raylib.h"
#include "block.h"
#include "level.h"

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600
#define BALL_RADIUS 7
#define BALL_SPEED 4
#define PADDLE_WIDTH 100
#define PADDLE_HEIGHT 10
#define PADDLE_SPEED 6
#define MAX_LIVES 3

typedef struct {
    Vector2 position;
    Vector2 speed;
    float radius;
    bool active;
} Ball;

typedef struct {
    Rectangle rect;
    int speed;
} Paddle;

void ResetBall(Ball *ball) {
    ball->position = (Vector2){ SCREEN_WIDTH / 2, SCREEN_HEIGHT - 50 };
    ball->speed = (Vector2){ BALL_SPEED, -BALL_SPEED };
    ball->active = true;
}

void ResetPaddle(Paddle *paddle) {
    paddle->rect.x = SCREEN_WIDTH / 2 - PADDLE_WIDTH / 2;
    paddle->rect.y = SCREEN_HEIGHT - 30;
    paddle->rect.width = PADDLE_WIDTH;
    paddle->rect.height = PADDLE_HEIGHT;
    paddle->speed = PADDLE_SPEED;
}

int main() {
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Breakout Game");
    SetTargetFPS(60);

    Block blocks[BLOCK_ROWS][BLOCK_COLS];
    InitLevelBlocks(blocks);

    Ball ball;
    ResetBall(&ball);

    Paddle paddle;
    ResetPaddle(&paddle);

    int lives = MAX_LIVES;
    int score = 0;

    while (!WindowShouldClose()) {
        // Kontrol Paddle
        if (IsKeyDown(KEY_LEFT) && paddle.rect.x > 0) {
            paddle.rect.x -= paddle.speed;
        }
        if (IsKeyDown(KEY_RIGHT) && paddle.rect.x + PADDLE_WIDTH < SCREEN_WIDTH) {
            paddle.rect.x += paddle.speed;
        }

        // Update posisi bola
        if (ball.active) {
            ball.position.x += ball.speed.x;
            ball.position.y += ball.speed.y;

            // Pantulan dari dinding kiri dan kanan
            if (ball.position.x - BALL_RADIUS <= 0 || ball.position.x + BALL_RADIUS >= SCREEN_WIDTH) {
                ball.speed.x *= -1;
            }

            // Pantulan dari atas
            if (ball.position.y - BALL_RADIUS <= 0) {
                ball.speed.y *= -1;
            }

            // Pantulan dari paddle
            if (CheckCollisionCircleRec(ball.position, BALL_RADIUS, paddle.rect)) {
                ball.speed.y *= -1;
                ball.position.y = paddle.rect.y - BALL_RADIUS;
            }

            // Cek tabrakan dengan blok
            for (int i = 0; i < BLOCK_ROWS; i++) {
                for (int j = 0; j < BLOCK_COLS; j++) {
                    Block *block = &blocks[i][j];

                    if (block->active && CheckBallBlockCollision(ball.position, BALL_RADIUS, block->rect)) {
                        UpdateBlockState(block);
                        ball.speed.y *= -1;
                        score += 10;
                    }
                }
            }

            // Jika bola jatuh ke bawah
            if (ball.position.y + BALL_RADIUS > SCREEN_HEIGHT) {
                lives--;
                if (lives <= 0) {
                    ball.active = false;  // Game over
                } else {
                    ResetBall(&ball);  // Reset bola jika masih ada nyawa
                }
            }
        }

        // Gambar semua elemen di layar
        BeginDrawing();
        ClearBackground(RAYWHITE);

        DrawBlocks(blocks);

        // Gambar bola
        if (ball.active) {
            DrawCircleV(ball.position, BALL_RADIUS, RED);
        }

        // Gambar paddle
        DrawRectangleRec(paddle.rect, BLUE);

        // Tampilkan skor dan nyawa
        DrawText(TextFormat("Score: %d", score), 20, 20, 20, BLACK);
        DrawText(TextFormat("Lives: %d", lives), SCREEN_WIDTH - 100, 20, 20, BLACK);

        if (!ball.active && lives <= 0) {
            DrawText("GAME OVER!", SCREEN_WIDTH / 2 - 80, SCREEN_HEIGHT / 2, 30, RED);
        }

        EndDrawing();
    }

    CloseWindow();
    return 0;
}
