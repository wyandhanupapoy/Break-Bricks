#include <SDL2/SDL.h>
#include <stdio.h>

#define SCREEN_WIDTH  640
#define SCREEN_HEIGHT 480

#define PADDLE_WIDTH  100
#define PADDLE_HEIGHT 10
#define BALL_SIZE 10

#define ROWS 5
#define COLS 10
#define BLOCK_WIDTH  60
#define BLOCK_HEIGHT  20

typedef struct {
    int x, y, w, h;
    int active;
} Block;

Block blocks[ROWS][COLS];

void initBlocks() {
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            blocks[i][j].x = j * (BLOCK_WIDTH + 5) + 50;
            blocks[i][j].y = i * (BLOCK_HEIGHT + 5) + 50;
            blocks[i][j].w = BLOCK_WIDTH;
            blocks[i][j].h = BLOCK_HEIGHT;
            blocks[i][j].active = 1;
        }
    }
}

void drawBlocks(SDL_Renderer *renderer) {
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            if (blocks[i][j].active) {
                SDL_Rect rect = { blocks[i][j].x, blocks[i][j].y, blocks[i][j].w, blocks[i][j].h };
                SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
                SDL_RenderFillRect(renderer, &rect);
            }
        }
    }
}

void checkCollisionBall(float *ballX, float *ballY, float *ballVelX, float *ballVelY) {
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            if (blocks[i][j].active) {
                if (*ballX < blocks[i][j].x + blocks[i][j].w &&
                    *ballX + BALL_SIZE > blocks[i][j].x &&
                    *ballY < blocks[i][j].y + blocks[i][j].h &&
                    *ballY + BALL_SIZE > blocks[i][j].y) {
                    
                    blocks[i][j].active = 0;
                    *ballVelY = -*ballVelY;
                }
            }
        }
    }
}

int main() {
    SDL_Init(SDL_INIT_VIDEO);
    SDL_Window *window = SDL_CreateWindow("Breakout", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    int paddleX = SCREEN_WIDTH / 2 - PADDLE_WIDTH / 2;
    float ballX = SCREEN_WIDTH / 2, ballY = SCREEN_HEIGHT - 50;
    float ballVelX = 3, ballVelY = -3;
    
    int running = 1;
    SDL_Event event;
    
    initBlocks();

    while (running) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                running = 0;
            }
        }

        const Uint8 *keys = SDL_GetKeyboardState(NULL);
        if (keys[SDL_SCANCODE_LEFT] && paddleX > 0) {
            paddleX -= 5;
        }
        if (keys[SDL_SCANCODE_RIGHT] && paddleX < SCREEN_WIDTH - PADDLE_WIDTH) {
            paddleX += 5;
        }

        ballX += ballVelX;
        ballY += ballVelY;

        if (ballX <= 0 || ballX + BALL_SIZE >= SCREEN_WIDTH) {
            ballVelX = -ballVelX;
        }
        if (ballY <= 0) {
            ballVelY = -ballVelY;
        }
        if (ballY + BALL_SIZE >= SCREEN_HEIGHT) {
            ballX = SCREEN_WIDTH / 2;
            ballY = SCREEN_HEIGHT - 50;
            ballVelX = 3;
            ballVelY = -3;
        }

        if (ballX + BALL_SIZE > paddleX && ballX < paddleX + PADDLE_WIDTH && 
            ballY + BALL_SIZE > SCREEN_HEIGHT - 30) {
            ballVelY = -ballVelY;
        }

        checkCollisionBall(&ballX, &ballY, &ballVelX, &ballVelY);

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        drawBlocks(renderer);

        SDL_Rect paddle = { paddleX, SCREEN_HEIGHT - 20, PADDLE_WIDTH, PADDLE_HEIGHT };
        SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
        SDL_RenderFillRect(renderer, &paddle);

        SDL_Rect ball = { ballX, ballY, BALL_SIZE, BALL_SIZE };
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_RenderFillRect(renderer, &ball);

        SDL_RenderPresent(renderer);

        SDL_Delay(16);
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}
