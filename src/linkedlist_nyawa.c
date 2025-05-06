#include "linkedlist_nyawa.h"
#include "raylib.h"
#include <stdlib.h>

void InitNyawaLinkedList(NodeNyawa **head, int nyawa)
{
    *head = NULL;
    for (int i = 0; i < nyawa; i++)
    {
        NodeNyawa *newNode = (NodeNyawa *)malloc(sizeof(NodeNyawa));
        newNode->next = *head;
        *head = newNode;
    }
}

void KurangiNyawaLinkedList(NodeNyawa **head)
{
    if (*head != NULL)
    {
        NodeNyawa *temp = *head;
        *head = (*head)->next;
        free(temp);
    }
}

int AnyLivesLeftLinkedList(NodeNyawa *head)
{
    return head != NULL;
}

void DrawNyawaLinkedList(NodeNyawa *head)
{
    int x = 20;
    NodeNyawa *current = head;
    while (current != NULL)
    {
        DrawCircle(x, 20, 10, RED);
        x += 25;
        current = current->next;
    }
}

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
