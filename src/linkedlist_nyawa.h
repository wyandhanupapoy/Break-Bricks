#ifndef LINKEDLIST_NYAWA_H
#define LINKEDLIST_NYAWA_H

#include "raylib.h"

// Struktur node untuk nyawa
typedef struct NodeNyawa
{
    struct NodeNyawa *next;
    Vector2 posisi; // Disiapkan jika ingin menggunakan posisi individual di masa depan
    float size;     // Disiapkan untuk ukuran nyawa
} NodeNyawa;

// Fungsi utama untuk sistem nyawa
void InitNyawaLinkedList(NodeNyawa **head, int jumlah);
void KurangiNyawaLinkedList(NodeNyawa **head);
bool AnyLivesLeftLinkedList(NodeNyawa *head);
void DrawNyawaLinkedList(NodeNyawa *head);
void FreeNyawaLinkedList(NodeNyawa **head);

// (Optional) Fungsi tambahan jika Anda menggunakan tekstur atau nyawa yang lebih kompleks
void LoadNyawaTexture();
void UnloadNyawaTexture();
void SetNyawaSize(float size);
void SetNyawaPosition(float x, float y);

#endif
