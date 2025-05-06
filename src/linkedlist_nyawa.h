#ifndef LINKEDLIST_NYAWA_H
#define LINKEDLIST_NYAWA_H

#include "raylib.h"

typedef struct NodeNyawa
{
    struct NodeNyawa *next;
    Vector2 posisi;
    float size;
} NodeNyawa;

// Fungsi utama
void InitNyawaLinkedList(NodeNyawa **head, int jumlah);
void KurangiNyawaLinkedList(NodeNyawa **head);
int AnyLivesLeftLinkedList(NodeNyawa *head);
void DrawNyawaLinkedList(NodeNyawa *head);
void FreeNyawaLinkedList(NodeNyawa **head);

// Tekstur dan ukuran
void LoadNyawaTexture();
void UnloadNyawaTexture();
void SetNyawaSize(float size);
void SetNyawaPosition(float x, float y);

#endif
