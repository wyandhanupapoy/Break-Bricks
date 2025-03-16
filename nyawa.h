#ifndef NYAWA_H
#define NYAWA_H

#include <raylib.h>

#define NYAWA_BARIS 1
#define NYAWA_KOLOM 5

#define NYAWA_WIDTH 30
#define NYAWA_HEIGHT 30
#define NYAWA_SPACING 10

typedef struct {
    Rectangle rect;
    bool aktif;
} Nyawa;

void InitNyawa(Nyawa nyawa[NYAWA_BARIS][NYAWA_KOLOM], int totalNyawa);
void DrawNyawa(Nyawa nyawa[NYAWA_BARIS][NYAWA_KOLOM]);
void KurangiNyawa(Nyawa nyawa[NYAWA_BARIS][NYAWA_KOLOM]);
bool AnyLivesLeft(Nyawa nyawa[NYAWA_BARIS][NYAWA_KOLOM]);

#endif // NYAWA_H