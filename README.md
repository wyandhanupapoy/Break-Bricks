# 🌌 Proyek 2 - Pengembangan Aplikasi Berbasis Library (C) | D3 Teknik Informatika POLBAN

## 📚 Deskripsi Proyek
Proyek ini merupakan bagian dari tugas **Mata Kuliah Pengembangan Aplikasi Berbasis Library** yang dikembangkan menggunakan bahasa C dan library **Raylib**. 

Fokus dari proyek ini adalah **membuat modul background animasi luar angkasa** yang dapat digunakan ulang (reusable) dalam pengembangan game atau aplikasi grafis lainnya.

### 🔥 Fitur Utama
- **Gradasi Latar Belakang Dinamis:** 
  - Latar belakang dengan efek gradasi warna yang terus berubah secara halus (animasi).
- **Efek Bintang Jatuh:** 
  - 100 bintang bergerak secara vertikal dari atas ke bawah menciptakan nuansa luar angkasa.
  - Bintang yang jatuh akan respawn dari atas secara acak.
- **Struktur Modular:** 
  - Kode dipisahkan dalam file header (`background.h`) dan source (`background.c`) untuk kemudahan integrasi ke proyek lain.

---

## 🧩 Struktur File
```
├── background.c    // Implementasi animasi background (gradasi + bintang)
├── background.h    // Header file untuk deklarasi fungsi dan struct
└── README.md       // Dokumentasi proyek
```

---

## 🛠️ Dependensi
- [Raylib](https://www.raylib.com/) (Graphics library berbasis C)
- Compiler C (GCC/Clang atau setara)

---

## 🚀 Cara Penggunaan
### 1️⃣ Inisialisasi Background
```c
InitBackground();
```

### 2️⃣ Update Background di game loop
```c
UpdateBackground();
```

### 3️⃣ Gambar Background di game loop
```c
DrawBackground();
```

> 📌 **Catatan:** Pastikan Raylib sudah diinisialisasi (`InitWindow()`, `BeginDrawing()`, dst.) sebelum memanggil `DrawBackground()`.

---

## 💾 Contoh Integrasi (Pseudocode)
```c
InitWindow(1000, 650, "Space Background Example");
InitBackground();

while (!WindowShouldClose()) {
    UpdateBackground();
    
    BeginDrawing();
    ClearBackground(BLACK);
    DrawBackground();
    EndDrawing();
}

CloseWindow();
```

---

## 📑 Author
- **Nama:** _(Isi Nama Kamu)_
- **NIM:** _(Isi NIM Kamu)_
- **Kelas:** D3 Teknik Informatika - POLBAN

---

## 📌 License
Proyek ini dibuat untuk tujuan edukasi dan dapat digunakan bebas selama mencantumkan credit sesuai ketentuan tugas.

---

Kalo mau aku tambahin bagian **preview image** atau **GIF contoh running**, tinggal kirim aja nanti aku buatkan. 😊