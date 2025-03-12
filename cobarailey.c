#include <raylib.h>

int main() {
    InitWindow(800, 600, "Hello, Raylib!");
    SetTargetFPS(60);

    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(RAYWHITE);
        DrawText("raylib anda tidak berjalan!", 300, 280, 20, BLACK);
        EndDrawing();
    }

    CloseWindow();
    return 0;
}