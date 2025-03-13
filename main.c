#include "raylib.h"
#include "skor.h"

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600

int main() {
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Break Bricks - Skor");
    SetTargetFPS(60);
    
    Skor skor[MAX_PLAYERS];
    InitSkor(skor);
    
    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(BLACK);
        
        // Menampilkan skor di layar
        DrawSkor(skor);
        
        EndDrawing();
    }
    
    CloseWindow();
    return 0;
}