@echo off
gcc -o breakout.exe main.c paddle.c block.c BOLA.c nyawa.c stopwatch.c skor.c leaderboard.c -lraylib -lm -lpthread -lwinmm
pause