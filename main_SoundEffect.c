#include "soundeffect.h"
#include <raylib.h>

#define SCREEN_WIDTH 1000
#define SCREEN_HEIGHT 650

int main() {
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Test Sound Effects");
    SetTargetFPS(60);

    Sound soundEffects[SOUND_ROWS][SOUND_COLS];
    InitSoundEffects(soundEffects);

    while (!WindowShouldClose()) {
        if (IsKeyPressed(KEY_ONE)) PlaySoundEffect(soundEffects, SOUND_BACKSOUND);
        if (IsKeyPressed(KEY_TWO)) PlaySoundEffect(soundEffects, SOUND_BUTTON);
        if (IsKeyPressed(KEY_THREE)) PlaySoundEffect(soundEffects, SOUND_BLOCK_BREAK);
        if (IsKeyPressed(KEY_FOUR)) PlaySoundEffect(soundEffects, SOUND_LOSE);
        if (IsKeyPressed(KEY_FIVE)) PlaySoundEffect(soundEffects, SOUND_BOUNCE);
        if (IsKeyPressed(KEY_SIX)) PlaySoundEffect(soundEffects, SOUND_WIN);

        BeginDrawing();
        ClearBackground(BLACK);
        DrawText("Press 1: Play Backsound", 20, 20, 20, WHITE);
        DrawText("Press 2: Play Button Click", 20, 50, 20, WHITE);
        DrawText("Press 3: Play Block Break", 20, 80, 20, WHITE);
        DrawText("Press 4: Play Lose Sound", 20, 110, 20, WHITE);
        DrawText("Press 5: Play Bounce Sound", 20, 140, 20, WHITE);
        DrawText("Press 6: Play Win Sound", 20, 170, 20, WHITE);
        EndDrawing();
    }

    UnloadSoundEffects(soundEffects);
    CloseWindow();
    return 0;
}
