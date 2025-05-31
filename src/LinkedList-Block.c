#include "LinkedList-Block.h"
#include <stdlib.h>

// 🔹 Fungsi untuk menginisialisasi linked list
void InitList(LinkedList *list) {
    list->head = NULL;
    list->tail = NULL;
}

// 🔹 Fungsi untuk menambahkan blok ke dalam linked list
void AddBlock(LinkedList *list, Block block) {
    NodeBlock *newNode = (NodeBlock *)malloc(sizeof(NodeBlock));
    newNode->data = block;
    newNode->next = NULL;

    if (list->tail != NULL) {
        list->tail->next = newNode; // Menambahkan di akhir list
    } else {
        list->head = newNode; // Jika list kosong, blok menjadi node pertama
    }

    list->tail = newNode; // Memperbarui tail
}

// 🔹 Fungsi untuk membersihkan linked list
void ClearList(LinkedList *list) {
    NodeBlock *current = list->head;
    while (current != NULL) {
        NodeBlock *next = current->next;
        free(current);  // Menghapus node
        current = next;
    }
    list->head = NULL;
    list->tail = NULL;
}

// 🔹 Update kondisi blok saat terkena bola
void UpdateBlockState(NodeBlock *node) {
    Block *block = &node->data;
    if (!block->active) return;

    block->hitPoints--; // Kurangi HP blok
    if (block->hitPoints <= 0) {
        block->active = false;
    } else {
        // 🔹 Update warna blok sesuai sisa HP
        if (block->hitPoints == 2) {
            block->color = (Color){255, 140, 26, 255}; // Orange Retro
        } else if (block->hitPoints == 1) {
            block->color = (Color){255, 204, 77, 255}; // Kuning Retro
        }
    }
}

// 🔹 Gambar semua blok
void DrawBlocks(LinkedList *blockList) {
    NodeBlock *current = blockList->head;
    while (current != NULL) {
        Block *block = &current->data;
        if (block->active) {
            DrawRectangleRec(block->rect, block->color);
            DrawRectangleLinesEx(block->rect, 2, BLACK);
        }
        current = current->next;
    }
}

// 🔹 Cek tabrakan bola dengan blok
bool CheckBallBlockCollision(Vector2 ballPosition, float ballRadius, Rectangle blockRect) {
    return CheckCollisionCircleRec(ballPosition, ballRadius, blockRect);
}

// 🔹 Cek apakah semua blok sudah hancur
bool AllBlocksDestroyed(LinkedList *blockList) {
    NodeBlock *current = blockList->head;
    while (current != NULL) {
        if (current->data.active) return false;
        current = current->next;
    }
    return true;
}
