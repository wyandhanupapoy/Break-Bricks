#include "linkedlist_nyawa.h"

static Texture2D nyawaTexture;
static float nyawaSize = 8.0f;
static Vector2 basePosition = {10, 10};

void LoadNyawaTexture()
{
    nyawaTexture = LoadTexture("assets/heart.png");
}

void UnloadNyawaTexture()
{
    UnloadTexture(nyawaTexture);
}

void SetNyawaSize(float size)
{
    nyawaSize = size;
}

void SetNyawaPosition(float x, float y)
{
    basePosition = (Vector2){x, y};
}

void InitNyawaLinkedList(NodeNyawa **head, int jumlah)
{
    for (int i = 0; i < jumlah; i++)
    {
        NodeNyawa *newNode = (NodeNyawa *)malloc(sizeof(NodeNyawa));
        newNode->posisi = (Vector2){basePosition.x + i * (nyawaSize + 4), basePosition.y};
        newNode->size = nyawaSize;
        newNode->next = *head;
        *head = newNode;
    }
}

void KurangiNyawaLinkedList(NodeNyawa **head)
{
    if (*head == NULL)
        return;
    NodeNyawa *temp = *head;
    *head = (*head)->next;
    free(temp);
}

int AnyLivesLeftLinkedList(NodeNyawa *head)
{
    return head != NULL;
}

void DrawNyawaLinkedList(NodeNyawa *head)
{
    NodeNyawa *current = head;
    while (current)
    {
        DrawTextureEx(nyawaTexture, current->posisi, 0.0f, current->size / nyawaTexture.width, WHITE);
        current = current->next;
    }
}

void FreeNyawaLinkedList(NodeNyawa **head)
{
    NodeNyawa *current = *head;
    while (current)
    {
        NodeNyawa *temp = current;
        current = current->next;
        free(temp);
    }
    *head = NULL;
}
