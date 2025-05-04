/*
Nama Pembuat:   Wyandhanu Maulidan Nugraha
Nama Fitur:     Leeaderboard
Deskripsi:      Fitur leaderboard untuk menyimpan data pemain dan menampilkannya dalam bentuk tabel
*/

#ifndef LEADERBOARD_H
#define LEADERBOARD_H

#include <raylib.h>

#define MAX_NAME_LENGTH 20
#define MAX_LEADERBOARD_ENTRIES 1000
#define LEADERBOARD_FILE "src/leaderboard.dat"
#define SCROLL_SPEED 10
#define SILVER (Color){192, 192, 192, 255}  // Define silver color
#define BRONZE (Color){205, 127, 50, 255}   // Define bronze color

typedef struct
{
    char name[MAX_NAME_LENGTH];
    int score;
    float time;
    int level;
    char status[10]; // 🔹 Tambahkan status ("WIN" atau "GAME OVER")
} LeaderboardEntry;

void InitLeaderboard(LeaderboardEntry leaderboard[MAX_LEADERBOARD_ENTRIES]);
void AddToLeaderboard(LeaderboardEntry leaderboard[MAX_LEADERBOARD_ENTRIES],
                      const char *name, int score, float time, int level, const char *status);
void DrawLeaderboard(LeaderboardEntry leaderboard[MAX_LEADERBOARD_ENTRIES], int x, int y);
void DrawLeaderboardMenu(LeaderboardEntry *leaderboard, int totalEntries, int scrollOffset);
void SaveLeaderboard(LeaderboardEntry leaderboard[MAX_LEADERBOARD_ENTRIES]);
void LoadLeaderboard(LeaderboardEntry leaderboard[MAX_LEADERBOARD_ENTRIES]);
void SortLeaderboard(LeaderboardEntry leaderboard[MAX_LEADERBOARD_ENTRIES]);

void LoadMedalTextures(void);
void UnloadMedalTextures(void);

void SetMedalScale(float scale);
void SetMedalSize(int width, int height);

#endif
