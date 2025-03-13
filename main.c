#include "raylib.h"
#include "BOLA.h"

int main() {
    InitWindow(800, 600, "Breakout - Raylib");
    SetTargetFPS(60);
    
    Bola bola[ROWS][COLS];
    InitBola(bola);
    
    while (!WindowShouldClose()) {
        // Update bola
        UpdateBola(bola);
        
        BeginDrawing();
        ClearBackground(RAYWHITE);
        
        // Gambar bola
        DrawBola(bola);
        
        EndDrawing();
    }
    
    CloseWindow();
    return 0;
}
