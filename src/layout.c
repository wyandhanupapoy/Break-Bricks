#include "layout.h"
#include "raylib.h"
#include <stdio.h>

void DrawPauseScreen()
{
    DrawRectangle(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, Fade(BLACK, 0.5f));
    DrawText("PAUSED", 400, 300, 40, WHITE);
    DrawText("Press P to resume", 390, 350, 20, WHITE);
}

void DrawGameOverScreen()
{
    ClearBackground(RAYWHITE);
    DrawRectangle(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, WHITE);
    DrawText("GAME OVER", 370, 300, 40, RED);
    DrawText("Returning to menu...", 400, 350, 20, DARKGRAY);
}

void DrawWinScreen()
{
    ClearBackground(RAYWHITE);
    DrawRectangle(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, WHITE);
    DrawText("YOU WIN!", 370, 300, 40, GREEN);
    DrawText("Returning to menu...", 370, 350, 20, DARKGRAY);
}

void DrawControlInfo()
{
    DrawRectangle(0, 620, 835, 30, LIGHTGRAY);
    DrawText("<- -> Move   |   P - Pause   |   F - Fullscreen   |   Esc - Exit   |   M - Mute", 15, 625, 20, BLACK);
}
