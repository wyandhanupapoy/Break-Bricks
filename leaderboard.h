#ifndef LEADERBOARD_H
#define LEADERBOARD_H

#include <raylib.h>

#define MAX_NAME_LENGTH 20
#define MAX_LEADERBOARD_ENTRIES 10
#define LEADERBOARD_FILE "leaderboard.dat"
#define MAX_LEADERBOARD_ENTRIES 10

typedef struct {
    char name[MAX_NAME_LENGTH];
    int score;
    float time;
    int level;
} LeaderboardEntry;

void InitLeaderboard(LeaderboardEntry leaderboard[MAX_LEADERBOARD_ENTRIES]);
void AddToLeaderboard(LeaderboardEntry leaderboard[MAX_LEADERBOARD_ENTRIES], const char* name, int score, float time, int level);
void DrawLeaderboard(LeaderboardEntry leaderboard[MAX_LEADERBOARD_ENTRIES]);
void SaveLeaderboard(LeaderboardEntry leaderboard[MAX_LEADERBOARD_ENTRIES]);
void LoadLeaderboard(LeaderboardEntry leaderboard[MAX_LEADERBOARD_ENTRIES]);
void SortLeaderboard(LeaderboardEntry leaderboard[MAX_LEADERBOARD_ENTRIES]);

#endif
