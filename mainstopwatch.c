#include "raylib.h"
#include "stopwatch.h"

int main() {
    InitWindow(800, 600, "Stopwatch in Raylib");
    SetTargetFPS(60);

    Stopwatch sw[ROWS][COLS]; // Deklarasi stopwatch sebagai array 2D
    InitStopwatch(sw);        // Inisialisasi stopwatch

    while (!WindowShouldClose()) {
        UpdateStopwatch(sw);  // Update stopwatch setiap frame

        BeginDrawing();
        ClearBackground(RAYWHITE);

        DrawText("Stopwatch Example", 280, 20, 20, BLACK);

        DrawStopwatch(sw); // Gambar stopwatch di tengah layar

        EndDrawing();
    }

    CloseWindow();
    return 0;
}
