# 🧱 Proyek 2 - Modul Block Breaker (Pengembangan Aplikasi Berbasis Library C)  
### 📌 D3 Teknik Informatika - Jurusan Teknik Komputer dan Informatika POLBAN

## 📚 Deskripsi Proyek
Proyek ini merupakan bagian dari **Tugas Proyek 2** pada mata kuliah **Pengembangan Aplikasi Berbasis Library**.  
Modul ini berfungsi untuk **mengelola blok-blok dalam game Breakout / Brick Breaker** menggunakan bahasa C dan library **Raylib**.

Modul dirancang **modular** dan **reusable** sehingga dapat diintegrasikan ke dalam game berbasis Raylib lainnya.

---

## 🔥 Fitur Utama
✅ **Inisialisasi Blok Secara Dinamis**
- Blok tersusun dalam array 2D (5 baris x 10 kolom).
- Otomatis menghitung posisi setiap blok berdasarkan ukuran dan jarak antar blok.

✅ **Render Blok ke Layar**
- Setiap blok yang aktif digambar dengan warna biru dan outline hitam.
- Blok yang sudah dihancurkan (tidak aktif) tidak akan digambar.

✅ **Struktur Modular**
- `block.c`: Implementasi fungsi.
- `block.h`: Deklarasi struct dan fungsi.

---

## 🧩 Struktur File
```
├── block.c         // Logika inisialisasi dan gambar blok
├── block.h         // Header file berisi struct dan deklarasi fungsi
└── README.md       // Dokumentasi proyek
```

---

## 🛠️ Spesifikasi Teknis
- **Bahasa:** C
- **Library:** [Raylib](https://www.raylib.com/)
- **Dimensi Blok:** 
  - Lebar: 75 piksel
  - Tinggi: 25 piksel
  - Jarak antar blok: 5 piksel
- **Grid Blok:** 5 baris x 10 kolom

---

## 🚀 Cara Menggunakan
### 1️⃣ Inisialisasi Blok
```c
Block blocks[ROWS][COLS];
InitBlocks(blocks);
```

### 2️⃣ Menggambar Blok di Game Loop
```c
DrawBlocks(blocks);
```

> Pastikan Raylib sudah diinisialisasi dan berada di dalam `BeginDrawing()` serta `EndDrawing()` saat memanggil `DrawBlocks()`.

---

## 💾 Contoh Penggunaan
```c
#include "raylib.h"
#include "block.h"

int main() {
    InitWindow(800, 600, "Block Breaker Example");

    Block blocks[ROWS][COLS];
    InitBlocks(blocks);

    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(RAYWHITE);

        DrawBlocks(blocks);

        EndDrawing();
    }

    CloseWindow();
    return 0;
}
```

---

## 📑 Author
- **Nama:** _(Isi Nama Kamu)_
- **NIM:** _(Isi NIM Kamu)_
- **Kelas:** D3 Teknik Informatika - POLBAN

---

## 📌 License
Proyek ini dibuat untuk **tujuan edukasi** sebagai bagian dari tugas kuliah dan **bebas digunakan** dengan mencantumkan sumber.

---

Kalo mau aku gabungkan README background dan block jadi satu dokumentasi game, tinggal bilang aja yaa! 🎮✨