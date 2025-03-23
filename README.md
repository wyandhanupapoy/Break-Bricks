# Main Menu "Break Bricks"

Menu utama adalah tampilan awal game sebelum bermain. Dari sini, pemain bisa memilih berbagai opsi seperti mulai game, pengaturan, leaderboard, dll.

## Struktur Menu
1. **Main Menu**
   - Start Game
   - Level Select
   - Leaderboard
   - Settings
   - Info
   - Exit Game
2. **Level Select**
   - Pilih level 1, 2, atau 3 (tingkat kesulitan berbeda).
3. **Name Input**
   - Masukkan nama pemain untuk leaderboard.
4. **Leaderboard**
   - Tampilkan skor tertinggi dari para pemain.
5. **Settings**
   - Nyalakan/matikan suara.
6. **Info**
   - Informasi tentang game.

## Fungsi Utama
- `InitMainMenu()` → Inisialisasi menu utama saat game dimulai.
- `UpdateMainMenu()` → Update logika menu (misal pindah antar menu).
- `DrawMainMenu()` → Gambar tampilan menu di layar.
- `DrawMainMenuMini()` → Tampilan menu versi kecil/sederhana.
- `UpdateMainMenuMini()` → Update menu mini.

## Kontrol
- `IsExitGame()` → Cek apakah pemain ingin keluar dari game.
- `IsStartGame()` → Cek apakah pemain ingin mulai game.
- `GetSelectedLevel()` → Ambil level yang dipilih pemain.
- `SetStartGame(bool value)` → Atur state mulai game.
- `GetPlayerName()` → Ambil nama pemain.

## Kontrol Suara
- `ToggleSound()` → Nyalakan/matikan suara.
- `IsSoundOn()` → Cek apakah suara aktif.

## Navigasi
- Bisa pakai **mouse** atau **keyboard** buat milih menu.
- Ada **efek suara** saat klik tombol (kalau suara diaktifkan).
