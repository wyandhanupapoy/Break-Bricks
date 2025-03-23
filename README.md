# BreakBricks

BreakBricks adalah sebuah game klasik berbasis Arkanoid di mana pemain mengontrol paddle untuk memantulkan bola dengan tujuan menghancurkan blok-blok yang ada di layar.

## Fitur Utama

### 1. Paddle
- **Deskripsi**: Paddle digunakan untuk memantulkan dan mengarahkan bola agar bisa menghancurkan blok.
- **Fungsi**:
  - Pemain dapat menggerakkan paddle ke kiri dan kanan menggunakan tombol panah kiri (`LEFT`) dan kanan (`RIGHT`).
  - Paddle memiliki batas gerakan agar tidak keluar dari layar.
  - Paddle akan digambar menggunakan warna cyan.

## Struktur Kode

### 1. File `paddle.h`
Mendefinisikan struktur dan fungsi terkait dengan paddle:
- `PADDLE_ROWS` dan `PADDLE_COLS`: Menentukan jumlah paddle dalam game.
- `PADDLE_WIDTH` dan `PADDLE_HEIGHT`: Menentukan ukuran paddle.
- `PADDLE_SPEED`: Kecepatan pergerakan paddle.
- `typedef struct Paddle`: Struktur paddle yang berisi posisi (Rectangle) dan kecepatan (Vector2).
- **Fungsi utama**:
  - `InitPaddles(Paddle paddles[PADDLE_ROWS][PADDLE_COLS])`: Inisialisasi posisi dan kecepatan paddle.
  - `UpdatePaddles(Paddle paddles[PADDLE_ROWS][PADDLE_COLS])`: Memproses input pemain dan memperbarui posisi paddle.
  - `DrawPaddles(Paddle paddles[PADDLE_ROWS][PADDLE_COLS])`: Menggambar paddle di layar.

### 2. File `paddle.c`
Mengimplementasikan fungsi yang dideklarasikan di `paddle.h`.

## Cara Bermain
1. Jalankan game BreakBricks.
2. Gunakan tombol **panah kiri** (`←`) untuk menggerakkan paddle ke kiri.
3. Gunakan tombol **panah kanan** (`→`) untuk menggerakkan paddle ke kanan.
4. Pantulkan bola menggunakan paddle untuk menghancurkan semua blok di layar.
5. Jika bola jatuh ke bawah tanpa terkena paddle, permainan berakhir.

## Persyaratan
- Library **Raylib** harus terinstal untuk menjalankan game ini.
- Kompiler C seperti **GCC** atau **Clang**.


