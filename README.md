# Block Bricker - Bola Module

## Deskripsi
Modul ini berisi implementasi bola dalam permainan *Block Bricker* menggunakan pustaka Raylib. File `bola.c` berisi fungsi-fungsi untuk menginisialisasi, memperbarui, menggambar, dan mereset bola dalam permainan. Sedangkan `bola.h` adalah header file yang mendeklarasikan struktur dan fungsi yang digunakan dalam modul ini.

## Struktur Data
```c
typedef struct {
    Vector2 position; // Posisi bola
    Vector2 speed;    // Kecepatan bola
    float radius;     // Radius bola
    Color color;      // Warna bola
    bool active;      // Status aktif bola
} Bola;
```

## Konstanta
- `SCREEN_W = 830` : Lebar layar permainan.
- `SCREEN_H = 600` : Tinggi layar permainan.
- `MIN_BALL_SPEED = 6.0f` : Kecepatan minimum bola.
- `MAX_BALL_SPEED = 9.0f` : Kecepatan maksimum bola.

## Fungsi

### 1. `void InitBola(Bola bola[BOLA_ROWS][BOLA_COLS])`
Menginisialisasi bola dengan posisi awal di tengah layar dan kecepatan default.

### 2. `void UpdateBola(...)`
Memperbarui posisi bola, menangani pantulan terhadap dinding, paddle, serta tabrakan dengan blok.

### 3. `void DrawBola(Bola bola[BOLA_ROWS][BOLA_COLS])`
Menggambar bola pada layar menggunakan fungsi `DrawCircleV` dari Raylib.

### 4. `void ResetBola(Bola bola[BOLA_ROWS][BOLA_COLS])`
Mengatur ulang posisi bola ke tengah layar dan mengembalikan statusnya menjadi aktif.

## Mekanisme Pantulan
- Bola akan memantul saat mengenai tepi layar kiri, kanan, dan atas.
- Bola akan memantul terhadap paddle dengan arah yang dipengaruhi oleh titik tabrakan.
- Saat menabrak blok, bola akan memantul sesuai dengan sisi tabrakan terdekat.
- Kecepatan bola dibatasi dalam rentang `MIN_BALL_SPEED` hingga `MAX_BALL_SPEED`.

## Ketentuan Tambahan
- Jika semua blok dihancurkan, permainan berakhir dengan kemenangan (`GAME_WIN`).
- Jika bola jatuh melewati bagian bawah layar, statusnya menjadi tidak aktif.
- Sistem skor bertambah berdasarkan waktu saat bola menghancurkan blok.

## Dependensi
Modul ini bergantung pada beberapa file header lain dalam proyek:
- `paddle.h` (untuk mendeteksi tabrakan dengan paddle)
- `block.h` (untuk deteksi tabrakan dengan blok)
- `skor.h` (untuk penambahan skor)
- `stopwatch.h` (untuk penghitungan waktu)
- `game_state.h` (untuk mengatur status permainan)
- `raylib.h` (untuk rendering dan kontrol game)

## Cara Penggunaan
1. **Tambahkan** `bola.c` ke dalam proyek.
2. **Sertakan** `bola.h` di dalam `main.c` dengan `#include "bola.h"`.
3. **Panggil** `InitBola()` saat memulai permainan.
4. **Panggil** `UpdateBola()` setiap frame dalam loop utama.
5. **Panggil** `DrawBola()` untuk menggambar bola di layar.
6. **Gunakan** `ResetBola()` ketika permainan di-reset.

---

Dengan modul ini, bola dalam permainan *Block Bricker* akan memiliki pergerakan yang realistis serta interaksi yang dinamis dengan objek lainnya. 🚀

