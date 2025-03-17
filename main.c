#include "raylib.h"
#include "bola.h"

int main() {
    const int screenWidth = 800;
    const int screenHeight = 600;

    InitWindow(screenWidth, screenHeight, "Block Bricker - Bola");

    Bola bola;
    InitBola(&bola, (Vector2){screenWidth / 2, screenHeight - 50}, (Vector2){4, -4}, 10);

    SetTargetFPS(60);

    while (!WindowShouldClose()) {
        UpdateBola(&bola, screenWidth, screenHeight);

        BeginDrawing();
        ClearBackground(RAYWHITE);
        DrawBola(&bola);
        EndDrawing();
    }

    CloseWindow();
    return 0;
}
