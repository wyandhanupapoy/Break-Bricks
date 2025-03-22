#include "nyawa.h"
#include "raylib.h"

static Texture2D heartTexture;  // Gambar nyawa
static float nyawaPosX = 850;   // Posisi default X
static float nyawaPosY = 20;    // Posisi default Y
static float nyawaScale = (float)DEFAULT_NYAWA_SIZE / 100.0f;  // Skala nyawa
static Texture2D nyawaTexture;

// 🔹 Memuat gambar nyawa
void LoadNyawaTexture()
{
    nyawaTexture = LoadTexture("assets/images/heart.png");
}

// 🔹 Membersihkan gambar nyawa dari memori
void UnloadNyawaTexture()
{
    UnloadTexture(nyawaTexture);
}

// 🔹 Mengatur posisi nyawa
void SetNyawaPosition(float x, float y)
{
    nyawaPosX = x;
    nyawaPosY = y;
}

// 🔹 Mengatur ukuran nyawa
void SetNyawaSize(float size)
{
    nyawaScale = size / 100.0f;
}

// 🔹 Inisialisasi jumlah nyawa
void InitNyawa(Nyawa nyawa[NYAWA_BARIS][NYAWA_KOLOM], int totalNyawa)
{
    for (int i = 0; i < NYAWA_KOLOM; i++)
    {
        nyawa[0][i].aktif = (i < totalNyawa);
    }
}

// 🔹 Kurangi nyawa jika kehilangan bola
void KurangiNyawa(Nyawa nyawa[NYAWA_BARIS][NYAWA_KOLOM])
{
    for (int i = NYAWA_KOLOM - 1; i >= 0; i--)
    {
        if (nyawa[0][i].aktif)
        {
            nyawa[0][i].aktif = false;
            break;
        }
    }
}

// 🔹 Cek apakah masih ada nyawa tersisa
bool AnyLivesLeft(Nyawa nyawa[NYAWA_BARIS][NYAWA_KOLOM])
{
    for (int i = 0; i < NYAWA_KOLOM; i++)
    {
        if (nyawa[0][i].aktif)
        {
            return true;
        }
    }
    return false;
}

// 🔹 Gambar nyawa dengan ukuran dinamis & berjejer dari kanan ke kiri
void DrawNyawa(Nyawa nyawa[NYAWA_BARIS][NYAWA_KOLOM])
{
    for (int i = 0; i < NYAWA_KOLOM; i++)
    {
        if (nyawa[0][i].aktif)
        {
            float posX = nyawaPosX - (i * ((nyawaTexture.width * nyawaScale) + NYAWA_SPACING));
            float posY = nyawaPosY;
            DrawTextureEx(nyawaTexture, (Vector2){posX, posY}, 0.0f, nyawaScale, WHITE);
        }
    }
}
