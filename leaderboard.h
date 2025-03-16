#ifndef LEADERBOARD_H
#define LEADERBOARD_H

#include <raylib.h>

#define MAX_PLAYERS 1 // Maximum number of players in the leaderboard

typedef struct {
    char name[20]; // Player's name
    int score;     // Player's score
    float time;    // Time taken to finish the game
} LeaderboardEntry;

void InitLeaderboard(LeaderboardEntry leaderboard[MAX_PLAYERS]);
void AddToLeaderboard(LeaderboardEntry leaderboard[MAX_PLAYERS], const char* name, int score, float time);
void DrawLeaderboard(LeaderboardEntry leaderboard[MAX_PLAYERS]);

#endif // LEADERBOARD_H