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
    Ball ball;
    Paddle paddle;
    int lives = MAX_LIVES;
    int score = 0;
    int level = 1;
    bool levelSelected = false;

    while (!levelSelected) {
        BeginDrawing();
        ClearBackground(RAYWHITE);
        DrawText("Press 1, 2, or 3 to Select Level", SCREEN_WIDTH / 2 - 150, SCREEN_HEIGHT / 2, 20, BLACK);
        EndDrawing();

        if (IsKeyPressed(KEY_ONE)) {
            level = 1;
            levelSelected = true;
        } else if (IsKeyPressed(KEY_TWO)) {
            level = 2;
            levelSelected = true;
        } else if (IsKeyPressed(KEY_THREE)) {
            level = 3;
            levelSelected = true;
        }
    }

    SetLevel(blocks, level);
    ResetBall(&ball);
    ResetPaddle(&paddle);

    while (!WindowShouldClose()) {
        if (IsKeyDown(KEY_LEFT) && paddle.rect.x > 0) {
            paddle.rect.x -= paddle.speed;
        }
        if (IsKeyDown(KEY_RIGHT) && paddle.rect.x + PADDLE_WIDTH < SCREEN_WIDTH) {
            paddle.rect.x += paddle.speed;
        }

        if (ball.active) {
            ball.position.x += ball.speed.x;
            ball.position.y += ball.speed.y;

            if (ball.position.x - BALL_RADIUS <= 0 || ball.position.x + BALL_RADIUS >= SCREEN_WIDTH) {
                ball.speed.x *= -1;
            }

            if (ball.position.y - BALL_RADIUS <= 0) {
                ball.speed.y *= -1;
            }

            if (CheckCollisionCircleRec(ball.position, BALL_RADIUS, paddle.rect)) {
                ball.speed.y *= -1;
                ball.position.y = paddle.rect.y - BALL_RADIUS;
            }

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

            if (ball.position.y + BALL_RADIUS > SCREEN_HEIGHT) {
                lives--;
                if (lives <= 0) {
                    ball.active = false;
                } else {
                    ResetBall(&ball);
                }
            }
        }

        BeginDrawing();
        ClearBackground(RAYWHITE);
        DrawBlocks(blocks);
        
        if (ball.active) {
            DrawCircleV(ball.position, BALL_RADIUS, RED);
        }
        DrawRectangleRec(paddle.rect, BLUE);
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