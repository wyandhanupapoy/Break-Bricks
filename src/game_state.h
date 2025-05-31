/*
Nama Pembuat:   Wyandhanu Maulidan Nugraha
Nama Fitur:     define game state
Deskripsi:      Fitur ini berisi definisi game state yang digunakan dalam game **Break Bricks**
*/

#ifndef GAME_STATE_H
#define GAME_STATE_H

typedef enum {
    GAME_MENU,
    GAME_START,
    GAME_PLAY,
    GAME_OVER,
    GAME_WIN
} GameState;

// Screen size
#define SCREEN_WIDTH 1000
#define SCREEN_HEIGHT 650

#define GAME_PLAY_AREA_WIDTH 830
#define GAME_PLAY_AREA_HEIGHT 600

#define MAX_PLAYERS 1000

#endif // GAME_STATE_H
