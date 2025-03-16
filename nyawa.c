#include "Brata.h"

// Fungsi untuk inisialisasi nyawa sesuai jumlah total nyawa yang diberikan
void InitNyawa(Nyawa nyawa[NYAWA_BARIS][NYAWA_KOLOM], int totalNyawa)
{
    int nyawaTerpasang = 0;

    for (int i = 0; i < NYAWA_BARIS; i++)
    {
        for (int j = 0; j < NYAWA_KOLOM; j++)
        {
            nyawa[i][j].rect.x = 20 + j * (NYAWA_WIDTH + NYAWA_SPACING);  // posisi x mulai dari 20 pixel ke kanan
            nyawa[i][j].rect.y = 20 + i * (NYAWA_HEIGHT + NYAWA_SPACING); // posisi y mulai dari 20 pixel ke bawah
            nyawa[i][j].rect.width = NYAWA_WIDTH;
            nyawa[i][j].rect.height = NYAWA_HEIGHT;

            // Aktifkan nyawa sesuai jumlah total nyawa
            if (nyawaTerpasang < totalNyawa)
            {
                nyawa[i][j].aktif = true;
                nyawaTerpasang++;
            }
            else
            {
                nyawa[i][j].aktif = false;
            }
        }
    }
}

// Fungsi untuk menggambar nyawa ke layar
// Fungsi untuk menggambar nyawa ke layar dalam bentuk hati
void DrawNyawa(Nyawa nyawa[NYAWA_BARIS][NYAWA_KOLOM])
{
    for (int i = 0; i < NYAWA_BARIS; i++)
    {
        for (int j = 0; j < NYAWA_KOLOM; j++)
        {
            if (nyawa[i][j].aktif)
            {
                // Ambil posisi tengah dari rect buat titik tengah gambar hati
                float centerX = nyawa[i][j].rect.x + nyawa[i][j].rect.width / 2;
                float centerY = nyawa[i][j].rect.y + nyawa[i][j].rect.height / 2;

                float size = nyawa[i][j].rect.width / 2;

                // Gambar dua lingkaran buat bagian atas hati
                DrawCircle(centerX - size / 2, centerY - size / 3, size / 2, RED);
                DrawCircle(centerX + size / 2, centerY - size / 3, size / 2, RED);

                // Gambar segitiga buat bagian bawah hati
                Vector2 point1 = {centerX - size - 1, centerY - size / 5};
                Vector2 point2 = {centerX + size + 1, centerY - size / 5};
                Vector2 point3 = {centerX, centerY + size};

                DrawTriangle(point1, point2, point3, RED);

                // Optional: Tambah outline kalau mau
                DrawCircleLines(centerX - size / 2, centerY - size / 3, size / 2, BLACK);
                DrawCircleLines(centerX + size / 2, centerY - size / 3, size / 2, BLACK);
                DrawLineEx(point1, point2, 2, BLACK);
                DrawLineEx(point2, point3, 2, BLACK);
                DrawLineEx(point3, point1, 2, BLACK);
            }
        }
    }
}

// Fungsi untuk mengurangi 1 nyawa (misalnya saat bola jatuh)
// Akan mematikan nyawa dari paling kanan ke kiri
void KurangiNyawa(Nyawa nyawa[NYAWA_BARIS][NYAWA_KOLOM])
{
    for (int i = NYAWA_BARIS - 1; i >= 0; i--)
    {
        for (int j = NYAWA_KOLOM - 1; j >= 0; j--)
        {
            if (nyawa[i][j].aktif)
            {
                nyawa[i][j].aktif = false; // Matikan nyawa
                return;                    // Hanya kurangi satu nyawa, lalu keluar fungsi
            }
        }
    }
}
