#include "LinkedList-Level.h"
#include "LinkedList-Block.h"
#include <stdlib.h>
#include <time.h>

// Fungsi untuk menambah blok di akhir linked list
void InsertLast(LinkedList *list, Block newBlock) {
    NodeBlock *newNode = (NodeBlock *)malloc(sizeof(NodeBlock));
    newNode->data = newBlock;
    newNode->next = NULL;

    if (list->tail == NULL) {
        list->head = newNode;
        list->tail = newNode;
    } else {
        list->tail->next = newNode;
        list->tail = newNode;
    }
}

// Fungsi untuk menginisialisasi blok-blok dalam permainan berdasarkan level yang dipilih
void InitLevelBlocks(LinkedList *blockList, int level) {
    srand(time(NULL)); // Seed untuk angka acak

    for (int i = 0; i < BLOCK_ROWS; i++) {
        for (int j = 0; j < BLOCK_COLS; j++) {
            Block newBlock;
            newBlock.rect.x = j * (BLOCK_WIDTH + BLOCK_SPACING) + 15;
            newBlock.rect.y = i * (BLOCK_HEIGHT + BLOCK_SPACING) + 70;
            newBlock.rect.width = BLOCK_WIDTH;
            newBlock.rect.height = BLOCK_HEIGHT;
            newBlock.active = true;

            // Nilai default untuk hitPoints dan color:
            newBlock.hitPoints = 1;
            newBlock.color = (Color){200, 200, 200, 255}; // Contoh: Abu-abu sebagai default

            if (level == 1) {
                newBlock.hitPoints = 1;
                newBlock.color = (Color){255, 204, 77, 255}; // Kuning Retro
            }
            else if (level == 2) {
                int randomType = rand() % 2;
                if (randomType == 0) {
                    newBlock.hitPoints = 1;
                    newBlock.color = (Color){255, 204, 77, 255}; // Kuning Retro
                } else {
                    newBlock.hitPoints = 2;
                    newBlock.color = (Color){255, 140, 26, 255}; // Orange Retro
                }
            }
            else if (level == 3) {
                int randomType = rand() % 3;
                if (randomType == 0) {
                    newBlock.hitPoints = 1;
                    newBlock.color = (Color){255, 204, 77, 255}; // Kuning Retro
                } else if (randomType == 1) {
                    newBlock.hitPoints = 2;
                    newBlock.color = (Color){255, 140, 26, 255}; // Orange Retro
                } else {
                    newBlock.hitPoints = 3;
                    newBlock.color = (Color){140, 90, 200, 255}; // Ungu Retro
                }
            }
            else {
                TraceLog(LOG_WARNING, "Level tidak dikenal: %d, menggunakan default block.", level);
                // Default sudah diatur di atas
             }

            InsertLast(blockList, newBlock);
        }
    }
}

// Atur level
void SetLevel(LinkedList *blockList, int level) {
    ClearList(blockList);           // Hapus semua blok sebelumnya
    InitLevelBlocks(blockList, level); // Inisialisasi ulang blok sesuai level
}
