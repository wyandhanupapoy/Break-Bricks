#include "leaderboard.h"
#include "game_state.h"
#include <stdio.h>
#include <string.h>

void InitLeaderboard(LeaderboardEntry leaderboard[MAX_LEADERBOARD_ENTRIES]) {
    for (int i = 0; i < MAX_LEADERBOARD_ENTRIES; i++) {
        strcpy(leaderboard[i].name, "");
        leaderboard[i].score = 0;
        leaderboard[i].time = 9999.9f;  // Set waktu awal sangat besar agar bisa dibandingkan
        leaderboard[i].level = 0;
    }
}

void AddToLeaderboard(LeaderboardEntry leaderboard[MAX_LEADERBOARD_ENTRIES], const char* name, int score, float time, int level) {
    // Cek apakah ada slot kosong atau bisa menggantikan yang lebih lambat
    int insertPos = MAX_LEADERBOARD_ENTRIES;
    
    for (int i = 0; i < MAX_LEADERBOARD_ENTRIES; i++) {
        if (time < leaderboard[i].time || leaderboard[i].score == 0) {
            insertPos = i;
            break;
        }
    }
    
    if (insertPos < MAX_LEADERBOARD_ENTRIES) {
        // Geser data ke bawah untuk memberi ruang bagi data baru
        for (int j = MAX_LEADERBOARD_ENTRIES - 1; j > insertPos; j--) {
            leaderboard[j] = leaderboard[j - 1];
        }
        
        // Tambahkan data baru
        strncpy(leaderboard[insertPos].name, name, MAX_NAME_LENGTH - 1);
        leaderboard[insertPos].name[MAX_NAME_LENGTH - 1] = '\0';
        leaderboard[insertPos].score = score;
        leaderboard[insertPos].time = time;
        leaderboard[insertPos].level = level;
        
        // Urutkan leaderboard berdasarkan waktu tercepat
        SortLeaderboard(leaderboard);
        
        // Simpan leaderboard ke file
        SaveLeaderboard(leaderboard);
    }
}

void SortLeaderboard(LeaderboardEntry leaderboard[MAX_LEADERBOARD_ENTRIES]) {
    // Bubble Sort berdasarkan waktu tercepat
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
    DrawRectangle(250, 50, 510, 500, Fade(DARKGRAY, 0.9f));
    DrawText("LEADERBOARD", 400, 70, 30, WHITE);
    DrawText("Backspace - Back to Menu", 370, 520, 20, LIGHTGRAY);
    
    for (int i = 0; i < MAX_LEADERBOARD_ENTRIES; i++) {
        if (leaderboard[i].score > 0) {
            char entryText[100];
            sprintf(entryText, "%d. %s - %d pts - %.2fs - Level %d", 
                    i + 1, leaderboard[i].name, leaderboard[i].score, leaderboard[i].time, leaderboard[i].level);
            DrawText(entryText, 280, 120 + i * 30, 20, WHITE);
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
