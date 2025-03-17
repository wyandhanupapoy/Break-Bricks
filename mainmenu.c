#include "raylib.h"
#include <stdio.h>
#include <stdbool.h>

// State Enum
typedef enum
{
    MENU_MAIN,
    MENU_LEVEL
} MenuState;

// Variables
static int selectedLevel = 0;
static int selectedOption = 0;
static float highlightAlpha = 0.0f;
static bool exitGame = false;
static bool startGame = false;
static MenuState currentMenu = MENU_MAIN;

// Rectangles for main menu
Rectangle startRect = {350, 300, 300, 40};
Rectangle exitRect = {350, 350, 300, 40};

// Dummy sound functions
Sound navigateSound;
Sound selectSound;

// Function declarations
void InitMainMenu(void);
void UpdateMainMenu(void);
void DrawMainMenu(void);
void UpdateLevelMenu(void);
void DrawLevelMenu(void);
void StartLevel(int level);
bool IsExitGame(void) { return exitGame; }
bool IsStartGame(void) { return startGame; }

// Initialize Main Menu
void InitMainMenu(void)
{
    selectedOption = 0;
    highlightAlpha = 0.0f;
    currentMenu = MENU_MAIN;
    exitGame = false;
    startGame = false;
}

// Update Main Menu
void UpdateMainMenu(void)
{
    if (currentMenu == MENU_MAIN)
    {
        static int lastSelectedOption = selectedOption;

        if (IsKeyPressed(KEY_DOWN))
        {
            selectedOption++;
            if (selectedOption > 1)
                selectedOption = 0;
            if (selectedOption != lastSelectedOption)
                PlaySound(navigateSound);
        }

        if (IsKeyPressed(KEY_UP))
        {
            selectedOption--;
            if (selectedOption < 0)
                selectedOption = 1;
            if (selectedOption != lastSelectedOption)
                PlaySound(navigateSound);
        }

        lastSelectedOption = selectedOption;

        Vector2 mousePoint = GetMousePosition();

        if (CheckCollisionPointRec(mousePoint, startRect))
        {
            if (selectedOption != 0)
                PlaySound(navigateSound);
            selectedOption = 0;

            if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
            {
                currentMenu = MENU_LEVEL;
                PlaySound(selectSound);
                selectedOption = 0;
            }
        }

        if (CheckCollisionPointRec(mousePoint, exitRect))
        {
            if (selectedOption != 1)
                PlaySound(navigateSound);
            selectedOption = 1;

            if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
            {
                exitGame = true;
                PlaySound(selectSound);
            }
        }

        if (IsKeyPressed(KEY_ENTER))
        {
            if (selectedOption == 0)
            {
                currentMenu = MENU_LEVEL;
                PlaySound(selectSound);
                selectedOption = 0;
            }
            else if (selectedOption == 1)
            {
                exitGame = true;
                PlaySound(selectSound);
            }
        }

        highlightAlpha += (selectedOption >= 0 ? 0.1f : -0.1f);
        if (highlightAlpha > 0.5f)
            highlightAlpha = 0.5f;
        if (highlightAlpha < 0.0f)
            highlightAlpha = 0.0f;
    }
    else if (currentMenu == MENU_LEVEL)
    {
        UpdateLevelMenu();
    }
}

// Draw Main Menu
void DrawMainMenu(void)
{
    ClearBackground(WHITE);

    if (currentMenu == MENU_MAIN)
    {
        int x = 300;
        int y = 150;
        int fontSize = 60;

        DrawTextEx(GetFontDefault(), "B", (Vector2){x, y}, fontSize, 2, (Color){231, 76, 60, 255});
        DrawTextEx(GetFontDefault(), "R", (Vector2){x + 35, y}, fontSize, 2, (Color){241, 196, 15, 255});
        DrawTextEx(GetFontDefault(), "E", (Vector2){x + 70, y}, fontSize, 2, (Color){46, 204, 113, 255});
        DrawTextEx(GetFontDefault(), "A", (Vector2){x + 105, y}, fontSize, 2, (Color){52, 152, 219, 255});
        DrawTextEx(GetFontDefault(), "K", (Vector2){x + 140, y}, fontSize, 2, (Color){155, 89, 182, 255});

        DrawTextEx(GetFontDefault(), "B", (Vector2){x + 190, y}, fontSize, 2, (Color){231, 76, 60, 255});
        DrawTextEx(GetFontDefault(), "R", (Vector2){x + 225, y}, fontSize, 2, (Color){241, 196, 15, 255});
        DrawTextEx(GetFontDefault(), "I", (Vector2){x + 260, y}, fontSize, 2, (Color){46, 204, 113, 255});
        DrawTextEx(GetFontDefault(), "C", (Vector2){x + 295, y}, fontSize, 2, (Color){52, 152, 219, 255});
        DrawTextEx(GetFontDefault(), "K", (Vector2){x + 330, y}, fontSize, 2, (Color){155, 89, 182, 255});
        DrawTextEx(GetFontDefault(), "S", (Vector2){x + 365, y}, fontSize, 2, (Color){241, 196, 15, 255});

        Color startColor = (selectedOption == 0) ? DARKGRAY : BLACK;
        DrawRectangleRec(startRect, (selectedOption == 0) ? Fade(LIGHTGRAY, highlightAlpha) : WHITE);
        DrawText("START GAME", startRect.x + 20, startRect.y + 8, 25, startColor);

        Color exitColor = (selectedOption == 1) ? DARKGRAY : BLACK;
        DrawRectangleRec(exitRect, (selectedOption == 1) ? Fade(LIGHTGRAY, highlightAlpha) : WHITE);
        DrawText("EXIT GAME", exitRect.x + 20, exitRect.y + 8, 25, exitColor);
    }
    else if (currentMenu == MENU_LEVEL)
    {
        DrawLevelMenu();
    }
}

// Update Level Menu
void UpdateLevelMenu(void)
{
    static int lastSelectedOption = selectedOption;

    if (IsKeyPressed(KEY_DOWN))
    {
        selectedOption++;
        if (selectedOption > 2)
            selectedOption = 0;
        if (selectedOption != lastSelectedOption)
            PlaySound(navigateSound);
    }

    if (IsKeyPressed(KEY_UP))
    {
        selectedOption--;
        if (selectedOption < 0)
            selectedOption = 2;
        if (selectedOption != lastSelectedOption)
            PlaySound(navigateSound);
    }

    lastSelectedOption = selectedOption;

    Vector2 mousePoint = GetMousePosition();

    Rectangle level1Rect = {350, 300, 300, 40};
    Rectangle level2Rect = {350, 350, 300, 40};
    Rectangle level3Rect = {350, 400, 300, 40};

    if (CheckCollisionPointRec(mousePoint, level1Rect))
    {
        if (selectedOption != 0)
            PlaySound(navigateSound);
        selectedOption = 0;
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
            StartLevel(1);
    }
    if (CheckCollisionPointRec(mousePoint, level2Rect))
    {
        if (selectedOption != 1)
            PlaySound(navigateSound);
        selectedOption = 1;
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
            StartLevel(2);
    }
    if (CheckCollisionPointRec(mousePoint, level3Rect))
    {
        if (selectedOption != 2)
            PlaySound(navigateSound);
        selectedOption = 2;
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
            StartLevel(3);
    }

    if (IsKeyPressed(KEY_ENTER))
    {
        StartLevel(selectedOption + 1);
    }

    if (IsKeyPressed(KEY_BACKSPACE) || IsKeyPressed(KEY_ESCAPE))
    {
        currentMenu = MENU_MAIN;
        selectedOption = 0;
    }

    highlightAlpha += 0.1f;
    if (highlightAlpha > 0.5f)
        highlightAlpha = 0.5f;
}

// Draw Level Menu
void DrawLevelMenu(void)
{
    ClearBackground(WHITE);

    DrawText("SELECT LEVEL", 350, 200, 40, BLACK);

    Rectangle level1Rect = {350, 300, 300, 40};
    Rectangle level2Rect = {350, 350, 300, 40};
    Rectangle level3Rect = {350, 400, 300, 40};

    Color level1Color = (selectedOption == 0) ? DARKGRAY : BLACK;
    Color level2Color = (selectedOption == 1) ? DARKGRAY : BLACK;
    Color level3Color = (selectedOption == 2) ? DARKGRAY : BLACK;

    DrawRectangleRec(level1Rect, (selectedOption == 0) ? Fade(LIGHTGRAY, highlightAlpha) : WHITE);
    DrawText("LEVEL 1", level1Rect.x + 20, level1Rect.y + 8, 25, level1Color);

    DrawRectangleRec(level2Rect, (selectedOption == 1) ? Fade(LIGHTGRAY, highlightAlpha) : WHITE);
    DrawText("LEVEL 2", level2Rect.x + 20, level2Rect.y + 8, 25, level2Color);

    DrawRectangleRec(level3Rect, (selectedOption == 2) ? Fade(LIGHTGRAY, highlightAlpha) : WHITE);
    DrawText("LEVEL 3", level3Rect.x + 20, level3Rect.y + 8, 25, level3Color);

    DrawText("PRESS ESC TO GO BACK", 350, 500, 20, DARKGRAY);

    Vector2 mousePoint = GetMousePosition();

    if (CheckCollisionPointRec(mousePoint, level1Rect) ||
        CheckCollisionPointRec(mousePoint, level2Rect) ||
        CheckCollisionPointRec(mousePoint, level3Rect))
    {
        SetMouseCursor(MOUSE_CURSOR_POINTING_HAND);
    }
    else
    {
        SetMouseCursor(MOUSE_CURSOR_DEFAULT);
    }
}

// Start selected level
void StartLevel(int level)
{
    printf("Level %d selected!\n", level);
    startGame = true;
    // Load level or game logic here
}