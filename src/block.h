//Nama Pembuat: Nezya Zulfa Fauziah
//Nama Fitur: Block
// Deskripsi: Fitur linked list ini mengelola blok-blok dalam game Break Bricks secara dinamis.
// Termasuk inisialisasi, penambahan, penghapusan, serta pembaruan kondisi blok saat terkena bola.
// Blok akan berubah warna sesuai sisa HP dan hilang jika HP habis.
// Sistem ini juga menangani gambar blok, deteksi tabrakan, dan pengecekan apakah semua blok telah hancur.

#ifndef LINKEDLIST_BLOCK_H
#define LINKEDLIST_BLOCK_H

#include "raylib.h"
#include <stdbool.h>

#define BLOCK_ROWS 5  // or any number that suits your design
#define BLOCK_COLS 10
#define BLOCK_WIDTH 75
#define BLOCK_HEIGHT 25
#define BLOCK_SPACING 5

// 🔹 Struktur Block
typedef struct Block {
    Rectangle rect;
    Color color;
    int hitPoints;
    bool active;
} Block;

// 🔹 Node dalam Linked List
typedef struct NodeBlock {
    Block data;
    struct NodeBlock *next;
} NodeBlock;

// 🔹 Struktur Linked List
typedef struct {
    NodeBlock *head;
    NodeBlock *tail;
} LinkedList;

// 🔹 Fungsi-fungsi Linked List Block
void InitList(LinkedList *list);
void AddBlock(LinkedList *list, Block block);
void ClearList(LinkedList *list);
void UpdateBlockState(NodeBlock *node);
void DrawBlocks(LinkedList *blockList);
bool CheckBallBlockCollision(Vector2 ballPosition, float ballRadius, Rectangle blockRect);
bool AllBlocksDestroyed(LinkedList *blockList);

#endif // LINKEDLIST_BLOCK_H
