#include "block.h"
#include "level.h" 

// Fungsi untuk menginisialisasi blok berdasarkan level yang dipilih
void InitBlocks(Block blocks[BLOCK_ROWS][BLOCK_COLS], int level) {
    InitLevelBlocks(blocks, level);  // Panggil fungsi dari level.c untuk menentukan warna dan status blok
}

// Fungsi untuk menggambar semua blok yang masih aktif di layar
void DrawBlocks(Block blocks[BLOCK_ROWS][BLOCK_COLS]) {
    for (int i = 0; i < BLOCK_ROWS; i++) {
        for (int j = 0; j < BLOCK_COLS; j++) {
            if (blocks[i][j].active) {  // Hanya gambar blok yang masih aktif
                DrawRectangleRec(blocks[i][j].rect, blocks[i][j].color);  // Gambar blok dengan warna yang ditentukan
                DrawRectangleLinesEx(blocks[i][j].rect, 2, BLACK);  // Tambahkan garis tepi hitam agar lebih terlihat
            }
        }
    }
}

// Fungsi untuk mengecek apakah bola bertabrakan dengan sebuah blok
bool CheckBallBlockCollision(Vector2 ballPosition, float ballRadius, Rectangle blockRect) {
    return CheckCollisionCircleRec(ballPosition, ballRadius, blockRect);  // Gunakan fungsi bawaan Raylib untuk cek tabrakan
}

// Fungsi untuk mengecek apakah semua blok sudah dihancurkan
bool AllBlocksDestroyed(Block blocks[BLOCK_ROWS][BLOCK_COLS]) {
    for (int i = 0; i < BLOCK_ROWS; i++) {
        for (int j = 0; j < BLOCK_COLS; j++) {
            if (blocks[i][j].active) return false;  // Jika masih ada blok aktif, maka belum semua hancur
        }
    }
    return true;  // Jika tidak ada blok aktif, maka semua sudah dihancurkan
}
