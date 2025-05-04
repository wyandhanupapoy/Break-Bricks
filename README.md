<<<<<<< HEAD
# Sound Effect Feature

## Nama Pembuat
Siti Soviyyah

## Nama Fitur
Sound Effect

## Deskripsi Fitur
Fitur Sound Effect ini bertujuan untuk meningkatkan pengalaman bermain game dengan menambahkan efek suara dan musik latar. Efek suara mencakup suara ketika pemain menekan tombol, bola mengenai paddle, bola menghancurkan blok, kehilangan nyawa, serta suara kemenangan dan kekalahan. Selain itu, fitur ini juga menyediakan fungsi untuk mengontrol musik latar, seperti memainkan, menghentikan, mengganti, dan mengatur volume musik secara dinamis.

## File yang Terkait
- **sound.c**: Berisi implementasi fungsi untuk mengelola efek suara dan musik.
- **sound.h**: Header file yang mendefinisikan fungsi-fungsi dalam `sound.c`.

## Fungsi Utama
- **Inisialisasi dan pembersihan** efek suara dan musik.
- **Pemutaran efek suara** seperti klik tombol, paddle hit, block hit, lose life, game over, dan game win.
- **Pengelolaan musik latar**, termasuk play, stop, pause, resume, dan mengganti lagu.
- **Kontrol volume**, memungkinkan pemain untuk menaikkan atau menurunkan volume efek suara dan musik.

## Cara Penggunaan
1. Panggil `InitSoundEffects()` untuk memuat semua efek suara dan musik sebelum digunakan.
2. Gunakan fungsi pemutaran efek suara seperti `PlayButtonClick()` saat tombol ditekan.
3. Gunakan `PlayBackgroundMusic()` untuk memulai musik latar.
4. Gunakan `IncreaseVolume()` atau `DecreaseVolume()` untuk mengatur volume.
5. Panggil `UnloadSoundEffects()` sebelum program berakhir untuk membersihkan sumber daya audio.

Fitur ini dibuat menggunakan **Raylib** sebagai library audio untuk memproses dan memainkan suara dalam game.
