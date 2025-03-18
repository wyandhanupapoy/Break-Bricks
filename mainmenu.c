#include "raylib.h"
#include "mainmenu.h"
#include <stdio.h>
#include <stdbool.h>



// Variables
static int selectedOption = 0;
static float highlightAlpha = 0.0f;
static bool exitGame = false;
static bool startGame = false;
static MenuState currentMenu = MENU_MAIN;

// Rectangles for main menu
Rectangle startRect = { 350, 300, 300, 40 };
Rectangle exitRect = { 350, 350, 300, 40 };

// Dummy sound functions
Sound navigateSound;
Sound selectSound;

// Function declarations

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
        static int lastSelectedOption = 0; // Inisialisasi dengan nilai konstan
        lastSelectedOption = selectedOption;

        if (IsKeyPressed(KEY_DOWN)) {
            selectedOption++;
            if (selectedOption > 1) selectedOption = 0;
            if (selectedOption != lastSelectedOption) PlaySound(navigateSound);
        }

        if (IsKeyPressed(KEY_UP)) {
            selectedOption--;
            if (selectedOption < 0) selectedOption = 1;
            if (selectedOption != lastSelectedOption) PlaySound(navigateSound);
        }

        Vector2 mousePoint = GetMousePosition();

        if (CheckCollisionPointRec(mousePoint, startRect)) {
            if (selectedOption != 0) PlaySound(navigateSound);
            selectedOption = 0;

            if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
                currentMenu = MENU_LEVEL;
                PlaySound(selectSound);
                selectedOption = 0;
            }
        }

        if (CheckCollisionPointRec(mousePoint, exitRect)) {
            if (selectedOption != 1) PlaySound(navigateSound);
            selectedOption = 1;

            if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
                exitGame = true;
                PlaySound(selectSound);
            }
        }

        if (IsKeyPressed(KEY_ENTER)) {
            if (selectedOption == 0) {
                currentMenu = MENU_LEVEL;
                PlaySound(selectSound);
                selectedOption = 0;
            }
            else if (selectedOption == 1) {
                exitGame = true;
                PlaySound(selectSound);
            }
        }

        highlightAlpha += (selectedOption >= 0 ? 0.1f : -0.1f);
        if (highlightAlpha > 0.5f) highlightAlpha = 0.5f;
        if (highlightAlpha < 0.0f) highlightAlpha = 0.0f;
    }
    else if (currentMenu == MENU_LEVEL)
    {
        UpdateLevelMenu();
    }
}

// Update Level Menu
void UpdateLevelMenu(void)
{
    static int lastSelectedOption = 0; // Inisialisasi dengan nilai konstan
    lastSelectedOption = selectedOption;

    if (IsKeyPressed(KEY_DOWN)) {
        selectedOption++;
        if (selectedOption > 2) selectedOption = 0;
        if (selectedOption != lastSelectedOption) PlaySound(navigateSound);
    }

    if (IsKeyPressed(KEY_UP)) {
        selectedOption--;
        if (selectedOption < 0) selectedOption = 2;
        if (selectedOption != lastSelectedOption) PlaySound(navigateSound);
    }

    Vector2 mousePoint = GetMousePosition();

    Rectangle levelRects[3] = {
        { 350, 300, 300, 40 },
        { 350, 350, 300, 40 },
        { 350, 400, 300, 40 }
    };

    for (int i = 0; i < 3; i++) {
        if (CheckCollisionPointRec(mousePoint, levelRects[i])) {
            if (selectedOption != i) PlaySound(navigateSound);
            selectedOption = i;
            if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) StartLevel(i + 1);
        }
    }

    if (IsKeyPressed(KEY_ENTER)) {
        StartLevel(selectedOption + 1);
    }

    if (IsKeyPressed(KEY_BACKSPACE) || IsKeyPressed(KEY_ESCAPE)) {
        currentMenu = MENU_MAIN;
        selectedOption = 0;
    }
}

// Start selected level
void StartLevel(int level)
{
    printf("Level %d selected!\n", level);
    startGame = true;
}
