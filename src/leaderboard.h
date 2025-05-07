/*
Nama Pembuat:   Wyandhanu Maulidan Nugraha
Nama Fitur:     Leaderboard
Deskripsi:      Fitur leaderboard untuk menyimpan data pemain dan menampilkannya dalam bentuk tabel
                Diimplementasikan menggunakan struktur data linked list
*/

#ifndef LEADERBOARD_H
#define LEADERBOARD_H

#include <raylib.h>

#define MAX_NAME_LENGTH 20
#define MAX_LEADERBOARD_ENTRIES 1000  // Maximum entries to display/save
#define LEADERBOARD_FILE "src/leaderboard.dat"
#define SCROLL_SPEED 10
#define SILVER (Color){192, 192, 192, 255}  // Define silver color
#define BRONZE (Color){205, 127, 50, 255}   // Define bronze color

typedef struct LeaderboardEntry {
    char name[MAX_NAME_LENGTH];
    int score;
    float time;
    int level;
    char status[10]; // Status ("WIN" atau "GAME OVER")
    struct LeaderboardEntry* next;  // Pointer to next entry for linked list
} LeaderboardEntry;

// Linked list leaderboard structure
typedef struct {
    LeaderboardEntry* head;  // Head of the linked list
    int count;              // Number of entries in the list
} Leaderboard;

// Initialize a new empty leaderboard
void InitLeaderboard(Leaderboard* leaderboard);

// Add a new entry to the leaderboard
void AddToLeaderboard(Leaderboard* leaderboard, const char* name, int score, float time, int level, const char* status);

// Sort the leaderboard (by score, then time, then status)
void SortLeaderboard(Leaderboard* leaderboard);

// Draw a simplified view of the leaderboard at the given position
void DrawLeaderboard(Leaderboard* leaderboard, int x, int y);

// Draw the full leaderboard menu with scrolling and medals
void DrawLeaderboardMenu(Leaderboard* leaderboard, int scrollOffset);

// Save the leaderboard to a file
void SaveLeaderboard(Leaderboard* leaderboard);

// Load the leaderboard from a file
void LoadLeaderboard(Leaderboard* leaderboard);

// Free all memory allocated for the leaderboard
void FreeLeaderboard(Leaderboard* leaderboard);

// Get an entry at a specific index (0-based)
LeaderboardEntry* GetLeaderboardEntry(Leaderboard* leaderboard, int index);

// Get the count of entries in the leaderboard
int GetLeaderboardCount(Leaderboard* leaderboard);

// Medal texture functions
void LoadMedalTextures(void);
void UnloadMedalTextures(void);
void SetMedalScale(float scale);
void SetMedalSize(int width, int height);

#endif