<<<<<<< HEAD
#include "raylib.h"

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600

int main(void) {
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Raylib Window");
    SetTargetFPS(60);
    
    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(RAYWHITE);
        EndDrawing();
    }
    
    CloseWindow();
    return 0;
}
=======
>>>>>>> origin/blok
