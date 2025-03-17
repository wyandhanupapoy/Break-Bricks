#include "leaderboard.h"
#include <stdio.h>
#include <string.h>

void InitLeaderboard(LeaderboardEntry leaderboard[MAX_PLAYERS]) {
    for (int i = 0; i < MAX_PLAYERS; i++) {
        strcpy(leaderboard[i].name, ""); // Initialize names to empty
        leaderboard[i].score = 0;          // Initialize scores to 0
        leaderboard[i].time = 0.0f;         // Initialize time to 0
    }
}

void AddToLeaderboard(LeaderboardEntry leaderboard[MAX_PLAYERS], const char* name, int score, float time) {
    // Find the position to insert the new score
    for (int i = 0; i < MAX_PLAYERS; i++) {
        if (score > leaderboard[i].score) {
            // Shift down the lower scores
            for (int j = MAX_PLAYERS - 1; j > i; j--) {
                leaderboard[j] = leaderboard[j - 1];
            }
            // Add the new entry
            strcpy(leaderboard[i].name, name);
            leaderboard[i].score = score;
            leaderboard[i].time = time;
            break;
        }
    }
}

void DrawLeaderboard(LeaderboardEntry leaderboard[MAX_PLAYERS]) {
    for (int i = 0; i < MAX_PLAYERS; i++) {
        if (leaderboard[i].score > 0) { // Only display non-zero scores
            char scoreText[50];
            sprintf(scoreText, "%d. %s - Score: %d, Time: %.2f", i + 1, leaderboard[i].name, leaderboard[i].score, leaderboard[i].time);
            DrawText(scoreText, 10, 50 + i * 20, 20, BLACK);
        }
    }
}