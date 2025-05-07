//Nama Pembuat: Nezya Zulfa Fauziah  
//Nama Fitur: Level  
//Deskripsi: Fitur level menentukan tingkat kesulitan permainan dengan membedakan ketahanan blok berdasarkan warna. **Level 1** hanya memiliki blok **kuning** (1 ketahanan). **Level 2** menambahkan blok **oranye** (2 ketahanan), yang berubah menjadi kuning sebelum hancur. **Level 3** menambah blok **ungu** (3 ketahanan), yang berubah menjadi oranye, lalu kuning sebelum hancur. Fitur ini memberikan variasi dan tantangan bagi pemain sesuai level yang dipilih.

#include "level.h"
#include "block.h"
#include <stdlib.h> // Untuk fungsi `rand()`
#include <time.h>   // Untuk seeding angka acak

//menginisialisasi blok-blok dalam permainan berdasarkan level yang dipilih
void InitLevelBlocks(Block blocks[BLOCK_ROWS][BLOCK_COLS], int level) {
    srand(time(NULL)); // Seed untuk angka acak berdasarkan waktu saat ini

    for (int i = 0; i < BLOCK_ROWS; i++) {
        for (int j = 0; j < BLOCK_COLS; j++) {
            // Mengatur posisi dan ukuran setiap blok
            blocks[i][j].rect.x = j * (BLOCK_WIDTH + BLOCK_SPACING) + 15;
            blocks[i][j].rect.y = i * (BLOCK_HEIGHT + BLOCK_SPACING) + 70;
            blocks[i][j].rect.width = BLOCK_WIDTH;
            blocks[i][j].rect.height = BLOCK_HEIGHT;
            blocks[i][j].active = true; // Blok aktif secara default

            // Menentukan warna dan hitPoints blok berdasarkan level permainan
            if (level == 1) {
                blocks[i][j].hitPoints = 1;
                blocks[i][j].color = (Color){255, 204, 77, 255}; // Kuning Retro
            }
            else if (level == 2) {
                int randomType = rand() % 2; // Nilai acak 0 atau 1
                if (randomType == 0) {
                    blocks[i][j].hitPoints = 1;
                    blocks[i][j].color = (Color){255, 204, 77, 255}; // Kuning Retro
                } else {
                    blocks[i][j].hitPoints = 2;
                    blocks[i][j].color = (Color){255, 140, 26, 255}; // Orange Retro
                }
            }
            else if (level == 3) {
                int randomType = rand() % 3; // Nilai acak 0 - 2 (Kuning, Orange, Ungu)
                if (randomType == 0) {
                    blocks[i][j].hitPoints = 1;
                    blocks[i][j].color = (Color){255, 204, 77, 255}; // Kuning Retro
                } else if (randomType == 1) {
                    blocks[i][j].hitPoints = 2;
                    blocks[i][j].color = (Color){255, 140, 26, 255}; // Orange Retro
                } else {
                    blocks[i][j].hitPoints = 3;
                    blocks[i][j].color = (Color){140, 90, 200, 255}; // Ungu Retro
                }
            }
        }
    }
}

//Atur Level
void SetLevel(Block blocks[BLOCK_ROWS][BLOCK_COLS], int level) {
    InitLevelBlocks(blocks, level); // Memanggil fungsi untuk menginisialisasi blok berdasarkan level
}