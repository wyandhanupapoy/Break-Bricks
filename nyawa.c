#include "nyawa.h"

void InitNyawa(Nyawa nyawa[NYAWA_BARIS][NYAWA_KOLOM], int totalNyawa) {
    for (int i = 0; i < NYAWA_KOLOM; i++) {
        nyawa[0][i].rect.x = 10 + (NYAWA_WIDTH + NYAWA_SPACING) * i;
        nyawa[0][i].rect.y = 10;
        nyawa[0][i].rect.width = NYAWA_WIDTH;
        nyawa[0][i].rect.height = NYAWA_HEIGHT;
        nyawa[0][i].aktif = i < totalNyawa;
    }
}
