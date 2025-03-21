#ifndef LEADERBOARD_H
#define LEADERBOARD_H

#include <raylib.h>

#define MAX_NAME_LENGTH 20
#define MAX_LEADERBOARD_ENTRIES 10
#define LEADERBOARD_FILE "leaderboard.dat"

typedef struct {
    char name[MAX_NAME_LENGTH];
    int score;
    float time;
    int level;
    char status[10];  // 🔹 Tambahkan status ("WIN" atau "GAME OVER")
} LeaderboardEntry;

void InitLeaderboard(LeaderboardEntry leaderboard[MAX_LEADERBOARD_ENTRIES]);
void AddToLeaderboard(LeaderboardEntry leaderboard[MAX_LEADERBOARD_ENTRIES], 
                      const char* name, int score, float time, int level, const char* status);
void DrawLeaderboard(LeaderboardEntry leaderboard[MAX_LEADERBOARD_ENTRIES]);
void SaveLeaderboard(LeaderboardEntry leaderboard[MAX_LEADERBOARD_ENTRIES]);
void LoadLeaderboard(LeaderboardEntry leaderboard[MAX_LEADERBOARD_ENTRIES]);
void SortLeaderboard(LeaderboardEntry leaderboard[MAX_LEADERBOARD_ENTRIES]);

#endif
