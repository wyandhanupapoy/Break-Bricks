#include "nyawa.h"

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
void DrawNyawa(Nyawa nyawa[NYAWA_BARIS][NYAWA_KOLOM])
{
    for (int i = 0; i < NYAWA_BARIS; i++)
    {
        for (int j = 0; j < NYAWA_KOLOM; j++)
        {
            if (nyawa[i][j].aktif)
            {
                DrawRectangleRec(nyawa[i][j].rect, RED);          // Nyawa aktif berwarna merah
                DrawRectangleLinesEx(nyawa[i][j].rect, 2, BLACK); // Garis tepi hitam
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
