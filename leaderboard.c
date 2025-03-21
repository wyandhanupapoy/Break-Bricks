#include "leaderboard.h"
#include <stdio.h>
#include <string.h>

void InitLeaderboard(LeaderboardEntry leaderboard[MAX_LEADERBOARD_ENTRIES]) {
    for (int i = 0; i < MAX_LEADERBOARD_ENTRIES; i++) {
        strcpy(leaderboard[i].name, "");
        leaderboard[i].score = 0;
        leaderboard[i].time = 9999.9f;
        leaderboard[i].level = 0;
        strcpy(leaderboard[i].status, "");  // Kosongkan status awal
    }
}

void AddToLeaderboard(LeaderboardEntry leaderboard[MAX_LEADERBOARD_ENTRIES], 
                      const char* name, int score, float time, int level, const char* status) {
    // 🔹 Muat leaderboard lama sebelum menambahkan data baru
    LoadLeaderboard(leaderboard);  

    int insertPos = MAX_LEADERBOARD_ENTRIES;
    for (int i = 0; i < MAX_LEADERBOARD_ENTRIES; i++) {
        if (time < leaderboard[i].time || leaderboard[i].score == 0) {
            insertPos = i;
            break;
        }
    }

    if (insertPos < MAX_LEADERBOARD_ENTRIES) {
        for (int j = MAX_LEADERBOARD_ENTRIES - 1; j > insertPos; j--) {
            leaderboard[j] = leaderboard[j - 1];
        }

        strncpy(leaderboard[insertPos].name, name, MAX_NAME_LENGTH - 1);
        leaderboard[insertPos].name[MAX_NAME_LENGTH - 1] = '\0';
        leaderboard[insertPos].score = score;
        leaderboard[insertPos].time = time;
        leaderboard[insertPos].level = level;
        strncpy(leaderboard[insertPos].status, status, 9);
        leaderboard[insertPos].status[9] = '\0';

        SortLeaderboard(leaderboard);
        SaveLeaderboard(leaderboard);  // 🔹 Pastikan leaderboard tersimpan setelah perubahan
    }
}

void SortLeaderboard(LeaderboardEntry leaderboard[MAX_LEADERBOARD_ENTRIES]) {
    for (int i = 0; i < MAX_LEADERBOARD_ENTRIES - 1; i++) {
        for (int j = 0; j < MAX_LEADERBOARD_ENTRIES - i - 1; j++) {
            if (leaderboard[j].time > leaderboard[j + 1].time) {
                LeaderboardEntry temp = leaderboard[j];
                leaderboard[j] = leaderboard[j + 1];
                leaderboard[j + 1] = temp;
            }
        }
    }
}

void DrawLeaderboard(LeaderboardEntry leaderboard[MAX_LEADERBOARD_ENTRIES]) {
    DrawRectangle(100, 50, 800, 500, Fade(DARKGRAY, 0.9f));
    DrawText("LEADERBOARD", 400, 70, 30, WHITE);
    DrawText("Backspace - Back to Menu", 370, 520, 20, LIGHTGRAY);
    
    for (int i = 0; i < MAX_LEADERBOARD_ENTRIES; i++) {
        if (leaderboard[i].score > 0) {
            char entryText[120];
            sprintf(entryText, "%d. %s - %d pts - %.2fs - Level %d - %s", 
                    i + 1, leaderboard[i].name, leaderboard[i].score, 
                    leaderboard[i].time, leaderboard[i].level, leaderboard[i].status);
            DrawText(entryText, 260, 120 + i * 30, 20, WHITE);
        }
    }
}

void SaveLeaderboard(LeaderboardEntry leaderboard[MAX_LEADERBOARD_ENTRIES]) {
    FILE *file = fopen(LEADERBOARD_FILE, "wb");
    if (file != NULL) {
        fwrite(leaderboard, sizeof(LeaderboardEntry), MAX_LEADERBOARD_ENTRIES, file);
        fclose(file);
    }
}

void LoadLeaderboard(LeaderboardEntry leaderboard[MAX_LEADERBOARD_ENTRIES]) {
    FILE *file = fopen(LEADERBOARD_FILE, "rb");
    if (file != NULL) {
        fread(leaderboard, sizeof(LeaderboardEntry), MAX_LEADERBOARD_ENTRIES, file);
        fclose(file);
    } else {
        InitLeaderboard(leaderboard);
    }
}
