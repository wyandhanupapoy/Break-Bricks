#include "mainmenu.h"
#include "sound.h"
#include "raylib.h"

// Variabel global
static MenuState currentMenu = MENU_MAIN;

static bool exitGame = false;
static bool startGame = false;
static bool soundOn = true;
static int selectedLevel = 0;

// Tombol utama
static Rectangle startBtn = {350, 300, 320, 50};
static Rectangle exitBtn = {350, 370, 320, 50};
static Rectangle soundBtn = {850, 600, 140, 40};

// Tombol level select
static Rectangle level1Btn = {350, 250, 300, 50};
static Rectangle level2Btn = {350, 320, 300, 50};
static Rectangle level3Btn = {350, 390, 300, 50};
static Rectangle backBtn = {20, 20, 100, 40};

// Inisialisasi
void InitMainMenu()
{
    currentMenu = MENU_MAIN;
    exitGame = false;
    startGame = false;
    selectedLevel = 0;
    soundOn = true;
}

void UpdateMainMenu()
{
    Vector2 mousePoint = GetMousePosition();

    if (currentMenu == MENU_MAIN)
    {
        if (CheckCollisionPointRec(mousePoint, startBtn))
        {
            if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
            {
                PlayButtonClick(); // Tambahkan ini
                currentMenu = MENU_LEVEL_SELECT;
            }
        }

        if (CheckCollisionPointRec(mousePoint, exitBtn))
        {
            if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
            {
                exitGame = true;
            }
        }

        if (CheckCollisionPointRec(mousePoint, soundBtn))
        {
            if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
            {
                ToggleSound();
            }
        }
    }
    else if (currentMenu == MENU_LEVEL_SELECT)
    {
        if (CheckCollisionPointRec(mousePoint, level1Btn))
        {
            if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
            {
                selectedLevel = 1;
                startGame = true;
            }
        }

        if (CheckCollisionPointRec(mousePoint, level2Btn))
        {
            if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
            {
                selectedLevel = 2;
                startGame = true;
            }
        }

        if (CheckCollisionPointRec(mousePoint, level3Btn))
        {
            if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
            {
                selectedLevel = 3;
                startGame = true;
            }
        }

        // Tombol BACK pakai mouse
        if (CheckCollisionPointRec(mousePoint, backBtn))
        {
            if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
            {
                currentMenu = MENU_MAIN;
            }
        }

        // Tombol BACK pakai keyboard
        if (IsKeyPressed(KEY_BACKSPACE))
        {
            currentMenu = MENU_MAIN;
        }
    }
}

void DrawMainMenu()
{
    ClearBackground((Color){30, 0, 60, 255});
    Vector2 mousePoint = GetMousePosition();

    if (currentMenu == MENU_MAIN)
    {
        DrawText("BREAK BRICKS", 320, 150, 50, WHITE);

        Color startColor = CheckCollisionPointRec(mousePoint, startBtn) ? ((Color){60, 125, 198, 255}) : LIGHTGRAY;
        DrawRectangleRec(startBtn, startColor);
        DrawText("START GAME", startBtn.x + 60, startBtn.y + 10, 30, BLACK);

        Color exitColor = CheckCollisionPointRec(mousePoint, exitBtn) ?  ((Color){198, 60, 60, 255}) :LIGHTGRAY;
        DrawRectangleRec(exitBtn, exitColor);
        DrawText("EXIT GAME", exitBtn.x + 80, exitBtn.y + 10, 30, BLACK);

        Color soundColor = CheckCollisionPointRec(mousePoint, soundBtn) ? YELLOW : GRAY;
        DrawRectangleRec(soundBtn, soundColor);
        DrawText(soundOn ? "SOUND ON" : "SOUND OFF", soundBtn.x + 10, soundBtn.y + 10, 20, BLACK);
    }
    else if (currentMenu == MENU_LEVEL_SELECT)
    {
        DrawText("SELECT LEVEL", 350, 150, 40, WHITE);

        Color level1Color = CheckCollisionPointRec(mousePoint, level1Btn) ? YELLOW : LIGHTGRAY;
        DrawRectangleRec(level1Btn, level1Color);
        DrawText("LEVEL 1", level1Btn.x + 95, level1Btn.y + 10, 30, BLACK);

        Color level2Color = CheckCollisionPointRec(mousePoint, level2Btn) ? YELLOW : LIGHTGRAY;
        DrawRectangleRec(level2Btn, level2Color);
        DrawText("LEVEL 2", level2Btn.x + 95, level2Btn.y + 10, 30, BLACK);

        Color level3Color = CheckCollisionPointRec(mousePoint, level3Btn) ? YELLOW : LIGHTGRAY;
        DrawRectangleRec(level3Btn, level3Color);
        DrawText("LEVEL 3", level3Btn.x + 95, level3Btn.y + 10, 30, BLACK);

        Color backColor = CheckCollisionPointRec(mousePoint, backBtn) ? RED : LIGHTGRAY;
        DrawRectangleRec(backBtn, backColor);
        DrawText("BACK", backBtn.x + 20, backBtn.y + 10, 20, BLACK);
    }
}

bool IsExitGame()
{
    return exitGame;
}

bool IsStartGame()
{
    return startGame;
}

int GetSelectedLevel()
{
    return selectedLevel;
}

void ToggleSound()
{
    soundOn = !soundOn;
}

bool IsSoundOn()
{
    return soundOn;
}

void SetStartGame(bool value)
{
    startGame = value;
}
