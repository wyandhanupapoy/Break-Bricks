#include "nyawa.h"
#include "layout.h"

static float nyawaPosX = 10.0f;
static float nyawaPosY = 10.0f;

void SetNyawaPosition(float x, float y)
{
    nyawaPosX = x;
    nyawaPosY = y;
}

void InitNyawa(Nyawa nyawa[NYAWA_BARIS][NYAWA_KOLOM], int totalNyawa)
{
    for (int i = 0; i < NYAWA_KOLOM; i++)
    {
        nyawa[0][i].rect.x = nyawaPosX + (NYAWA_WIDTH + NYAWA_SPACING) * i;
        nyawa[0][i].rect.y = nyawaPosY;
        nyawa[0][i].rect.width = NYAWA_WIDTH;
        nyawa[0][i].rect.height = NYAWA_HEIGHT;
        nyawa[0][i].aktif = i < totalNyawa;
    }
}

void DrawNyawa(Nyawa nyawa[NYAWA_BARIS][NYAWA_KOLOM])
{
    for (int i = 0; i < NYAWA_KOLOM; i++)
    {
        if (nyawa[0][i].aktif)
        {
            DrawRectangleRec(nyawa[0][i].rect, RED);
        }
    }
}

void KurangiNyawa(Nyawa nyawa[NYAWA_BARIS][NYAWA_KOLOM])
{
    for (int i = 0; i < NYAWA_KOLOM; i++)
    {
        if (nyawa[0][i].aktif)
        {
            nyawa[0][i].aktif = false;
            break;
        }
    }
}

bool AnyLivesLeft(Nyawa nyawa[NYAWA_BARIS][NYAWA_KOLOM])
{
    for (int i = 0; i < NYAWA_KOLOM; i++)
    {
        if (nyawa[0][i].aktif)
            return true;
    }
    return false;
}
