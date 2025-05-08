#include "linkedlist_nyawa.h"
#include "raylib.h"
#include <stdlib.h>

// Variabel global untuk gambar dan posisi nyawa
static Texture2D nyawaTexture;
static float nyawaSize = 32.0f;
static Vector2 basePosition = {800, 30};

// Load dan unload tekstur
void LoadNyawaTexture()
{
    nyawaTexture = LoadTexture("assets/images/heart.png");
}

void UnloadNyawaTexture()
{
    UnloadTexture(nyawaTexture);
}

// Set ukuran ikon hati
void SetNyawaSize(float size)
{
    nyawaSize = size;
}

// Set posisi awal gambar nyawa (kanan atas layar)
void SetNyawaPosition(float x, float y)
{
    basePosition = (Vector2){x, y};
}

// Inisialisasi nyawa sebagai linked list
void InitNyawaLinkedList(NodeNyawa **head, int jumlah)
{
    *head = NULL;
    for (int i = 0; i < jumlah; i++)
    {
        NodeNyawa *newNode = (NodeNyawa *)malloc(sizeof(NodeNyawa));
        newNode->next = *head;
        *head = newNode;
    }
}

// Kurangi 1 nyawa (hapus node paling depan)
void KurangiNyawaLinkedList(NodeNyawa **head)
{
    if (*head == NULL)
        return;

    NodeNyawa *temp = *head;
    *head = (*head)->next;
    free(temp);
}

// Cek apakah masih ada nyawa
bool AnyLivesLeftLinkedList(NodeNyawa *head)
{
    return head != NULL;
}

// Gambar semua nyawa sebagai ikon hati
void DrawNyawaLinkedList(NodeNyawa *head)
{
    NodeNyawa *current = head;
    int i = 0;
    while (current != NULL)
    {
        Vector2 position = {
            basePosition.x - i * (nyawaSize + 5),
            basePosition.y};
        float scale = nyawaSize / (float)nyawaTexture.height;
        DrawTextureEx(nyawaTexture, position, 0.0f, scale, WHITE);
        current = current->next;
        i++;
    }
}

// Bebaskan seluruh linked list nyawa
void FreeNyawaLinkedList(NodeNyawa **head)
{
    NodeNyawa *current = *head;
    while (current != NULL)
    {
        NodeNyawa *temp = current;
        current = current->next;
        free(temp);
    }
    *head = NULL;
}
