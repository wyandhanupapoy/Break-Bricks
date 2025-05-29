/*
Nama Pembuat:   Wyandhanu Maulidan Nugraha
Nama Fitur:     Leaderboard (Linked List)
Deskripsi:      Implementasi fitur leaderboard menggunakan linked list.
*/
#include "leaderboard.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h> // Untuk malloc dan free

// Pointer ke kepala linked list (global statis untuk modul ini)
static LeaderboardNode* leaderboardHead = NULL;


// Variabel untuk tekstur medali (tetap sama)
static Texture2D goldMedal;
static Texture2D silverMedal;
static Texture2D bronzeMedal;
static bool medalsLoaded = false;
static float medalScale = 0.08f; // Disesuaikan agar lebih kecil
static int medalWidth = 24;    // Default, bisa diubah dengan SetMedalSize
static int medalHeight = 24;   // Default, bisa diubah dengan SetMedalSize

// 🔹 Forward declaration untuk fungsi helper internal
static void FreeLeaderboardRecursive(LeaderboardNode* node) { // <--- TAMBAHKAN static
    if (node == NULL) return;
    FreeLeaderboardRecursive(node->next);
    free(node);
}


// --- Fungsi Inisialisasi & Pembersihan ---

void InitLeaderboard() {
    FreeLeaderboard(); // Bersihkan dulu jika ada sisa
    leaderboardHead = NULL;
    // Pastikan tekstur medali dimuat jika belum
    if (!medalsLoaded) {
        LoadMedalTextures();
    }
}

void FreeLeaderboard() {
    LeaderboardNode* current = leaderboardHead;
    LeaderboardNode* nextNode;
    while (current != NULL) {
        nextNode = current->next;
        free(current);
        current = nextNode;
    }
    leaderboardHead = NULL;
}

// --- Fungsi Operasi Leaderboard ---

void AddEntryToLeaderboard(const char *name, int score, float time, int level, const char *status) {
    LeaderboardNode* newNode = (LeaderboardNode*)malloc(sizeof(LeaderboardNode));
    if (!newNode) {
        TraceLog(LOG_WARNING, "Failed to allocate memory for new leaderboard entry.");
        return;
    }

    strncpy(newNode->name, name, MAX_NAME_LENGTH - 1);
    newNode->name[MAX_NAME_LENGTH - 1] = '\0';
    newNode->score = score;
    newNode->time = time;
    newNode->level = level;
    strncpy(newNode->status, status, sizeof(newNode->status) - 1);
    newNode->status[sizeof(newNode->status) - 1] = '\0';
    newNode->next = NULL;

    // Kasus 1: List kosong atau newNode lebih baik dari head
    if (leaderboardHead == NULL ||
        (newNode->score > leaderboardHead->score) ||
        (newNode->score == leaderboardHead->score && newNode->time < leaderboardHead->time) ||
        (newNode->score == leaderboardHead->score && newNode->time == leaderboardHead->time && strcmp(newNode->status, "Win") == 0 && strcmp(leaderboardHead->status, "GAME OVER") == 0)) {
        newNode->next = leaderboardHead;
        leaderboardHead = newNode;
    } else {
        // Kasus 2: Cari posisi yang tepat untuk disisipkan
        LeaderboardNode* current = leaderboardHead;
        while (current->next != NULL &&
               (newNode->score < current->next->score ||
                (newNode->score == current->next->score && newNode->time > current->next->time) ||
                (newNode->score == current->next->score && newNode->time == current->next->time && !(strcmp(newNode->status, "Win") == 0 && strcmp(current->next->status, "GAME OVER") == 0)))) {
            current = current->next;
        }
        newNode->next = current->next;
        current->next = newNode;
    }

    // Membatasi jumlah entri hingga MAX_LEADERBOARD_ENTRIES
    int count = 0;
    LeaderboardNode* current = leaderboardHead;
    LeaderboardNode* prev = NULL;
    while (current != NULL) {
        count++;
        if (count > MAX_LEADERBOARD_ENTRIES) {
            if (prev) { // Seharusnya selalu ada prev jika count > MAX_LEADERBOARD_ENTRIES
                prev->next = NULL; // Putuskan sisa list
                FreeLeaderboardRecursive(current); // Hapus sisa node setelah prev
            }
            break; 
        }
        prev = current;
        current = current->next;
    }
}


void SaveLeaderboard(const char *filename) {
    FILE *file = fopen(filename, "wb");
    if (!file) {
        TraceLog(LOG_WARNING, "Failed to open leaderboard file for writing: %s", filename);
        return;
    }

    LeaderboardNode* current = leaderboardHead;
    int entriesWritten = 0;
    while (current != NULL && entriesWritten < MAX_LEADERBOARD_ENTRIES) {
        // Hanya tulis data relevan, bukan pointer 'next'
        fwrite(current->name, sizeof(char), MAX_NAME_LENGTH, file);
        fwrite(&current->score, sizeof(int), 1, file);
        fwrite(&current->time, sizeof(float), 1, file);
        fwrite(&current->level, sizeof(int), 1, file);
        fwrite(current->status, sizeof(char), 10, file); // Asumsi status max 10 char
        
        current = current->next;
        entriesWritten++;
    }
    fclose(file);
}

void LoadLeaderboard(const char *filename) {
    FreeLeaderboard(); // Bersihkan list yang ada sebelum memuat

    FILE *file = fopen(filename, "rb");
    if (!file) {
        TraceLog(LOG_INFO, "Leaderboard file not found or cannot be opened: %s. Initializing empty leaderboard.", filename);
        // Tidak perlu InitLeaderboard() lagi karena sudah dihandle FreeLeaderboard() dan head jadi NULL
        return;
    }

    // Buat buffer sementara untuk data yang dibaca
    char tempName[MAX_NAME_LENGTH];
    int tempScore;
    float tempTime;
    int tempLevel;
    char tempStatus[10];

    // Baca entri satu per satu
    while (fread(tempName, sizeof(char), MAX_NAME_LENGTH, file) == MAX_NAME_LENGTH &&
           fread(&tempScore, sizeof(int), 1, file) == 1 &&
           fread(&tempTime, sizeof(float), 1, file) == 1 &&
           fread(&tempLevel, sizeof(int), 1, file) == 1 &&
           fread(tempStatus, sizeof(char), 10, file) == 10)
    {
        // Daripada memanggil AddEntryToLeaderboard yang kompleks dan mahal untuk setiap load,
        // kita akan buat node dan tambahkan ke akhir, lalu sort sekali jika perlu.
        // Atau, karena data di file seharusnya sudah terurut, kita bisa langsung tambahkan ke akhir.
        // Untuk kesederhanaan, kita panggil AddEntryToLeaderboard agar urutannya terjaga.
        AddEntryToLeaderboard(tempName, tempScore, tempTime, tempLevel, tempStatus);
    }

    fclose(file);
}


int GetLeaderboardCount() {
    int count = 0;
    LeaderboardNode* current = leaderboardHead;
    while (current != NULL) {
        count++;
        current = current->next;
    }
    return count;
}


// --- Fungsi Tampilan ---

void DrawLeaderboardInfo(int x, int y, int maxEntriesToDisplay) {
    DrawText("Leaderboard:", x, y, 20, BLACK);
    LeaderboardNode* current = leaderboardHead;
    int entriesDrawn = 0;
    int currentY = y + 30;

    while (current != NULL && entriesDrawn < maxEntriesToDisplay) {
        char entryText[128];
        char displayName[MAX_NAME_LENGTH + 4]; // +4 untuk "..." dan null terminator

        if (strlen(current->name) > 15) {
            strncpy(displayName, current->name, 15);
            displayName[15] = '\0'; // Pastikan null-terminated
            strcat(displayName, "...");
        } else {
            strcpy(displayName, current->name);
        }

        snprintf(entryText, sizeof(entryText), "%d. %s - %d (%.2fs) %s",
                 entriesDrawn + 1, displayName, current->score, current->time, current->status);
        DrawText(entryText, x, currentY, 18, DARKGRAY);

        currentY += 25;
        current = current->next;
        entriesDrawn++;
    }
}

void DrawLeaderboardMenuScreen(int scrollOffset) {
    // Pastikan tekstur medali dimuat
    if (!medalsLoaded) {
        LoadMedalTextures();
    }

    DrawRectangle(100, 50, 800, 500, Fade(DARKGRAY, 0.9f));
    DrawText("LEADERBOARD", 400, 70, 30, WHITE);
    DrawText("Backspace - Back to Menu | Scroll with Mouse Wheel", 250, 520, 20, LIGHTGRAY);

    // Indikator scroll
    int totalEntries = GetLeaderboardCount();
    int contentHeight = totalEntries * 30;
    int visibleAreaHeight = 380; // Tinggi area yang bisa di-scroll (150 sampai 500-30-y_header)

    if (scrollOffset > 0) {
        DrawTriangle((Vector2){860, 130}, (Vector2){875, 115}, (Vector2){845, 115}, LIGHTGRAY); // Panah atas
    }
    if (contentHeight > visibleAreaHeight && scrollOffset < (contentHeight - visibleAreaHeight)) {
        DrawTriangle((Vector2){860, 480}, (Vector2){875, 495}, (Vector2){845, 495}, LIGHTGRAY); // Panah bawah
    }
    
    // Tombol Refresh (opsional, bisa di-handle di mainmenu.c jika perlu)
    // Rectangle refreshButton = {750, 60, 120, 30};
    // Vector2 mousePos = GetMousePosition();
    // Color refreshBtnColor = CheckCollisionPointRec(mousePos, refreshButton) ? SKYBLUE : BLUE;
    // DrawRectangleRec(refreshButton, refreshBtnColor);
    // DrawText("Refresh", 770, 65, 20, WHITE);
    // if (CheckCollisionPointRec(mousePos, refreshButton) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
    //     LoadLeaderboard(LEADERBOARD_FILE); // Reload
    //     PlayButtonClick(); // Asumsi ada fungsi ini
    // }

    DrawLine(100, 110, 900, 110, WHITE); // Garis pembatas
    DrawText("Rank", 150, 120, 20, GOLD);
    DrawText("Name", 260, 120, 20, GOLD);
    DrawText("Score", 420, 120, 20, GOLD); // Disesuaikan x-pos
    DrawText("Time", 520, 120, 20, GOLD);  // Disesuaikan x-pos
    DrawText("Level", 620, 120, 20, GOLD); // Disesuaikan x-pos
    DrawText("Status", 720, 120, 20, GOLD);// Disesuaikan x-pos

    LeaderboardNode* current = leaderboardHead;
    int i = 0;
    while (current != NULL) {
        int yPos = 150 + (i * 30) - scrollOffset;

        // Hanya gambar entri yang terlihat
        if (yPos >= 120 && yPos <= 470) { // Area tampil dari bawah header sampai sebelum footer
            char rankText[10];
            sprintf(rankText, "#%d", i + 1);
            Color rankColor = WHITE;
            Texture2D medalToDraw = {0}; // Default no medal

            if (i == 0) { rankColor = GOLD; medalToDraw = goldMedal; }
            else if (i == 1) { rankColor = SILVER; medalToDraw = silverMedal; }
            else if (i == 2) { rankColor = BRONZE; medalToDraw = bronzeMedal; }

            if (medalToDraw.id != 0 && medalsLoaded) { // Cek jika medali valid dan sudah dimuat
                 DrawTextureEx(medalToDraw, (Vector2){120, yPos -5}, 0.0f, medalScale, WHITE);
            }
            DrawText(rankText, 155, yPos, 20, rankColor);

            char displayName[MAX_NAME_LENGTH + 4];
            if (strlen(current->name) > 15) { // Disesuaikan untuk lebar kolom nama
                strncpy(displayName, current->name, 15);
                displayName[15] = '\0';
                strcat(displayName, "...");
            } else {
                strcpy(displayName, current->name);
            }
            DrawText(displayName, 260, yPos, 20, WHITE);

            char scoreText[20]; sprintf(scoreText, "%d", current->score);
            DrawText(scoreText, 420, yPos, 20, WHITE);

            char timeText[20]; sprintf(timeText, "%.2fs", current->time);
            DrawText(timeText, 520, yPos, 20, WHITE);

            char levelText[10]; sprintf(levelText, "%d", current->level);
            DrawText(levelText, 620, yPos, 20, WHITE);
            
            Color statusColor = WHITE;
            if (strcmp(current->status, "Win") == 0) statusColor = GREEN;
            else if (strcmp(current->status, "GAME OVER") == 0) statusColor = RED; // Cocokkan string dari main.c
            DrawText(current->status, 720, yPos, 20, statusColor);
        }
        i++;
        current = current->next;
         if (i >= MAX_LEADERBOARD_ENTRIES) break; // Hanya tampilkan MAX_LEADERBOARD_ENTRIES
    }
}


// --- Fungsi Tekstur Medali (Implementasi sebagian besar sama) ---

void LoadMedalTextures() {
    if (!medalsLoaded) {
        // Pastikan path relatif terhadap direktori kerja saat eksekusi
        goldMedal = LoadTexture("assets/images/gold_medal.png");
        silverMedal = LoadTexture("assets/images/silver_medal.png");
        bronzeMedal = LoadTexture("assets/images/bronze_medal.png");

        if (goldMedal.id == 0 || silverMedal.id == 0 || bronzeMedal.id == 0) {
            TraceLog(LOG_WARNING, "Failed to load one or more medal textures. Check paths.");
        } else {
            medalsLoaded = true;
            TraceLog(LOG_INFO, "Medal textures loaded successfully.");
        }
    }
}

void UnloadMedalTextures() {
    if (medalsLoaded) {
        UnloadTexture(goldMedal);
        UnloadTexture(silverMedal);
        UnloadTexture(bronzeMedal);
        medalsLoaded = false;
        TraceLog(LOG_INFO, "Medal textures unloaded.");
    }
}

void SetMedalScale(float scale) {
    medalScale = scale;
}

void SetMedalSize(int width, int height) {
    medalWidth = width;
    medalHeight = height;
}