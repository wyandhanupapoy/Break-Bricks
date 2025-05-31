/* Nama Pembuat: Muhammad Brata Hadinata
    Nama Fitur: nyawa.c
    Deskripsi: Mengelola sistem nyawa dalam game secara dinamis menggunakan hitungan integer.
               Menampilkan ikon nyawa di layar, menangani pengurangan nyawa,
               dan memuat/menghapus tekstur ikon nyawa. */

               #include "nyawa.h"
               // #include "layout.h" // Tidak lagi secara langsung dibutuhkan di sini jika posisi dari main.c
               
               static int currentLives = 0; // Jumlah nyawa saat ini
               static Texture2D lifeTexture; // Tekstur untuk ikon nyawa
               static float lifeIconPosX = 0;
               static float lifeIconPosY = 0;
               static float lifeIconScale = (float)DEFAULT_LIFE_ICON_SIZE / 100.0f;
               
               // 🔹 Memuat gambar ikon nyawa
               void LoadLifeTexture() // Nama baru: LoadLifeTexture
               {
                   lifeTexture = LoadTexture("assets/images/heart.png"); // Path tekstur tetap sama
               }
               
               // 🔹 Membersihkan gambar ikon nyawa dari memori
               void UnloadLifeTexture() // Nama baru: UnloadLifeTexture
               {
                   UnloadTexture(lifeTexture);
               }
               
               // 🔹 Mengatur posisi awal untuk tampilan ikon nyawa (pojok kanan atas ikon pertama)
               void SetLivesDisplayPosition(float x, float y) // Nama baru: SetLivesDisplayPosition
               {
                   lifeIconPosX = x;
                   lifeIconPosY = y;
               }
               
               // 🔹 Mengatur ukuran ikon nyawa
               void SetLifeIconSize(float size) // Nama baru: SetLifeIconSize
               {
                   lifeIconScale = size / 100.0f;
               }
               
               // 🔹 Inisialisasi jumlah nyawa
               void InitLivesSystem(int initialLives) // Nama baru: InitLivesSystem
               {
                   currentLives = initialLives;
                   if (currentLives < 0) {
                       currentLives = 0;
                   }
               }
               
               // 🔹 Kurangi satu nyawa
               void DecreaseLife(void) // Nama baru: DecreaseLife
               {
                   if (currentLives > 0)
                   {
                       currentLives--;
                   }
               }
               
               // 🔹 Cek apakah pemain masih memiliki nyawa
               bool HasLivesLeft(void) // Nama baru: HasLivesLeft
               {
                   return currentLives > 0;
               }
               
               // 🔹 Gambar ikon nyawa berdasarkan jumlah nyawa saat ini
               // Ikon digambar berjejer dari kanan ke kiri
               void DrawLives(void) // Nama baru: DrawLives
               {
                   int livesToDraw = currentLives;
                   if (livesToDraw > MAX_DISPLAY_LIVES) { // Batasi jumlah ikon yang digambar jika nyawa > MAX_DISPLAY_LIVES
                       livesToDraw = MAX_DISPLAY_LIVES;
                   }
               
                   for (int i = 0; i < livesToDraw; i++)
                   {
                       // Logika menggambar dari kanan ke kiri
                       // Ikon ke-0 (paling kanan) ada di lifeIconPosX
                       // Ikon ke-1 ada di sebelah kirinya, dst.
                       float posX = lifeIconPosX - (i * ((lifeTexture.width * lifeIconScale) + LIFE_ICON_SPACING));
                       float posY = lifeIconPosY;
                       DrawTextureEx(lifeTexture, (Vector2){posX, posY}, 0.0f, lifeIconScale, WHITE);
                   }
               }