# Stopwatch - BreakBricks

Stopwatch adalah fitur dalam game BreakBricks yang digunakan untuk menampilkan waktu permainan yang terus bertambah dan akan berhenti saat permainan selesai.

## Fitur Stopwatch
- Stopwatch mulai berjalan secara otomatis saat permainan dimulai.
- Waktu bertambah setiap frame selama permainan berlangsung.
- Waktu berhenti saat permainan selesai.
- Waktu ditampilkan di layar agar pemain bisa melihat durasi permainan.

## Struktur Kode

### 1. File `stopwatch.h`
Mendefinisikan struktur dan fungsi terkait dengan stopwatch:
- `STOPWATCH_ROWS` dan `STOPWATCH_COLS`: Menentukan jumlah stopwatch dalam game.
- `typedef struct Stopwatch`: Struktur stopwatch yang berisi waktu yang terus bertambah dan status berjalan atau tidak.
- **Fungsi utama**:
  - `InitStopwatch(Stopwatch sw[STOPWATCH_ROWS][STOPWATCH_COLS])`: Inisialisasi stopwatch dengan waktu awal 0 dan status berjalan.
  - `UpdateStopwatch(Stopwatch sw[STOPWATCH_ROWS][STOPWATCH_COLS])`: Memperbarui waktu selama permainan berlangsung.
  - `DrawStopwatch(Stopwatch sw[STOPWATCH_ROWS][STOPWATCH_COLS])`: Menampilkan waktu permainan di layar.

## Persyaratan
- Library **Raylib** harus terinstal untuk menjalankan stopwatch.
- Kompiler C seperti **GCC** atau **Clang**.





