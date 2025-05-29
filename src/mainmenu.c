// Nama Pembuat: Muhammad Brata Hadinata
// Nama Fitur: mainmenu.c
// Deskripsi: Kode ini mengatur tampilan dan logika Main Menu dalam game "Break Bricks".
//            Modifikasi: Menggunakan linked list dinamis untuk menu.
//            Termasuk menu utama, pemilihan level, pengaturan, input nama pemain, leaderboard, dan info.
//            Kode juga menangani interaksi tombol dengan mouse/keyboard serta efek suara.

#include "mainmenu.h"
#include "sound.h"
// #include "game_state.h" // Sudah diinclude via mainmenu.h
#include "background.h"
#include "layout.h"     // Untuk DrawInfo()
#include "raylib.h"
#include "leaderboard.h" // Untuk MAX_NAME_LENGTH, GetLeaderboardCount, DrawLeaderboardMenuScreen, SCROLL_SPEED
#include <string.h>
#include <stdio.h>
#include <stdlib.h>     // Untuk malloc, free

// 🔹 Variabel Global untuk Menu Dinamis
static MenuScreen* mainMenuScreen = NULL;
static MenuScreen* levelSelectScreen = NULL;
static MenuScreen* nameInputScreen = NULL;
static MenuScreen* leaderboardScreen = NULL;
static MenuScreen* settingsScreen = NULL;
static MenuScreen* infoScreen = NULL;
static MenuScreen* currentActiveScreen = NULL;

// 🔹 Variabel State Game Lainnya (yang sebelumnya static global)
static bool exitGame = false;
static bool startGame = false;
static bool soundOn = true; // Status suara, sinkronkan dengan modul sound jika perlu
static int selectedLevel = 0;
static char playerName[MAX_NAME_LENGTH] = ""; // MAX_NAME_LENGTH dari leaderboard.h
static int letterCount = 0;

// Variabel untuk UI spesifik
static Rectangle textBox = {SCREEN_WIDTH / 2 - 150, 300, 300, 50}; // Disesuaikan untuk tengah
static bool mouseOnText = false;
static int leaderboardScrollOffset = 0;
static Rectangle miniMenuBtn = {850, 580, 140, 40}; // Tombol mini menu di game

// 🔹 Warna Pelangi (tetap sama)
static Color rainbowColors[] = {RED, ORANGE, YELLOW, GREEN, BLUE, PURPLE};
static int rainbowSize = sizeof(rainbowColors) / sizeof(rainbowColors[0]);

// Prototipe fungsi helper internal dan aksi
static void Action_NavigateToLevelSelect(void);
static void Action_NavigateToLeaderboard(void);
static void Action_NavigateToSettings(void);
static void Action_NavigateToInfo(void);
static void Action_ExitGame(void);
static void Action_GoBack(void);
static void Action_SelectLevel1(void);
static void Action_SelectLevel2(void);
static void Action_SelectLevel3(void);
static void Action_ConfirmNameAndStart(void);
static void Action_MM_ToggleSound(void); // Menggunakan prefix MM_ untuk menghindari konflik jika ada ToggleSound global
static void Action_MM_IncreaseVolume(void);
static void Action_MM_DecreaseVolume(void);

// Prototipe fungsi custom draw/update
static void DrawNameInputScreenCustom(Vector2 mousePos);
static void UpdateNameInputScreenCustom(Vector2 mousePos);
static void DrawLeaderboardScreenCustom(Vector2 mousePos);
static void UpdateLeaderboardScreenCustom(Vector2 mousePos);
static void DrawSettingsScreenCustom(Vector2 mousePos);
static void UpdateSettingsScreenCustom(Vector2 mousePos);
static void DrawInfoScreenCustom(Vector2 mousePos);
static void UpdateInfoScreenCustom(Vector2 mousePos);


// 🔹 Gambar Teks Pelangi dengan Spacing yang Lebih Presisi (tetap sama)
void DrawRainbowText(const char *text, int centerX, int posY, int fontSize){
    int currentLetterCount = 0; // Renamed to avoid conflict with global letterCount
    float totalWidth = 0;
    float letterWidths[256] = {0};
    for (int i = 0; text[i] != '\0'; i++) {
        letterWidths[i] = MeasureTextEx(GetFontDefault(), TextFormat("%c", text[i]), fontSize, 2).x;
        totalWidth += letterWidths[i] + 3; // Include spacing in totalWidth calculation more accurately
        currentLetterCount++;
    }
    float startX = centerX - (totalWidth / 2.0f); // Center align
    float xOffset = 0;
    for (int i = 0; i < currentLetterCount; i++) {
        Color letterColor = rainbowColors[i % rainbowSize];
        DrawTextEx(GetFontDefault(), TextFormat("%c", text[i]),
                   (Vector2){startX + xOffset, (float)posY}, fontSize, 2, letterColor);
        xOffset += letterWidths[i] + 5; // Consistent spacing after each letter
    }
}

// 🔹 Gambar Title "BREAK BRICKS" (tetap sama)
void DrawTitle(){
    DrawRainbowText("BREAK BRICKS", SCREEN_WIDTH / 2, 150, 75);
}

// ----------------------------------------------------------------------------------
// Menu Item dan Screen Helper Functions
// ----------------------------------------------------------------------------------
MenuItem* CreateMenuItem(const char* text, Rectangle rect, Color base, Color hover, Color textColor, MenuItemAction action, MenuScreen* target) {
    MenuItem* newItem = (MenuItem*)malloc(sizeof(MenuItem));
    if (!newItem) {
        TraceLog(LOG_ERROR, "Failed to allocate memory for MenuItem");
        return NULL;
    }
    strncpy(newItem->text, text, sizeof(newItem->text) - 1);
    newItem->text[sizeof(newItem->text) - 1] = '\0';
    newItem->rect = rect;
    newItem->baseColor = base;
    newItem->hoverColor = hover;
    newItem->textColor = textColor;
    newItem->action = action;
    newItem->targetScreen = target; // Biasanya NULL jika action menangani navigasi
    newItem->next = NULL;
    return newItem;
}

void AddMenuItemToScreen(MenuScreen* screen, MenuItem* item) {
    if (!screen || !item) return;
    if (screen->itemsHead == NULL) {
        screen->itemsHead = item;
    } else {
        MenuItem* temp = screen->itemsHead;
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = item;
    }
}

MenuScreen* CreateMenuScreen(const char* title, MenuScreenType type, MenuScreen* parent,
                             void (*drawCustom)(Vector2), void (*updateCustom)(Vector2)) {
    MenuScreen* newScreen = (MenuScreen*)malloc(sizeof(MenuScreen));
    if (!newScreen) {
        TraceLog(LOG_ERROR, "Failed to allocate memory for MenuScreen");
        return NULL;
    }
    strncpy(newScreen->title, title, sizeof(newScreen->title) - 1);
    newScreen->title[sizeof(newScreen->title) - 1] = '\0';
    newScreen->type = type;
    newScreen->itemsHead = NULL;
    newScreen->parentScreen = parent;
    newScreen->drawScreenCustom = drawCustom;
    newScreen->updateScreenCustom = updateCustom;
    return newScreen;
}

// ----------------------------------------------------------------------------------
// Actions for MenuItems
// ----------------------------------------------------------------------------------
static void Action_NavigateToLevelSelect(void) { currentActiveScreen = levelSelectScreen; PlaySfx("button_click"); }
static void Action_NavigateToLeaderboard(void) { currentActiveScreen = leaderboardScreen; PlaySfx("button_click"); LoadLeaderboard(LEADERBOARD_FILE); leaderboardScrollOffset = 0;}
static void Action_NavigateToSettings(void) { currentActiveScreen = settingsScreen; PlaySfx("button_click"); }
static void Action_NavigateToInfo(void) { currentActiveScreen = infoScreen; PlaySfx("button_click"); }
static void Action_ExitGame(void) { exitGame = true; PlaySfx("button_click"); }

static void Action_GoBack(void) {
    if (currentActiveScreen && currentActiveScreen->parentScreen) {
        currentActiveScreen = currentActiveScreen->parentScreen;
        PlaySfx("button_click");
    } else {
        currentActiveScreen = mainMenuScreen; // Fallback to main menu
        PlaySfx("button_click");
    }
}

static void Action_SelectLevel(int level) {
    selectedLevel = level;
    letterCount = 0; // Reset player name input
    memset(playerName, 0, sizeof(playerName)); // Clear player name string
    currentActiveScreen = nameInputScreen;
    PlaySfx("button_click");
}
static void Action_SelectLevel1(void) { Action_SelectLevel(1); }
static void Action_SelectLevel2(void) { Action_SelectLevel(2); }
static void Action_SelectLevel3(void) { Action_SelectLevel(3); }

static void Action_ConfirmNameAndStart(void) {
    if (letterCount > 0) {
        startGame = true; // main.c will detect this and change game state
        // currentActiveScreen = mainMenuScreen; // Game will transition out of menu state
        PlaySfx("button_click");
    }
}

static void Action_MM_ToggleSound(void) {
    ToggleSound(); // This function should be from sound.h/sound.c or defined here
    PlaySfx("button_click");
}
static void Action_MM_IncreaseVolume(void) { IncreaseVolume(); PlaySfx("button_click"); } // from sound.h/sound.c
static void Action_MM_DecreaseVolume(void) { DecreaseVolume(); PlaySfx("button_click"); } // from sound.h/sound.c

// ----------------------------------------------------------------------------------
// Custom Screen Draw and Update Functions
// ----------------------------------------------------------------------------------

// --- Name Input Screen ---
static void DrawNameInputScreenCustom(Vector2 mousePos) {
    DrawRectangleRec(textBox, LIGHTGRAY);
    DrawRectangleLinesEx(textBox, 2, mouseOnText ? RED : DARKGRAY);
    DrawText(playerName, textBox.x + 10, textBox.y + (textBox.height - 30)/2, 30, BLACK);

    if (mouseOnText) {
        if (letterCount < MAX_NAME_LENGTH_INPUT) { // MAX_NAME_LENGTH_INPUT is 8
            if (((int)(GetTime() * 2.0f) % 2) == 0) {
                DrawText("_", textBox.x + 10 + MeasureText(playerName, 30), textBox.y + (textBox.height - 30)/2, 30, BLACK);
            }
        }
    }
    DrawText("Press ENTER to confirm", textBox.x, textBox.y + textBox.height + 10, 20, WHITE);
    DrawText("Press BACKSPACE to erase", textBox.x, textBox.y + textBox.height + 35, 20, WHITE);
    DrawText(TextFormat("Max %d characters", MAX_NAME_LENGTH_INPUT), textBox.x, textBox.y + textBox.height + 60, 20, WHITE);
}

static void UpdateNameInputScreenCustom(Vector2 mousePos) {
    mouseOnText = CheckCollisionPointRec(mousePos, textBox);
    if (mouseOnText) {
        SetMouseCursor(MOUSE_CURSOR_IBEAM);
        int key = GetCharPressed();
        while (key > 0) { // Process all characters in the queue
            if ((key >= 32) && (key <= 125)) { // Printable characters
                if (letterCount < MAX_NAME_LENGTH_INPUT) {
                    playerName[letterCount] = (char)key;
                    playerName[letterCount + 1] = '\0';
                    letterCount++;
                }
            }
            key = GetCharPressed(); // Get next char
        }

        if (IsKeyPressed(KEY_BACKSPACE)) {
            if (letterCount > 0) {
                letterCount--;
                playerName[letterCount] = '\0';
            }
        }
        if (IsKeyPressed(KEY_ENTER)) {
            Action_ConfirmNameAndStart();
        }
    } else {
        SetMouseCursor(MOUSE_CURSOR_DEFAULT);
    }
    // "BACK" button is a standard MenuItem, handled by generic update
}

// --- Leaderboard Screen ---
static void DrawLeaderboardScreenCustom(Vector2 mousePos) {
    DrawLeaderboardMenuScreen(leaderboardScrollOffset); // From leaderboard.c
}

static void UpdateLeaderboardScreenCustom(Vector2 mousePos) {
    leaderboardScrollOffset -= (GetMouseWheelMove() * SCROLL_SPEED); // SCROLL_SPEED from leaderboard.h

    int totalBoardEntries = GetLeaderboardCount(); // From leaderboard.c
    int maxScroll = 0;
    if (totalBoardEntries > 5) { // Assuming roughly 5 entries visible without scroll. Adjust as needed.
        int contentHeight = totalBoardEntries * 30; // Approx height per entry
        int visibleAreaHeight = 380; // Approx visible area in DrawLeaderboardMenuScreen
        if (contentHeight > visibleAreaHeight) {
            maxScroll = contentHeight - visibleAreaHeight;
        }
    }

    if (leaderboardScrollOffset < 0) leaderboardScrollOffset = 0;
    if (leaderboardScrollOffset > maxScroll) leaderboardScrollOffset = maxScroll;

    if (IsKeyPressed(KEY_BACKSPACE)) { // Specific back handling
        Action_GoBack();
    }
}

// --- Settings Screen ---
// Using rects from original static buttons for specific layout
static Rectangle settings_SoundToggleBtnRect = {SCREEN_WIDTH / 2 - 70, 280, 140, 40};
static Rectangle settings_VolDownBtnRect = {SCREEN_WIDTH / 2 - 120, 280, 40, 40};
static Rectangle settings_VolUpBtnRect = {SCREEN_WIDTH / 2 + 80, 280, 40, 40};

static void DrawSettingsScreenCustom(Vector2 mousePos) {
    // Sound Toggle Button
    Color soundColor = CheckCollisionPointRec(mousePos, settings_SoundToggleBtnRect) ? SKYBLUE : YELLOW;
    DrawRectangleRec(settings_SoundToggleBtnRect, soundColor);
    const char* soundText = IsSoundOn() ? "SOUND ON" : "SOUND OFF";
    DrawText(soundText, settings_SoundToggleBtnRect.x + (settings_SoundToggleBtnRect.width - MeasureText(soundText, 20))/2, settings_SoundToggleBtnRect.y + 10, 20, BLACK);

    // Volume Down Button
    Color decreaseColor = CheckCollisionPointRec(mousePos, settings_VolDownBtnRect) ? SKYBLUE : YELLOW;
    DrawRectangleRec(settings_VolDownBtnRect, decreaseColor);
    DrawText("-", settings_VolDownBtnRect.x + (settings_VolDownBtnRect.width - MeasureText("-", 20))/2, settings_VolDownBtnRect.y + 10, 20, BLACK);

    // Volume Up Button
    Color increaseColor = CheckCollisionPointRec(mousePos, settings_VolUpBtnRect) ? SKYBLUE : YELLOW;
    DrawRectangleRec(settings_VolUpBtnRect, increaseColor);
    DrawText("+", settings_VolUpBtnRect.x + (settings_VolUpBtnRect.width - MeasureText("+", 20))/2, settings_VolUpBtnRect.y + 10, 20, BLACK);
}

static void UpdateSettingsScreenCustom(Vector2 mousePos) {
    if (CheckCollisionPointRec(mousePos, settings_SoundToggleBtnRect) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
        Action_MM_ToggleSound();
    }
    if (CheckCollisionPointRec(mousePos, settings_VolDownBtnRect) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
        Action_MM_DecreaseVolume();
    }
    if (CheckCollisionPointRec(mousePos, settings_VolUpBtnRect) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
        Action_MM_IncreaseVolume();
    }
    if (IsKeyPressed(KEY_BACKSPACE)) { // Back handled by MenuItem or this
         Action_GoBack();
    }
    // "BACK" MenuItem is handled by generic update
}

// --- Info Screen ---
static void DrawInfoScreenCustom(Vector2 mousePos) {
    // Titles drawn by DrawDynamicMainMenu title handler
    DrawInfo(); // From layout.c, draws the list of names
}

static void UpdateInfoScreenCustom(Vector2 mousePos) {
    if (IsKeyPressed(KEY_BACKSPACE)) { // Back handled by MenuItem or this
         Action_GoBack();
    }
    // "BACK" MenuItem is handled by generic update
}


// ----------------------------------------------------------------------------------
// Main Menu Functions (Dynamic Version)
// ----------------------------------------------------------------------------------
void InitDynamicMainMenu(void) {
    FreeDynamicMainMenu(); // Clear any existing menu

    float btnWidth = 320, btnHeight = 50, btnSpacing = 15; // Consistent spacing
    float centerX = SCREEN_WIDTH / 2 - btnWidth / 2;
    float currentY;

    // 1. Main Menu Screen
    mainMenuScreen = CreateMenuScreen("", MENU_TYPE_MAIN, NULL, NULL, NULL); // Title drawn by DrawTitle()
    currentY = 240;
    AddMenuItemToScreen(mainMenuScreen, CreateMenuItem("START GAME", (Rectangle){centerX, currentY, btnWidth, btnHeight}, LIGHTGRAY, GREEN, BLACK, Action_NavigateToLevelSelect, NULL));
    currentY += btnHeight + btnSpacing;
    AddMenuItemToScreen(mainMenuScreen, CreateMenuItem("LEADERBOARD", (Rectangle){centerX, currentY, btnWidth, btnHeight}, LIGHTGRAY, BLUE, BLACK, Action_NavigateToLeaderboard, NULL));
    currentY += btnHeight + btnSpacing;
    AddMenuItemToScreen(mainMenuScreen, CreateMenuItem("SETTINGS", (Rectangle){centerX, currentY, btnWidth, btnHeight}, LIGHTGRAY, YELLOW, BLACK, Action_NavigateToSettings, NULL));
    currentY += btnHeight + btnSpacing;
    AddMenuItemToScreen(mainMenuScreen, CreateMenuItem("INFO", (Rectangle){centerX, currentY, btnWidth, btnHeight}, LIGHTGRAY, SKYBLUE, BLACK, Action_NavigateToInfo, NULL));
    currentY += btnHeight + btnSpacing;
    AddMenuItemToScreen(mainMenuScreen, CreateMenuItem("EXIT GAME", (Rectangle){centerX, currentY, btnWidth, btnHeight}, LIGHTGRAY, RED, BLACK, Action_ExitGame, NULL));

    // 2. Level Select Screen
    levelSelectScreen = CreateMenuScreen("SELECT LEVEL", MENU_TYPE_LEVEL_SELECT, mainMenuScreen, NULL, NULL);
    currentY = 240;
    AddMenuItemToScreen(levelSelectScreen, CreateMenuItem("EASY", (Rectangle){centerX, currentY, btnWidth, btnHeight}, LIGHTGRAY, GREEN, BLACK, Action_SelectLevel1, NULL));
    currentY += btnHeight + btnSpacing;
    AddMenuItemToScreen(levelSelectScreen, CreateMenuItem("MEDIUM", (Rectangle){centerX, currentY, btnWidth, btnHeight}, LIGHTGRAY, ORANGE, BLACK, Action_SelectLevel2, NULL));
    currentY += btnHeight + btnSpacing;
    AddMenuItemToScreen(levelSelectScreen, CreateMenuItem("HARD", (Rectangle){centerX, currentY, btnWidth, btnHeight}, LIGHTGRAY, RED, BLACK, Action_SelectLevel3, NULL));
    AddMenuItemToScreen(levelSelectScreen, CreateMenuItem("BACK", (Rectangle){20, 20, 100, 40}, LIGHTGRAY, DARKGRAY, BLACK, Action_GoBack, NULL)); // Top-left back

    // 3. Name Input Screen
    // textBox is defined globally for this screen.
    nameInputScreen = CreateMenuScreen("ENTER YOUR NAME", MENU_TYPE_NAME_INPUT, levelSelectScreen, DrawNameInputScreenCustom, UpdateNameInputScreenCustom);
    AddMenuItemToScreen(nameInputScreen, CreateMenuItem("BACK", (Rectangle){20, 20, 100, 40}, LIGHTGRAY, DARKGRAY, BLACK, Action_GoBack, NULL)); // Top-left back

    // 4. Leaderboard Screen
    leaderboardScreen = CreateMenuScreen("LEADERBOARD", MENU_TYPE_LEADERBOARD, mainMenuScreen, DrawLeaderboardScreenCustom, UpdateLeaderboardScreenCustom);
    // Back is handled by KEY_BACKSPACE in UpdateLeaderboardScreenCustom

    // 5. Settings Screen
    settingsScreen = CreateMenuScreen("SETTINGS", MENU_TYPE_SETTINGS, mainMenuScreen, DrawSettingsScreenCustom, UpdateSettingsScreenCustom);
    // Specific buttons drawn by DrawSettingsScreenCustom, Back button as MenuItem:
    AddMenuItemToScreen(settingsScreen, CreateMenuItem("Back", (Rectangle){SCREEN_WIDTH/2 - 35, 380, 70, 40}, LIGHTGRAY, DARKGRAY, BLACK, Action_GoBack, NULL));

    // 6. Info Screen
    infoScreen = CreateMenuScreen("INFO", MENU_TYPE_INFO, mainMenuScreen, DrawInfoScreenCustom, UpdateInfoScreenCustom);
    AddMenuItemToScreen(infoScreen, CreateMenuItem("Back", (Rectangle){20, 20, 100, 40}, LIGHTGRAY, DARKGRAY, BLACK, Action_GoBack, NULL));


    currentActiveScreen = mainMenuScreen;
    exitGame = false;
    startGame = false;
    selectedLevel = 0;
    soundOn = IsSoundOn(); // Initialize local soundOn with actual sound status
    letterCount = 0;
    strcpy(playerName, "");
    leaderboardScrollOffset = 0;
}

void UpdateDynamicMainMenu(void) {
    if (!currentActiveScreen) return;
    Vector2 mouse = GetMousePosition();

    // Handle custom update logic first
    if (currentActiveScreen->updateScreenCustom) {
        currentActiveScreen->updateScreenCustom(mouse);
    }

    // Handle generic menu item interactions
    MenuItem* currentItem = currentActiveScreen->itemsHead;
    while (currentItem != NULL) {
        if (CheckCollisionPointRec(mouse, currentItem->rect)) {
            if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
                if (currentItem->action) {
                    currentItem->action();
                    // currentActiveScreen might have changed, so break or be careful if continuing loop
                    return; // Action might change screen, so re-evaluate from top next frame
                }
            }
        }
        currentItem = currentItem->next;
    }

    // Generic KEY_BACKSPACE for screens without custom backspace handling in their update
    // (NameInput, Leaderboard, Settings have custom handling or specific back items)
    if (currentActiveScreen->type != MENU_TYPE_NAME_INPUT &&
        currentActiveScreen->type != MENU_TYPE_LEADERBOARD &&
        currentActiveScreen->type != MENU_TYPE_SETTINGS) { // Assuming BACKSPACE is not used otherwise
        if (IsKeyPressed(KEY_BACKSPACE)) {
            Action_GoBack();
        }
    }
}

void DrawDynamicMainMenu(void) {
    if (!currentActiveScreen) return;

    ClearBackground((Color){30, 0, 60, 255});
    DrawBackground(); // From background.c

    Vector2 mouse = GetMousePosition();

    // Draw screen title
    if (currentActiveScreen->type == MENU_TYPE_MAIN) {
        DrawTitle(); // Special title for main menu
    } else if (strlen(currentActiveScreen->title) > 0) {
        int titleFontSize = 45;
        int titleY = 150;
        if(currentActiveScreen->type == MENU_TYPE_LEADERBOARD) titleY = 70;
        else if (currentActiveScreen->type == MENU_TYPE_INFO) titleY = 100;

        DrawRainbowText(currentActiveScreen->title, SCREEN_WIDTH / 2, titleY, titleFontSize);

        if (currentActiveScreen->type == MENU_TYPE_INFO) { // Subtitles for INFO screen
            DrawRainbowText("Dibuat Oleh", SCREEN_WIDTH / 2, titleY + 60, 20);
            DrawRainbowText("Kelompok C6 Proyek 2 POLBAN:", SCREEN_WIDTH / 2, titleY + 85, 20);
        }
    }

    // Draw generic menu items
    MenuItem* currentItem = currentActiveScreen->itemsHead;
    while (currentItem != NULL) {
        Color itemColor = currentItem->baseColor;
        if (CheckCollisionPointRec(mouse, currentItem->rect)) {
            itemColor = currentItem->hoverColor;
        }
        DrawRectangleRec(currentItem->rect, itemColor);

        int fontSize = (currentItem->rect.height > 45) ? 30 : 20; // Adjust font based on button height
        int textWidth = MeasureText(currentItem->text, fontSize);
        DrawText(currentItem->text,
                 currentItem->rect.x + (currentItem->rect.width - textWidth) / 2,
                 currentItem->rect.y + (currentItem->rect.height - fontSize) / 2,
                 fontSize, currentItem->textColor);
        currentItem = currentItem->next;
    }

    // Handle custom drawing for the screen
    if (currentActiveScreen->drawScreenCustom) {
        currentActiveScreen->drawScreenCustom(mouse);
    }
}

void FreeMenuItems(MenuItem* head) {
    MenuItem* current = head;
    MenuItem* next;
    while (current != NULL) {
        next = current->next;
        free(current);
        current = next;
    }
}

void FreeMenuScreen(MenuScreen** screen_ptr) {
    if (screen_ptr && *screen_ptr) {
        FreeMenuItems((*screen_ptr)->itemsHead);
        free(*screen_ptr);
        *screen_ptr = NULL;
    }
}

void FreeDynamicMainMenu(void) {
    FreeMenuScreen(&mainMenuScreen);
    FreeMenuScreen(&levelSelectScreen);
    FreeMenuScreen(&nameInputScreen);
    FreeMenuScreen(&leaderboardScreen);
    FreeMenuScreen(&settingsScreen);
    FreeMenuScreen(&infoScreen);
    currentActiveScreen = NULL; // Ensure it's reset
}

// ----------------------------------------------------------------------------------
// Mini Menu (In-Game) - Stays mostly the same
// ----------------------------------------------------------------------------------
void UpdateMainMenuMini(GameState *state){
    Vector2 mouse = GetMousePosition();
    if ((*state == GAME_START || *state == GAME_PLAY) && CheckCollisionPointRec(mouse, miniMenuBtn) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
        PlaySfx("button_click");
        *state = GAME_MENU; // Signal to main.c to go to menu
        ChangeMusic("assets/sounds/background_music.mp3"); // Assuming ChangeMusic is globally available
        // UpdateMusic(); // main.c's loop calls UpdateMusic
        InitDynamicMainMenu(); // Re-initialize main menu state when returning
    }
}

void DrawMainMenuMini(GameState state){
    if (state != GAME_START && state != GAME_PLAY) return;

    Vector2 mouse = GetMousePosition();
    Color miniColor = CheckCollisionPointRec(mouse, miniMenuBtn) ? SKYBLUE : YELLOW;
    DrawRectangleRec(miniMenuBtn, miniColor);
    const char* text = "Main Menu";
    int textWidth = MeasureText(text, 20);
    DrawText(text, miniMenuBtn.x + (miniMenuBtn.width - textWidth)/2, miniMenuBtn.y + (miniMenuBtn.height - 20)/2, 20, BLACK);
}


// ----------------------------------------------------------------------------------
// Getters and Setters (for main.c and other modules)
// ----------------------------------------------------------------------------------
bool IsExitGame() { return exitGame; }
bool IsStartGame() { return startGame; }
int GetSelectedLevel() { return selectedLevel; }
const char *GetPlayerName() { return playerName; }
void SetStartGame(bool value) { startGame = value; }

MenuScreenType GetCurrentMenuScreenType(void) {
    if (currentActiveScreen) {
        return currentActiveScreen->type;
    }
    return MENU_TYPE_NONE;
}

// Sound control - these call functions from sound.c or are wrappers
// Ensure sound.c provides IsSoundOn(), ToggleMusic(), IncreaseVolume(), DecreaseVolume()
// For this example, ToggleSound is the action, IsSoundOn is the getter.
void ToggleSound() { // This is the one called by Action_MM_ToggleSound
    // Assuming ToggleMusic in sound.c handles the logic of toggling on/off
    // and updates its internal state reflected by IsSoundOn()
    ToggleMusic(); // From sound.h
    soundOn = !soundOn; // Update local reflection if needed, but better to rely on sound module's state
}

bool IsSoundOn() {
    // This should ideally query the sound module's state
    // For now, it uses the local 'soundOn' which is toggled by Action_MM_ToggleSound
    return soundOn;
}