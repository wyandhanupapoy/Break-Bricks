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

#endif // GAME_STATE_H
