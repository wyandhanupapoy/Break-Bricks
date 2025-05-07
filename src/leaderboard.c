/*
Nama Pembuat:   Wyandhanu Maulidan Nugraha
Nama Fitur:     Leaderboard
Deskripsi:      Fitur leaderboard untuk menyimpan data pemain dan menampilkannya dalam bentuk tabel
                Diimplementasikan menggunakan struktur data linked list
*/
#include "leaderboard.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

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

void InitLeaderboard(Leaderboard* leaderboard)
{
    leaderboard->head = NULL;
    leaderboard->count = 0;
}

// Helper function to create a new leaderboard entry
LeaderboardEntry* CreateLeaderboardEntry(const char* name, int score, float time, int level, const char* status)
{
    LeaderboardEntry* newEntry = (LeaderboardEntry*)malloc(sizeof(LeaderboardEntry));
    if (newEntry == NULL) {
        // Handle memory allocation failure
        return NULL;
    }
    
    // Copy data to the new entry
    strncpy(newEntry->name, name, MAX_NAME_LENGTH - 1);
    newEntry->name[MAX_NAME_LENGTH - 1] = '\0'; // Ensure null-terminated
    
    newEntry->score = score;
    newEntry->time = time;
    newEntry->level = level;
    
    strncpy(newEntry->status, status, 9);
    newEntry->status[9] = '\0'; // Ensure null-terminated
    
    newEntry->next = NULL;
    
    return newEntry;
}

void AddToLeaderboard(Leaderboard* leaderboard, const char* name, int score, float time, int level, const char* status)
{
    // Create a new entry
    LeaderboardEntry* newEntry = CreateLeaderboardEntry(name, score, time, level, status);
    if (newEntry == NULL) return;
    
    // Add the new entry to the beginning of the list
    newEntry->next = leaderboard->head;
    leaderboard->head = newEntry;
    leaderboard->count++;
    
    // Sort the list after adding the new entry
    SortLeaderboard(leaderboard);
    
    // Trim the list if it exceeds MAX_LEADERBOARD_ENTRIES
    if (leaderboard->count > MAX_LEADERBOARD_ENTRIES) {
        int count = 0;
        LeaderboardEntry* current = leaderboard->head;
        
        // Find the MAX_LEADERBOARD_ENTRIES-th entry
        while (current != NULL && count < MAX_LEADERBOARD_ENTRIES - 1) {
            current = current->next;
            count++;
        }
        
        // Truncate the list
        if (current != NULL) {
            LeaderboardEntry* temp = current->next;
            current->next = NULL;
            
            // Free the remaining entries
            while (temp != NULL) {
                LeaderboardEntry* toFree = temp;
                temp = temp->next;
                free(toFree);
                leaderboard->count--;
            }
        }
    }
    
    // Save the updated leaderboard
    SaveLeaderboard(leaderboard);
}

// Helper function to swap the data of two LeaderboardEntry nodes
void SwapEntryData(LeaderboardEntry* a, LeaderboardEntry* b) {
    // Swap name
    char tempName[MAX_NAME_LENGTH];
    strcpy(tempName, a->name);
    strcpy(a->name, b->name);
    strcpy(b->name, tempName);
    
    // Swap score
    int tempScore = a->score;
    a->score = b->score;
    b->score = tempScore;
    
    // Swap time
    float tempTime = a->time;
    a->time = b->time;
    b->time = tempTime;
    
    // Swap level
    int tempLevel = a->level;
    a->level = b->level;
    b->level = tempLevel;
    
    // Swap status
    char tempStatus[10];
    strcpy(tempStatus, a->status);
    strcpy(a->status, b->status);
    strcpy(b->status, tempStatus);
}

void SortLeaderboard(Leaderboard* leaderboard)
{
    if (leaderboard->head == NULL || leaderboard->head->next == NULL) {
        return; // Empty or single entry, no need to sort
    }
    
    // Bubble sort implementation for linked list
    int swapped;
    LeaderboardEntry* ptr1;
    LeaderboardEntry* lptr = NULL;
    
    do {
        swapped = 0;
        ptr1 = leaderboard->head;
        
        while (ptr1->next != lptr) {
            LeaderboardEntry* ptr2 = ptr1->next;
            
            int shouldSwap = 0;
            
            // Urutkan berdasarkan skor (descending)
            if (ptr1->score < ptr2->score) {
                shouldSwap = 1;
            }
            // Jika skor sama, urutkan berdasarkan waktu (ascending)
            else if (ptr1->score == ptr2->score && ptr1->time > ptr2->time) {
                shouldSwap = 1;
            }
            // Jika skor dan waktu sama, urutkan berdasarkan status ("Win" di atas "Lose")
            else if (ptr1->score == ptr2->score && ptr1->time == ptr2->time) {
                if (strcmp(ptr1->status, "Win") < 0 && strcmp(ptr2->status, "Lose") == 0) {
                    shouldSwap = 1;
                }
            }
            
            if (shouldSwap) {
                SwapEntryData(ptr1, ptr2);
                swapped = 1;
            }
            
            ptr1 = ptr1->next;
        }
        lptr = ptr1;
    } while (swapped);
}

void DrawLeaderboard(Leaderboard* leaderboard, int x, int y)
{
    DrawText("Leaderboard:", x, y, 20, BLACK);
    
    LeaderboardEntry* current = leaderboard->head;
    int i = 0;
    
    // Display top 5 entries
    while (current != NULL && i < 5) {
        char entry[128];
        
        // Potong nama jika lebih dari 15 karakter
        char displayName[MAX_NAME_LENGTH];
        if (strlen(current->name) > 15) {
            strncpy(displayName, current->name, 15);
            displayName[8] = '\0';      // Pastikan null-terminated
            strcat(displayName, "..."); // Tambahkan elipsis
        } else {
            strcpy(displayName, current->name);
        }

        snprintf(entry, sizeof(entry), "%d. %s - Score: %d - Time: %.2f - %s",
                 i + 1, displayName, current->score, current->time, current->status);
        DrawText(entry, x, y + 30 + i * 25, 18, DARKGRAY);
        
        current = current->next;
        i++;
    }
}

LeaderboardEntry* GetLeaderboardEntry(Leaderboard* leaderboard, int index)
{
    if (index < 0 || index >= leaderboard->count) {
        return NULL; // Invalid index
    }
    
    LeaderboardEntry* current = leaderboard->head;
    for (int i = 0; i < index && current != NULL; i++) {
        current = current->next;
    }
    
    return current;
}

int GetLeaderboardCount(Leaderboard* leaderboard)
{
    return leaderboard->count;
}

void DrawLeaderboardMenu(Leaderboard* leaderboard, int scrollOffset)
{
    // Make sure medal textures are loaded before drawing
    if (!medalsLoaded) {
        LoadMedalTextures();
    }

    DrawRectangle(100, 50, 800, 500, Fade(DARKGRAY, 0.9f));
    DrawText("LEADERBOARD", 400, 70, 30, WHITE);
    DrawText("Backspace - Back to Menu", 370, 520, 20, LIGHTGRAY);
    DrawText("Scroll ^", 800, 520, 20, LIGHTGRAY);

    // Draw scroll indicators if needed
    if (scrollOffset > 0) {
        DrawTriangle(
            (Vector2){500, 110},
            (Vector2){515, 95},
            (Vector2){485, 95},
            LIGHTGRAY);
    }

    // Calculate maximum possible scroll offset
    int maxEntries = leaderboard->count;
    int maxScroll = (maxEntries * 30) - 380; // Adjust based on your UI
    if (maxScroll > 0 && scrollOffset < maxScroll) {
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
    LeaderboardEntry* current = leaderboard->head;
    int i = 0;
    
    // Skip entries based on scroll offset (30 pixels per entry)
    int entriesToSkip = scrollOffset / 30;
    for (int j = 0; j < entriesToSkip && current != NULL; j++) {
        current = current->next;
        i++;
    }
    
    // Draw visible entries
    while (current != NULL) {
        int yPos = 150 + ((i - entriesToSkip) * 30);
        
        // Only draw entries that are in the visible area
        if (yPos >= 150 && yPos <= 490) {
            // Draw rank with different colors for top 3
            char rankText[5];
            sprintf(rankText, "#%d", i + 1);
            Color rankColor = WHITE;

            // Draw medals for top 3 ranks with size control
            if (i == 0) {
                rankColor = GOLD;
                DrawTextureEx(goldMedal,
                              (Vector2){120, yPos - 3}, // Position
                              0.0f,                     // Rotation
                              medalScale,               // Scale factor
                              WHITE);                   // Tint
            }
            else if (i == 1) {
                rankColor = SILVER; // Silver
                DrawTextureEx(silverMedal,
                              (Vector2){120, yPos - 3},
                              0.0f,
                              medalScale,
                              WHITE);
            }
            else if (i == 2) {
                rankColor = BRONZE; // Bronze
                DrawTextureEx(bronzeMedal,
                              (Vector2){120, yPos - 3},
                              0.0f,
                              medalScale,
                              WHITE);
            }

            DrawText(rankText, 150, yPos, 20, rankColor);

            // Potong nama jika lebih dari 15 karakter
            char displayName[MAX_NAME_LENGTH];
            if (strlen(current->name) > 15) {
                strncpy(displayName, current->name, 15);
                displayName[8] = '\0';      // Pastikan null-terminated
                strcat(displayName, "..."); // Tambahkan elipsis
            } else {
                strcpy(displayName, current->name);
            }
            DrawText(displayName, 260, yPos, 20, WHITE);

            char scoreText[20];
            sprintf(scoreText, "%d", current->score);
            DrawText(scoreText, 390, yPos, 20, WHITE);

            char timeText[20];
            sprintf(timeText, "%.2fs", current->time);
            DrawText(timeText, 470, yPos, 20, WHITE);

            char levelText[10];
            sprintf(levelText, "%d", current->level);
            DrawText(levelText, 550, yPos, 20, WHITE);

            // Draw status with color
            Color statusColor = WHITE;
            if (strcmp(current->status, "Win") == 0)
                statusColor = GREEN;
            else if (strcmp(current->status, "Lose") == 0)
                statusColor = RED;
            DrawText(current->status, 630, yPos, 20, statusColor);
        }
        
        // Move to next entry
        current = current->next;
        i++;
        
        // Break if we've drawn entries beyond the visible area
        if (yPos > 490) break;
    }
}

void SetMedalScale(float scale)
{
    medalScale = scale;
}

void SetMedalSize(int width, int height)
{
    medalWidth = width;
    medalHeight = height;
}

void SaveLeaderboard(Leaderboard* leaderboard)
{
    FILE* file = fopen(LEADERBOARD_FILE, "wb");
    if (file != NULL) {
        // First write the count
        fwrite(&leaderboard->count, sizeof(int), 1, file);
        
        // Then write each entry without the 'next' pointer
        LeaderboardEntry* current = leaderboard->head;
        while (current != NULL) {
            // Write just the data without the next pointer
            fwrite(current->name, sizeof(char), MAX_NAME_LENGTH, file);
            fwrite(&current->score, sizeof(int), 1, file);
            fwrite(&current->time, sizeof(float), 1, file);
            fwrite(&current->level, sizeof(int), 1, file);
            fwrite(current->status, sizeof(char), 10, file);
            
            current = current->next;
        }
        
        fclose(file);
    }
}

void LoadLeaderboard(Leaderboard* leaderboard)
{
    // Free any existing leaderboard entries
    FreeLeaderboard(leaderboard);
    
    // Initialize a new empty leaderboard
    InitLeaderboard(leaderboard);
    
    FILE* file = fopen(LEADERBOARD_FILE, "rb");
    if (file != NULL) {
        int count;
        // Read the count first
        if (fread(&count, sizeof(int), 1, file) == 1) {
            // Read each entry
            for (int i = 0; i < count && i < MAX_LEADERBOARD_ENTRIES; i++) {
                // Create a temporary structure to hold the data
                char name[MAX_NAME_LENGTH];
                int score;
                float time;
                int level;
                char status[10];
                
                // Read the data
                if (fread(name, sizeof(char), MAX_NAME_LENGTH, file) != MAX_NAME_LENGTH) break;
                if (fread(&score, sizeof(int), 1, file) != 1) break;
                if (fread(&time, sizeof(float), 1, file) != 1) break;
                if (fread(&level, sizeof(int), 1, file) != 1) break;
                if (fread(status, sizeof(char), 10, file) != 10) break;
                
                // Create a new entry and add it to the end of the list
                LeaderboardEntry* newEntry = CreateLeaderboardEntry(name, score, time, level, status);
                if (newEntry == NULL) continue;
                
                // Add to the end of the list to maintain the saved order
                if (leaderboard->head == NULL) {
                    leaderboard->head = newEntry;
                } else {
                    LeaderboardEntry* current = leaderboard->head;
                    while (current->next != NULL) {
                        current = current->next;
                    }
                    current->next = newEntry;
                }
                
                leaderboard->count++;
            }
        }
        fclose(file);
    }
}

void FreeLeaderboard(Leaderboard* leaderboard)
{
    LeaderboardEntry* current = leaderboard->head;
    while (current != NULL) {
        LeaderboardEntry* temp = current;
        current = current->next;
        free(temp);
    }
    
    leaderboard->head = NULL;
    leaderboard->count = 0;
}