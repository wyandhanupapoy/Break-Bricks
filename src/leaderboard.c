/* * Nama Pembuat: Wyandhanu Maulidan Nugraha * Nama Fitur:   Leaderboard (Linked List) - Source File * Deskripsi:    Implementasi fitur leaderboard menggunakan linked list. * Mencakup fungsi untuk menambah, menyimpan, memuat, dan menampilkan data leaderboard. */
#include "leaderboard.h" // Menyertakan deklarasi dari file header leaderboard.h
#include <stdio.h>      // Diperlukan untuk operasi file (fopen, fwrite, fread, fclose) dan snprintf.
#include <string.h>     // Diperlukan untuk operasi string (strncpy, strcmp, strlen, strcat).
#include <stdlib.h>     // Diperlukan untuk alokasi memori dinamis (malloc, free).

// === Variabel Global Statis untuk Modul Ini ===
// 'static' berarti variabel ini hanya dapat diakses dari dalam file leaderboard.c ini.
// Pointer ke kepala (entri pertama) dari linked list leaderboard.
// Awalnya NULL, menandakan leaderboard kosong.
static LeaderboardNode* leaderboardHead = NULL;

// Variabel untuk menyimpan tekstur (gambar) medali.
static Texture2D goldMedal;
static Texture2D silverMedal;
static Texture2D bronzeMedal;
static bool medalsLoaded = false; // Status apakah tekstur medali sudah dimuat ke memori.

// Pengaturan default untuk tampilan medali.
static float medalScale = 0.3f; // Skala ukuran medali (0.08 = 8% dari ukuran asli).
static int medalWidth = 24;      // Lebar default medali (dalam piksel).
static int medalHeight = 24;     // Tinggi default medali (dalam piksel).

// === Deklarasi Fungsi Helper Internal ===
// Fungsi ini hanya digunakan di dalam file ini untuk membantu fungsi lain.
static void FreeLeaderboardRecursive(LeaderboardNode* node); // Fungsi rekursif untuk membebaskan memori node.

// Static helper function to determine if entry A should be ranked higher than entry B
static bool is_better(LeaderboardNode* A, LeaderboardNode* B) {
    if (A->score > B->score) return true;  // Higher score is better
    if (A->score < B->score) return false; // Lower score is worse

    // Scores are equal, compare by status
    bool a_is_win = (strcmp(A->status, "WIN") == 0);
    bool b_is_win = (strcmp(B->status, "WIN") == 0);

    // If A is "WIN" and B is not "WIN" (implicitly "GAME OVER" if those are the only two main states), A is better.
    if (a_is_win && !b_is_win) return true;
    // If A is not "WIN" (implicitly "GAME OVER") and B is "WIN", A is worse.
    if (!a_is_win && b_is_win) return false;

    // Scores are equal AND statuses are equivalent for sorting purposes
    // (e.g., both are "WIN", or both are "GAME OVER").
    // Now, compare by time (lower time is better).
    return A->time < B->time;
}


// === Implementasi Fungsi ===

// --- Fungsi Inisialisasi & Pembersihan ---
/** * @brief Menginisialisasi sistem leaderboard. * Membersihkan leaderboard yang ada (jika ada), mengatur head ke NULL, * dan memuat tekstur medali jika belum dimuat. * Seharusnya juga memanggil LoadLeaderboard() untuk memuat data dari file. */
void InitLeaderboard() {
    FreeLeaderboard();      // Pastikan leaderboard bersih sebelum inisialisasi.
    leaderboardHead = NULL; // Set kepala list ke NULL (kosong).
    // Muat tekstur medali jika belum pernah dimuat.
    if (!medalsLoaded) {
        LoadMedalTextures();
    }
    // Seharusnya: LoadLeaderboard(LEADERBOARD_FILE); // Untuk memuat data yang tersimpan.
    // Kode asli Anda memanggil LoadLeaderboard() di main.c setelah InitLeaderboard().
    // Itu juga valid, tergantung preferensi struktur kode.
}

/** * @brief Membebaskan semua memori yang dialokasikan untuk node-node leaderboard. * Menggunakan iterasi untuk menghapus setiap node satu per satu. */
void FreeLeaderboard() {
    LeaderboardNode* current = leaderboardHead; // Mulai dari kepala list.
    LeaderboardNode* nextNode;
    while (current != NULL) { // Ulangi selama masih ada node.
        nextNode = current->next; // Simpan pointer ke node berikutnya.
        free(current);            // Bebaskan memori node saat ini.
        current = nextNode;       // Pindah ke node berikutnya.
    }
    leaderboardHead = NULL; // Setelah semua node dibebaskan, set head kembali ke NULL.
}

/** * @brief Fungsi helper rekursif untuk membebaskan memori node dari titik tertentu ke akhir list. * @param node Node awal dari mana pembebasan memori akan dimulai. */
static void FreeLeaderboardRecursive(LeaderboardNode* node) {
    if (node == NULL) return; // Kondisi berhenti rekursi: jika node saat ini NULL.
    FreeLeaderboardRecursive(node->next); // Panggil rekursif untuk node berikutnya.
    free(node);                           // Bebaskan memori node saat ini (setelah anak-anaknya dibebaskan).
}

// --- Fungsi Operasi Leaderboard ---
/** * @brief Menambahkan entri baru ke leaderboard dengan menjaga urutan. * Urutan: Skor tertinggi, lalu status "Win" diutamakan, lalu waktu tercepat. * Juga memastikan jumlah entri tidak melebihi MAX_LEADERBOARD_ENTRIES. * * @param name Nama pemain. * @param score Skor pemain. * @param time Waktu bermain pemain. * @param level Level yang dicapai. * @param status Status akhir permainan ("WIN" atau "GAME OVER"). */
void AddEntryToLeaderboard(const char *name, int score, float time, int level, const char *status) {
    // 1. Alokasikan memori untuk node baru.
    LeaderboardNode* newNode = (LeaderboardNode*)malloc(sizeof(LeaderboardNode));
    if (!newNode) { // Jika alokasi gagal (misalnya, kehabisan memori).
        TraceLog(LOG_WARNING, "LEADERBOARD: Gagal alokasi memori untuk entri baru.");
        return;
    }

    // 2. Isi data ke node baru.
    strncpy(newNode->name, name, MAX_NAME_LENGTH - 1); // Salin nama, sisakan ruang untuk null terminator.
    newNode->name[MAX_NAME_LENGTH - 1] = '\0';         // Pastikan nama diakhiri null terminator.
    newNode->score = score;
    newNode->time = time;
    newNode->level = level;
    strncpy(newNode->status, status, sizeof(newNode->status) - 1);
    newNode->status[sizeof(newNode->status) - 1] = '\0';
    newNode->next = NULL; // Awalnya, node baru belum menunjuk ke mana pun.

    // 3. Sisipkan node baru ke dalam linked list dengan urutan yang benar.
    // Kasus 1: Leaderboard kosong ATAU node baru lebih baik dari entri pertama (head).
    if (leaderboardHead == NULL || is_better(newNode, leaderboardHead)) {
        newNode->next = leaderboardHead; // Node baru menunjuk ke head lama.
        leaderboardHead = newNode;       // Node baru menjadi head baru.
    } else {
        // Kasus 2: Cari posisi yang tepat untuk menyisipkan node baru.
        LeaderboardNode* current = leaderboardHead;
        // Iterasi selama node berikutnya ada DAN node berikutnya (current->next) lebih baik dari newNode.
        while (current->next != NULL && is_better(current->next, newNode)) {
            current = current->next; // Pindah ke node berikutnya.
        }
        // Setelah loop, 'current' adalah node SEBELUM posisi penyisipan.
        newNode->next = current->next; // Node baru menunjuk ke node yang tadinya ditunjuk 'current'.
        current->next = newNode;       // 'current' sekarang menunjuk ke node baru.
    }

    // 4. Batasi jumlah entri hingga MAX_LEADERBOARD_ENTRIES.
    int count = 0;
    LeaderboardNode* current = leaderboardHead;
    LeaderboardNode* prev = NULL;
    while (current != NULL) {
        count++;
        if (count > MAX_LEADERBOARD_ENTRIES) {
            // Jika jumlah entri melebihi batas.
            if (prev) { // Seharusnya 'prev' tidak NULL jika count > 1.
                prev->next = NULL; // Putuskan hubungan dari 'prev' ke 'current'. Ini membuat 'prev' jadi node terakhir.
                FreeLeaderboardRecursive(current); // Hapus 'current' dan semua node setelahnya.
            }
            break; // Keluar dari loop, karena sudah memotong kelebihan.
        }
        prev = current;        // Simpan node saat ini sebagai 'prev' untuk iterasi berikutnya.
        current = current->next; // Pindah ke node berikutnya.
    }
}

/** * @brief Menyimpan data leaderboard saat ini ke file biner. * @param filename Nama file untuk menyimpan data. */
void SaveLeaderboard(const char *filename) {
    FILE *file = fopen(filename, "wb"); // Buka file dalam mode "write binary" ("wb").
                                        // "wb" akan membuat file baru atau menimpa yang sudah ada.
    if (!file) { // Jika gagal membuka file.
        TraceLog(LOG_WARNING, "LEADERBOARD: Gagal membuka file leaderboard untuk penulisan: %s", filename);
        return;
    }

    LeaderboardNode* current = leaderboardHead;
    int entriesWritten = 0;
    // Tulis setiap entri ke file, hingga MAX_LEADERBOARD_ENTRIES atau akhir list.
    while (current != NULL && entriesWritten < MAX_LEADERBOARD_ENTRIES) {
        // Tulis setiap field dari struct LeaderboardNode secara berurutan.
        // Perhatikan bahwa pointer 'next' TIDAK disimpan ke file.
        fwrite(current->name, sizeof(char), MAX_NAME_LENGTH, file);
        fwrite(&current->score, sizeof(int), 1, file);
        fwrite(&current->time, sizeof(float), 1, file);
        fwrite(&current->level, sizeof(int), 1, file);
        fwrite(current->status, sizeof(char), 10, file); // Asumsi status maks 10 char seperti di .h (char status[10])
        current = current->next;
        entriesWritten++;
    }
    fclose(file); // Tutup file setelah selesai menulis.
    // TraceLog(LOG_INFO, "LEADERBOARD: Data disimpan ke %s", filename);
}

/** * @brief Memuat data leaderboard dari file biner. * Membersihkan list yang ada sebelum memuat. * @param filename Nama file untuk memuat data. */
void LoadLeaderboard(const char *filename) {
    FreeLeaderboard(); // Bersihkan list yang ada di memori sebelum memuat dari file.
    FILE *file = fopen(filename, "rb"); // Buka file dalam mode "read binary" ("rb").
    if (!file) { // Jika file tidak ditemukan atau tidak bisa dibuka.
        TraceLog(LOG_INFO, "LEADERBOARD: File leaderboard tidak ditemukan atau gagal dibuka: %s. Leaderboard kosong.", filename);
        // Tidak perlu InitLeaderboard() lagi, karena FreeLeaderboard() sudah mengatur head ke NULL.
        return;
    }

    // Buffer sementara untuk membaca data dari file.
    char tempName[MAX_NAME_LENGTH];
    int tempScore;
    float tempTime;
    int tempLevel;
    char tempStatus[10]; // Sesuaikan dengan ukuran yang ditulis di SaveLeaderboard

    // Baca entri satu per satu dari file.
    // fread mengembalikan jumlah item yang berhasil dibaca.
    // Loop berlanjut selama semua field berhasil dibaca untuk satu entri.
    while (fread(tempName, sizeof(char), MAX_NAME_LENGTH, file) == MAX_NAME_LENGTH &&
           fread(&tempScore, sizeof(int), 1, file) == 1 &&
           fread(&tempTime, sizeof(float), 1, file) == 1 &&
           fread(&tempLevel, sizeof(int), 1, file) == 1 &&
           fread(tempStatus, sizeof(char), 10, file) == 10) // Baca 10 byte untuk status
    {
        // Tambahkan entri yang dibaca ke leaderboard di memori.
        // AddEntryToLeaderboard akan menangani penyisipan secara terurut.
        AddEntryToLeaderboard(tempName, tempScore, tempTime, tempLevel, tempStatus);
    }
    fclose(file); // Tutup file setelah selesai membaca.
    // TraceLog(LOG_INFO, "LEADERBOARD: Data dimuat dari %s", filename);
}

/** * @brief Mendapatkan jumlah entri yang ada di leaderboard saat ini. * @return Jumlah entri. */
int GetLeaderboardCount() {
    int count = 0;
    LeaderboardNode* current = leaderboardHead;
    while (current != NULL) { // Iterasi sepanjang list.
        count++;
        current = current->next;
    }
    return count;
}

// --- Fungsi Tampilan ---
/** * @brief Menggambar informasi leaderboard ringkas pada posisi x, y. * @param x Posisi X untuk mulai menggambar. * @param y Posisi Y untuk mulai menggambar. * @param maxEntriesToDisplay Jumlah entri maksimum yang akan ditampilkan. */
void DrawLeaderboardInfo(int x, int y, int maxEntriesToDisplay) {
    DrawText("Leaderboard:", x, y, 20, BLACK); // Judul kecil.
    LeaderboardNode* current = leaderboardHead;
    int entriesDrawn = 0;
    int currentY = y + 30; // Posisi Y untuk entri pertama.

    // Loop untuk menggambar setiap entri hingga batas maxEntriesToDisplay atau akhir list.
    while (current != NULL && entriesDrawn < maxEntriesToDisplay) {
        char entryText[128]; // Buffer untuk teks entri.
        char displayName[MAX_NAME_LENGTH + 4]; // Buffer untuk nama (bisa dipotong jika terlalu panjang).

        // Jika nama terlalu panjang (misalnya > 15 karakter), potong dan tambahkan "...".
        if (strlen(current->name) > 15) {
            strncpy(displayName, current->name, 15);
            displayName[15] = '\0'; // Pastikan null-terminated.
            strcat(displayName, "...");
        } else {
            strcpy(displayName, current->name);
        }

        // Format teks entri: "Peringkat. Nama - Skor (Waktu s) Status"
        snprintf(entryText, sizeof(entryText), "%d. %s - %d (%.2fs) %s",
                 entriesDrawn + 1, displayName, current->score, current->time, current->status);
        DrawText(entryText, x, currentY, 18, DARKGRAY); // Gambar teks entri.

        currentY += 25; // Naikkan posisi Y untuk entri berikutnya.
        current = current->next;
        entriesDrawn++;
    }
}

/** * @brief Menggambar layar menu leaderboard lengkap dengan scroll dan medali. * @param scrollOffset Nilai offset untuk scrolling (menggeser tampilan vertikal). */
void DrawLeaderboardMenuScreen(int scrollOffset) {
    // Pastikan tekstur medali sudah dimuat.
    if (!medalsLoaded) {
        LoadMedalTextures();
    }

    // Latar belakang menu leaderboard.
    DrawText("Backspace - Back to Menu", 370, 540, 20, LIGHTGRAY); // Info kontrol.

    // Indikator scroll (panah atas/bawah) jika konten bisa di-scroll.
    int totalEntries = GetLeaderboardCount();
    int contentHeight = totalEntries * 30; // Perkiraan tinggi total konten (30 piksel per entri).
    int visibleAreaHeight = 380; // Tinggi area yang bisa di-scroll (dari Y=120 hingga Y=500).

    if (scrollOffset > 0) { // Jika sudah di-scroll ke bawah, tampilkan panah atas.
        DrawTriangle((Vector2){860, 130}, (Vector2){875, 115}, (Vector2){845, 115}, LIGHTGRAY);
    }
    if (contentHeight > visibleAreaHeight && scrollOffset < (contentHeight - visibleAreaHeight)) {
        // Jika konten lebih tinggi dari area terlihat DAN belum di-scroll sampai akhir, tampilkan panah bawah.
        DrawTriangle((Vector2){860, 480}, (Vector2){875, 495}, (Vector2){845, 495}, LIGHTGRAY);
    }

    // Garis pemisah dan header tabel.
    DrawLine(100, 100, 900, 100, WHITE);
    DrawRectangle(100, 105, 800, 30, BLACK); // Header background.
    DrawText("Rank", 150, 110, 20, GOLD);
    DrawText("Name", 295, 110, 20, GOLD);
    DrawText("Score", 425, 110, 20, GOLD);
    DrawText("Time", 540, 110, 20, GOLD);
    DrawText("Level", 630, 110, 20, GOLD);
    DrawText("Status", 765, 110, 20, GOLD);
    DrawLine(100, 530, 900, 530, WHITE);
<<<<<<< HEAD
=======

>>>>>>> origin/LinkedList-Level
    DrawLine(900, 100, 900, 530, WHITE);
    DrawLine(100, 100, 100, 530, WHITE);
    DrawLine(240, 100, 240, 530, WHITE);
    DrawLine(400, 100, 400, 530, WHITE);
    DrawLine(510, 100, 510, 530, WHITE);
    DrawLine(610, 100, 610, 530, WHITE);
    DrawLine(710, 100, 710, 530, WHITE);

    LeaderboardNode* current = leaderboardHead;
    int i = 0; // Indeks peringkat (mulai dari 0).
    while (current != NULL) {
        // Hitung posisi Y entri dengan mempertimbangkan scrollOffset.
        int yPos = 150 + (i * 30) - scrollOffset;

        // Hanya gambar entri yang terlihat dalam area yang ditentukan.
        if (yPos >= 140 && yPos <= 500) { // Adjusted for header and potential bottom margin
            char rankText[10];
            sprintf(rankText, "#%d", i + 1); // Teks peringkat (misalnya, "#1").
            Color rankColor = WHITE;
            Texture2D medalToDraw = {0}; // Tekstur medali yang akan digambar (default: tidak ada).

            // Tentukan warna peringkat dan medali untuk 3 teratas.
            if (i == 0) { rankColor = GOLD; medalToDraw = goldMedal; }
            else if (i == 1) { rankColor = SILVER; medalToDraw = silverMedal; }
            else if (i == 2) { rankColor = BRONZE; medalToDraw = bronzeMedal; }

            // Gambar medali jika ada dan sudah dimuat.
            if (medalToDraw.id != 0 && medalsLoaded) {
                DrawTextureEx(medalToDraw, (Vector2){120.0f, (float)yPos - 1.5f}, 0.0f, medalScale, WHITE);
            }
            DrawText(rankText, 155, yPos, 20, rankColor); // Gambar teks peringkat.

            // Potong nama jika terlalu panjang.
            char displayName[MAX_NAME_LENGTH + 4];
            if (strlen(current->name) > 15) {
                strncpy(displayName, current->name, 15);
                displayName[15] = '\0';
                strcat(displayName, "...");
            } else {
                strcpy(displayName, current->name);
            }
            DrawText(displayName, 260, yPos, 20, WHITE); // Gambar nama.

            // Gambar skor, waktu, dan level.
            char scoreText[20]; sprintf(scoreText, "%d", current->score);
            DrawText(scoreText, 420, yPos, 20, WHITE);
            char timeText[20];  sprintf(timeText, "%.2fs", current->time);
            DrawText(timeText, 520, yPos, 20, WHITE);
            char levelText[10]; sprintf(levelText, "%d", current->level);
            DrawText(levelText, 620, yPos, 20, WHITE);

            // Gambar status dengan warna berbeda (hijau untuk WIN, merah untuk GAME OVER).
            Color statusColor = WHITE;
            if (strcmp(current->status, "WIN") == 0) statusColor = GREEN;
            else if (strcmp(current->status, "GAME OVER") == 0) statusColor = RED;
            DrawText(current->status, 720, yPos, 20, statusColor);
        }
        i++;
        current = current->next;
        if (i >= MAX_LEADERBOARD_ENTRIES) break; // Hanya tampilkan hingga MAX_LEADERBOARD_ENTRIES.
    }
}

// --- Fungsi Tekstur Medali ---
/** * @brief Memuat tekstur medali dari file gambar. * Hanya dijalankan sekali jika medalsLoaded false. */
void LoadMedalTextures() {
    if (!medalsLoaded) {
        // Path harus relatif terhadap direktori kerja saat program dieksekusi.
        // Contoh: jika program dijalankan dari folder utama proyek, dan gambar ada di assets/images/.
        goldMedal = LoadTexture("assets/images/gold_medal.png");
        silverMedal = LoadTexture("assets/images/silver_medal.png");
        bronzeMedal = LoadTexture("assets/images/bronze_medal.png");

        // Cek apakah semua tekstur berhasil dimuat.
        if (goldMedal.id == 0 || silverMedal.id == 0 || bronzeMedal.id == 0) {
            TraceLog(LOG_WARNING, "LEADERBOARD: Gagal memuat satu atau lebih tekstur medali. Periksa path!");
        } else {
            medalsLoaded = true; // Tandai bahwa medali sudah dimuat.
            TraceLog(LOG_INFO, "LEADERBOARD: Tekstur medali berhasil dimuat.");
        }
    }
}

/** * @brief Melepaskan (unload) tekstur medali dari memori. * Dilakukan saat game ditutup untuk membebaskan sumber daya. */
void UnloadMedalTextures() {
    if (medalsLoaded) {
        UnloadTexture(goldMedal);
        UnloadTexture(silverMedal);
        UnloadTexture(bronzeMedal);
        medalsLoaded = false; // Tandai bahwa medali sudah tidak dimuat.
        TraceLog(LOG_INFO, "LEADERBOARD: Tekstur medali dilepaskan.");
    }
}

/** * @brief Mengatur faktor skala untuk tekstur medali. * @param scale Faktor skala (misalnya, 0.1f untuk 10% ukuran asli). */
void SetMedalScale(float scale) {
    medalScale = scale;
}

/** * @brief Mengatur ukuran (lebar dan tinggi) target untuk medali saat digambar. * Catatan: Kode DrawLeaderboardMenuScreen menggunakan medalScale, bukan medalWidth/Height secara langsung * untuk menggambar tekstur. Fungsi ini mungkin dimaksudkan untuk penggunaan lain atau penyesuaian internal. * @param width Lebar target medali. * @param height Tinggi target medali. */
void SetMedalSize(int width, int height) {
    medalWidth = width;
    medalHeight = height;
}