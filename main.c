// main.c - Program utama yang menggabungkan semua komponen
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h>
#include <windows.h>

// Include semua file header
#include "definisi.h"
#include "tampilan.h"
#include "paddle.h"
#include "bola.h"
#include "blok.h"
#include "game.h"

int main() {
    // Setup konsol
    system("title Breakout Game");
    system("mode con cols=65 lines=30");
    
    // Inisialisasi random seed
    srand(time(NULL));
    
    // Mulai permainan
    mainkanGame();
    
    return 0;
}