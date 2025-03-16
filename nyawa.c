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

void DrawNyawa(Nyawa nyawa[NYAWA_BARIS][NYAWA_KOLOM]) {
    for (int i = 0; i < NYAWA_KOLOM; i++) {
        if (nyawa[0][i].aktif) {
            DrawRectangleRec(nyawa[0][i].rect, GREEN);
        }
    }
}

void KurangiNyawa(Nyawa nyawa[NYAWA_BARIS][NYAWA_KOLOM]) {
    for (int i = 0; i < NYAWA_KOLOM; i++) {
        if (nyawa[0][i].aktif) {
            nyawa[0][i].aktif = false; // Mengurangi nyawa
            break;
        }
    }
}

bool AnyLivesLeft(Nyawa nyawa[NYAWA_BARIS][NYAWA_KOLOM]) {
    for (int i = 0; i < NYAWA_KOLOM; i++) {
        if (nyawa[0][i].aktif) return true;
    }
    return false;
}