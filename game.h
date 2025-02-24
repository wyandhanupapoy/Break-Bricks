//game.h
#ifndef GAME_H
#define GAME_H

// Fungsi deklarasi
void setup();
void drraw();
void input();
void logic();
void gameOver();
void restartGame();

// Bola dan Paddle
int ballX, ballY;
int ballDirX, ballDirY;
int paddleX, paddleWidth;
int score;

// Block
int block[5][5];

#endif