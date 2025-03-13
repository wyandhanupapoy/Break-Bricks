#include "raylib.h"
#include "BOLA.h"

int main() {
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Break Bricks - Bola");
    SetTargetFPS(60);
    
    Bola bola[BOLA_ROWS][BOLA_COLS];
    InitBola(bola);
    
    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(RAYWHITE);
        
        UpdateBola(bola);
        DrawBola(bola);
        
        EndDrawing();
    }
    
    CloseWindow();
    return 0;
}