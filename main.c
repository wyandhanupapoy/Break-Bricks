<<<<<<< HEAD
<<<<<<< HEAD
=======
>>>>>>> 588526b9be4263d9e33322941397818ad2e2afc5
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
<<<<<<< HEAD
=======
>>>>>>> origin/blok
=======
>>>>>>> 588526b9be4263d9e33322941397818ad2e2afc5
