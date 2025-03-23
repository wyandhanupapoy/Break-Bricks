# 🎖 Leaderboard System - Break Bricks Game

Sistem **Leaderboard** ini dibuat untuk menyimpan, menampilkan, dan mengelola skor pemain dalam game *Break Bricks* menggunakan **Raylib**.

## 📂 File Struktur
```
leaderboard.h
leaderboard.c
assets/images/gold_medal.png
assets/images/silver_medal.png
assets/images/bronze_medal.png
src/leaderboard.dat
```

## 📜 Fitur Utama
✅ Menyimpan data leaderboard ke file binary  
✅ Load dan simpan data leaderboard secara otomatis  
✅ Sorting berdasarkan skor tertinggi dan waktu tercepat  
✅ Menampilkan 3 besar dengan medali (Gold, Silver, Bronze)  
✅ Scroll leaderboard untuk melihat semua data  
✅ Tombol Refresh leaderboard  
✅ Warna status (Win = Hijau, Lose = Merah)

---

## 🗂 Struktur Data
```c
typedef struct {
    char name[MAX_NAME_LENGTH];
    int score;
    float time;
    int level;
    char status[10]; // "Win" atau "Lose"
} LeaderboardEntry;
```

---

## ⚙️ Fungsi Utama
| Fungsi | Deskripsi |
|-------|----------|
| `InitLeaderboard()` | Inisialisasi data leaderboard kosong |
| `AddToLeaderboard()` | Menambahkan entry baru dan otomatis sort |
| `SaveLeaderboard()` | Menyimpan leaderboard ke file `leaderboard.dat` |
| `LoadLeaderboard()` | Memuat leaderboard dari file |
| `SortLeaderboard()` | Mengurutkan leaderboard |
| `DrawLeaderboard()` | Menampilkan leaderboard secara sederhana |
| `DrawLeaderboardMenu()` | Menampilkan leaderboard dengan UI scroll, refresh, dan medali |
| `LoadMedalTextures()` / `UnloadMedalTextures()` | Load & unload texture medali |
| `SetMedalScale()` / `SetMedalSize()` | Mengatur ukuran medali |

---

## 🏅 Medali
- 🥇 **Gold Medal** → Juara 1
- 🥈 **Silver Medal** → Juara 2
- 🥉 **Bronze Medal** → Juara 3

File gambar medali disimpan di folder `assets/images/`.

---

## 💾 Penyimpanan
Leaderboard disimpan di file:
```
src/leaderboard.dat
```
Menggunakan mode binary (`fwrite`, `fread`).

---

## 🔄 Scrolling & Refresh
- Leaderboard bisa di-scroll jika data banyak
- Tersedia tombol **Refresh** untuk me-reload data dari file
- Navigasi menggunakan scroll offset

---

## 🎨 Dependencies
✅ [Raylib](https://www.raylib.com/)  
✅ Texture images for medals

---

## 📈 Contoh Tampilan (Leaderboard)
```
#1  🥇 Player1 - Score: 5000 - Time: 45.23s - Win
#2  🥈 Player2 - Score: 4500 - Time: 50.12s - Win
#3  🥉 Player3 - Score: 4000 - Time: 55.67s - Lose
...
```

---

## 📝 Notes
- Pastikan file medal (`gold_medal.png`, `silver_medal.png`, `bronze_medal.png`) tersedia
- Leaderboard menampilkan **Top 5** di fungsi `DrawLeaderboard()` biasa
- Full leaderboard & fitur scroll ada di `DrawLeaderboardMenu()`

---

## 📌 Author
Created by: **[Your Name]**  
For: *Break Bricks Game Project*

---

Kalau mau dimodifikasi sesuai style atau nambahin gambar, tinggal bilang ya!