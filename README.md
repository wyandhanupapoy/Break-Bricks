# Sistem Nyawa Pemain

Sistem nyawa digunakan untuk menentukan kapan game selesai (Game Over). Pemain punya sejumlah nyawa yang berkurang kalau bola jatuh/melewati paddle.

## Cara Kerja
- Pemain mulai dengan **3 nyawa**.
- Setiap kali bola tidak berhasil ditangkis paddle dan keluar dari layar bawah, **nyawa berkurang 1**.
- Kalau nyawa sudah habis (**nyawa = 0**), maka:
  - Game masuk ke **Game Over** state.
  - Pemain bisa restart game atau kembali ke menu utama.

## Fungsi yang Digunakan
- `ResetLives()` → Atur ulang nyawa ke nilai awal (biasanya 3) saat game dimulai ulang.
- `LoseLife()` → Kurangi nyawa pemain sebanyak 1 ketika bola jatuh.
- `GetLives()` → Ambil jumlah nyawa saat ini, berguna buat ditampilkan di layar.
- `IsGameOver()` → Cek apakah nyawa habis dan game harus berakhir.

## Visual
Biasanya nyawa ditampilkan dalam bentuk ikon hati atau angka di sudut layar selama permainan.
