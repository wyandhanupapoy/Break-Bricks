/*
Nama Pembuat:   Wyandhanu Maulidan Nugraha
Nama Fitur:     Leeaderboard
Deskripsi:      Fitur leaderboard untuk menyimpan data pemain dan menampilkannya dalam bentuk tabel
*/
#include "leaderboard.h"
#include <stdio.h>
#include <string.h>

static Texture2D goldMedal;
static Texture2D silverMedal;
static Texture2D bronzeMedal;
static bool medalsLoaded = false;
static float medalScale = 0.3f; // Scale factor to resize medals (adjust as needed)
static int medalWidth = 24;     // Desired medal width
static int medalHeight = 24;    // Desired medal height

void LoadMedalTextures()
{
    if (!medalsLoaded)
    {
        goldMedal = LoadTexture("assets/images/gold_medal.png");
        silverMedal = LoadTexture("assets/images/silver_medal.png");
        bronzeMedal = LoadTexture("assets/images/bronze_medal.png");
        medalsLoaded = true;
    }
}

void UnloadMedalTextures()
{
    if (medalsLoaded)
    {
        UnloadTexture(goldMedal);
        UnloadTexture(silverMedal);
        UnloadTexture(bronzeMedal);
        medalsLoaded = false;
    }
}

void InitLeaderboard(LeaderboardEntry leaderboard[MAX_LEADERBOARD_ENTRIES])
{
    for (int i = 0; i < MAX_LEADERBOARD_ENTRIES; i++)
    {
        strcpy(leaderboard[i].name, "");
        leaderboard[i].score = 0;
        leaderboard[i].time = 9999.9f;
        leaderboard[i].level = 0;
        strcpy(leaderboard[i].status, ""); // Kosongkan status awal
    }
}

void AddToLeaderboard(LeaderboardEntry leaderboard[MAX_LEADERBOARD_ENTRIES],
                      const char *name, int score, float time, int level, const char *status)
{
    // Muat leaderboard lama sebelum menambahkan data baru
    LoadLeaderboard(leaderboard);

    int insertPos = MAX_LEADERBOARD_ENTRIES;
    for (int i = 0; i < MAX_LEADERBOARD_ENTRIES; i++)
    {
        if (time < leaderboard[i].time || leaderboard[i].score == 0)
        {
            insertPos = i;
            break;
        }
    }

    if (insertPos < MAX_LEADERBOARD_ENTRIES)
    {
        for (int j = MAX_LEADERBOARD_ENTRIES - 1; j > insertPos; j--)
        {
            leaderboard[j] = leaderboard[j - 1];
        }

        // Potong nama jika lebih dari MAX_NAME_LENGTH - 1
        strncpy(leaderboard[insertPos].name, name, MAX_NAME_LENGTH - 1);
        leaderboard[insertPos].name[MAX_NAME_LENGTH - 1] = '\0'; // Pastikan null-terminated

        leaderboard[insertPos].score = score;
        leaderboard[insertPos].time = time;
        leaderboard[insertPos].level = level;
        strncpy(leaderboard[insertPos].status, status, 9);
        leaderboard[insertPos].status[9] = '\0';

        SortLeaderboard(leaderboard);
        SaveLeaderboard(leaderboard); // Pastikan leaderboard tersimpan setelah perubahan
    }
}

void SortLeaderboard(LeaderboardEntry leaderboard[MAX_LEADERBOARD_ENTRIES])
{
    for (int i = 0; i < MAX_LEADERBOARD_ENTRIES - 1; i++)
    {
        for (int j = 0; j < MAX_LEADERBOARD_ENTRIES - i - 1; j++)
        {
            int shouldSwap = 0;

            // Urutkan berdasarkan skor (descending)
            if (leaderboard[j].score < leaderboard[j + 1].score)
            {
                shouldSwap = 1;
            }
            // Jika skor sama, urutkan berdasarkan waktu (ascending)
            else if (leaderboard[j].score == leaderboard[j + 1].score &&
                     leaderboard[j].time > leaderboard[j + 1].time)
            {
                shouldSwap = 1;
            }
            // Jika skor dan waktu sama, urutkan berdasarkan status ("Win" di atas "Lose")
            else if (leaderboard[j].score == leaderboard[j + 1].score &&
                     leaderboard[j].time == leaderboard[j + 1].time)
            {
                if (strcmp(leaderboard[j].status, "Win") < 0 && strcmp(leaderboard[j + 1].status, "Lose") == 0)
                {
                    shouldSwap = 1;
                }
            }

            if (shouldSwap)
            {
                LeaderboardEntry temp = leaderboard[j];
                leaderboard[j] = leaderboard[j + 1];
                leaderboard[j + 1] = temp;
            }
        }
    }
}

void DrawLeaderboard(LeaderboardEntry leaderboard[MAX_LEADERBOARD_ENTRIES], int x, int y)
{
    DrawText("Leaderboard:", x, y, 20, BLACK);
    for (int i = 0; i < 5; i++)
    { // Tampilkan 5 besar
        char entry[128];
        // Potong nama jika lebih dari 15 karakter
        char displayName[MAX_NAME_LENGTH];
        if (strlen(leaderboard[i].name) > 15)
        {
            strncpy(displayName, leaderboard[i].name, 15);
            displayName[8] = '\0';      // Pastikan null-terminated
            strcat(displayName, "..."); // Tambahkan elipsis
        }
        else
        {
            strcpy(displayName, leaderboard[i].name);
        }

        snprintf(entry, sizeof(entry), "%d. %s - Score: %d - Time: %.2f - %s",
                 i + 1, displayName, leaderboard[i].score, leaderboard[i].time, leaderboard[i].status);
        DrawText(entry, x, y + 30 + i * 25, 18, DARKGRAY);
    }
}

// Add this at the top with other global variables in mainmenu.c
static int leaderboardScrollOffset = 0;

// Implementation of DrawLeaderboardMenu with scrolling and refresh button
void DrawLeaderboardMenu(LeaderboardEntry *leaderboard, int totalEntries, int scrollOffset)
{
    // Make sure medal textures are loaded before drawing
    if (!medalsLoaded)
    {
        LoadMedalTextures();
    }

    DrawRectangle(100, 50, 800, 500, Fade(DARKGRAY, 0.9f));
    DrawText("LEADERBOARD", 400, 70, 30, WHITE);
    DrawText("Backspace - Back to Menu", 370, 520, 20, LIGHTGRAY);
    DrawText("Scroll ^", 800, 520, 20, LIGHTGRAY);

    // Draw scroll indicators if needed
    if (scrollOffset > 0)
    {
        DrawTriangle(
            (Vector2){500, 110},
            (Vector2){515, 95},
            (Vector2){485, 95},
            LIGHTGRAY);
    }

    int maxScroll = (MAX_LEADERBOARD_ENTRIES * 30) - 380;
    if (maxScroll > 0 && scrollOffset < maxScroll)
    {
        DrawTriangle(
            (Vector2){500, 500},
            (Vector2){515, 485},
            (Vector2){485, 485},
            LIGHTGRAY);
    }

    // Draw refresh button
    Rectangle refreshButton = {750, 60, 120, 30};
    Vector2 mousePos = GetMousePosition();
    Color refreshBtnColor = CheckCollisionPointRec(mousePos, refreshButton) ? SKYBLUE : BLUE;

    DrawRectangleRec(refreshButton, refreshBtnColor);
    DrawText("Refresh", 770, 65, 20, WHITE);

    // Draw dividing line
    DrawLine(100, 110, 900, 110, WHITE);

    // Draw header
    DrawText("Rank", 150, 120, 20, GOLD);
    DrawText("Name", 260, 120, 20, GOLD);
    DrawText("Score", 390, 120, 20, GOLD);
    DrawText("Time", 470, 120, 20, GOLD);
    DrawText("Level", 550, 120, 20, GOLD);
    DrawText("Status", 630, 120, 20, GOLD);

    // Draw scrollable content
    for (int i = 0; i < totalEntries; i++)
    {
        // Skip empty entries
        if (leaderboard[i].score == 0 && leaderboard[i].time == 9999.9f)
            continue;

        int yPos = 150 + (i * 30) - scrollOffset;

        // Only draw visible entries
        if (yPos >= 150 && yPos <= 490)
        {
            // Draw rank with different colors for top 3
            char rankText[5];
            sprintf(rankText, "#%d", i + 1);
            Color rankColor = WHITE;

            // Draw medals for top 3 ranks with size control
            if (i == 0)
            {
                rankColor = GOLD;
                // Option 1: Using DrawTextureEx with scale
                DrawTextureEx(goldMedal,
                              (Vector2){120, yPos - 3}, // Position (adjust as needed)
                              0.0f,                     // Rotation (0 = no rotation)
                              medalScale,               // Scale factor
                              WHITE);                   // Tint

                // Option 2: Using source/dest rectangles for precise control
                // Rectangle source = {0, 0, goldMedal.width, goldMedal.height};
                // Rectangle dest = {120, yPos - 3, medalWidth, medalHeight};
                // DrawTexturePro(goldMedal, source, dest, (Vector2){0, 0}, 0.0f, WHITE);
            }
            else if (i == 1)
            {
                rankColor = (Color){192, 192, 192, 255}; // Silver
                DrawTextureEx(silverMedal,
                              (Vector2){120, yPos - 3},
                              0.0f,
                              medalScale,
                              WHITE);
            }
            else if (i == 2)
            {
                rankColor = (Color){205, 127, 50, 255}; // Bronze
                DrawTextureEx(bronzeMedal,
                              (Vector2){120, yPos - 3},
                              0.0f,
                              medalScale,
                              WHITE);
            }

            DrawText(rankText, 150, yPos, 20, rankColor);

            // Potong nama jika lebih dari 15 karakter
            char displayName[MAX_NAME_LENGTH];
            if (strlen(leaderboard[i].name) > 15)
            {
                strncpy(displayName, leaderboard[i].name, 15);
                displayName[8] = '\0';      // Pastikan null-terminated
                strcat(displayName, "..."); // Tambahkan elipsis
            }
            else
            {
                strcpy(displayName, leaderboard[i].name);
            }
            DrawText(displayName, 260, yPos, 20, WHITE);

            char scoreText[20];
            sprintf(scoreText, "%d", leaderboard[i].score);
            DrawText(scoreText, 390, yPos, 20, WHITE);

            char timeText[20];
            sprintf(timeText, "%.2fs", leaderboard[i].time);
            DrawText(timeText, 470, yPos, 20, WHITE);

            char levelText[10];
            sprintf(levelText, "%d", leaderboard[i].level);
            DrawText(levelText, 550, yPos, 20, WHITE);

            // Draw status with color
            Color statusColor = WHITE;
            if (strcmp(leaderboard[i].status, "Win") == 0)
                statusColor = GREEN;
            else if (strcmp(leaderboard[i].status, "Lose") == 0)
                statusColor = RED;
            DrawText(leaderboard[i].status, 630, yPos, 20, statusColor);
        }
    }
}

// Function to set medal scale
void SetMedalScale(float scale)
{
    medalScale = scale;
}

// Function to set medal dimensions
void SetMedalSize(int width, int height)
{
    medalWidth = width;
    medalHeight = height;
}

void SaveLeaderboard(LeaderboardEntry leaderboard[MAX_LEADERBOARD_ENTRIES])
{
    FILE *file = fopen(LEADERBOARD_FILE, "wb");
    if (file != NULL)
    {
        fwrite(leaderboard, sizeof(LeaderboardEntry), MAX_LEADERBOARD_ENTRIES, file);
        fclose(file);
    }
}

void LoadLeaderboard(LeaderboardEntry leaderboard[MAX_LEADERBOARD_ENTRIES])
{
    FILE *file = fopen(LEADERBOARD_FILE, "rb");
    if (file != NULL)
    {
        fread(leaderboard, sizeof(LeaderboardEntry), MAX_LEADERBOARD_ENTRIES, file);
        fclose(file);
    }
    else
    {
        InitLeaderboard(leaderboard);
    }
}
