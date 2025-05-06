#include "linkedlist_mainmenu.h"
#include "sound.h"
#include "game_state.h"
#include "background.h"
#include "layout.h"
#include "raylib.h"
#include "leaderboard.h"
#include "game_state.h"

#include <string.h>
#include <stdio.h>

typedef struct MenuButton
{
    Rectangle rect;
    char label[50];
    struct MenuButton *next;
} MenuButton;

static MenuButton *mainButtons = NULL;
static MenuButton *levelButtonsLL = NULL;
static MenuState currentMenu = MENU_MAIN;
static char playerName[50] = "";
static bool exitGame = false;

MenuButton *CreateButton(Rectangle rect, const char *label)
{
    MenuButton *btn = (MenuButton *)malloc(sizeof(MenuButton));
    btn->rect = rect;
    strcpy(btn->label, label);
    btn->next = NULL;
    return btn;
}

void AddButton(MenuButton **head, Rectangle rect, const char *label)
{
    MenuButton *newBtn = CreateButton(rect, label);
    if (*head == NULL)
    {
        *head = newBtn;
    }
    else
    {
        MenuButton *current = *head;
        while (current->next != NULL)
            current = current->next;
        current->next = newBtn;
    }
}

void FreeButtons(MenuButton *head)
{
    while (head != NULL)
    {
        MenuButton *tmp = head;
        head = head->next;
        free(tmp);
    }
}

void InitMainMenu()
{
    FreeButtons(mainButtons);
    FreeButtons(levelButtonsLL);
    mainButtons = NULL;
    levelButtonsLL = NULL;

    AddButton(&mainButtons, (Rectangle){350, 250, 320, 50}, "START GAME");
    AddButton(&mainButtons, (Rectangle){350, 320, 320, 50}, "LEADERBOARD");
    AddButton(&mainButtons, (Rectangle){350, 390, 320, 50}, "SETTINGS");
    AddButton(&mainButtons, (Rectangle){350, 460, 320, 50}, "EXIT GAME");
    AddButton(&mainButtons, (Rectangle){900, 590, 70, 40}, "INFO");

    AddButton(&levelButtonsLL, (Rectangle){350, 250, 300, 50}, "EASY");
    AddButton(&levelButtonsLL, (Rectangle){350, 320, 300, 50}, "MEDIUM");
    AddButton(&levelButtonsLL, (Rectangle){350, 390, 300, 50}, "HARD");
    AddButton(&levelButtonsLL, (Rectangle){20, 20, 100, 40}, "BACK");
}

void DrawButtons(MenuButton *head)
{
    Vector2 mouse = GetMousePosition();
    MenuButton *btn = head;
    while (btn != NULL)
    {
        Color color = CheckCollisionPointRec(mouse, btn->rect) ? YELLOW : LIGHTGRAY;
        DrawRectangleRec(btn->rect, color);
        int textWidth = MeasureText(btn->label, 30);
        int textX = btn->rect.x + (btn->rect.width - textWidth) / 2;
        int textY = btn->rect.y + (btn->rect.height - 30) / 2;
        DrawText(btn->label, textX, textY, 30, BLACK);
        btn = btn->next;
    }
}

void DrawMainMenu()
{
    DrawText("MAIN MENU", 350, 180, 40, MAROON);
    DrawButtons(mainButtons);
}

void DrawLevelMenu()
{
    DrawText("SELECT LEVEL", 350, 180, 40, DARKGREEN);
    DrawButtons(levelButtonsLL);
}

void UpdateMainMenu()
{
    Vector2 mouse = GetMousePosition();

    switch (currentMenu)
    {
    case MENU_MAIN:
    {
        MenuButton *btn = mainButtons;
        int index = 0;
        while (btn != NULL)
        {
            if (CheckCollisionPointRec(mouse, btn->rect) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
            {
                PlayButtonClick();
                switch (index)
                {
                case 0:
                    currentMenu = MENU_LEVEL_SELECT;
                    break;
                case 1:
                    currentMenu = MENU_LEADERBOARD;
                    break;
                case 2:
                    currentMenu = MENU_SETTINGS;
                    break;
                case 3:
                    exitGame = true;
                    break;
                case 4:
                    currentMenu = MENU_INFO;
                    break;
                }
            }
            btn = btn->next;
            index++;
        }
        break;
    }
    case MENU_LEVEL_SELECT:
    {
        MenuButton *btn = levelButtonsLL;
        int index = 0;
        while (btn != NULL)
        {
            if (CheckCollisionPointRec(mouse, btn->rect) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
            {
                PlayButtonClick();
                switch (index)
                {
                case 0:
                case 1:
                case 2: /* load level */
                    break;
                case 3:
                    currentMenu = MENU_MAIN;
                    break;
                }
            }
            btn = btn->next;
            index++;
        }
        break;
    }
    default:
        break;
    }
}

bool ShouldExitGame()
{
    return exitGame;
}

MenuState GetCurrentMenu()
{
    return currentMenu;
}

const char *GetPlayerName()
{
    return playerName;
}

void SetPlayerName(const char *name)
{
    strncpy(playerName, name, sizeof(playerName) - 1);
    playerName[sizeof(playerName) - 1] = '\0';
}
