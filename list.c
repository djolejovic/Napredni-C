#include "list.h"
#include <stdio.h>
#include <stdlib.h>

//креирање листе
Node* list_create(size_t start, size_t end)
{
    Node* node = (Node*)malloc(sizeof(Node));
    if (node != NULL)
    {
        node->block.start = start;
        node->block.end = end;
        node->next = NULL;
    }
    return node;
}

//убацивање листе, посебна провера за празну листу, ако је нова листа пре прве, и остатак низа
Node* list_insert(Node* head, size_t start, size_t end)
{
    Node* newNode = list_create(start, end);


    if (newNode == NULL)
    {
        return head;
    }

    if ((head == NULL) || (start < head->block.start))
    {
        newNode->next = head;
        return newNode;
    }

    Node* temp = head;
    while ((temp->next != NULL) && (temp->next->block.start < start))
    {
        temp = temp->next;
    }

    newNode->next = temp->next;
    temp->next = newNode;

    return head;
}

//уклањање листе, ако је празна, ако је на првом елементу хеад и уопштен случај
Node* list_remove(Node* head, Node* target)
{
    if (head == NULL)
    {
        return NULL;
    }

    if (head == target)
    {
        Node* nxt = head->next;
        free(head);
        return nxt;
    }

    Node* temp = head;
    while ((temp->next != NULL) && (temp->next != target))
    {
        temp = temp->next;
    }

    if (temp->next == target)
    {
        temp->next = target->next;
        free(target);
    }

    return head;
}

//ослободи целу листу
void list_free(Node* head)
{
    Node* temp = head;
    while (temp != NULL)
    {
        Node* nxt = temp->next;
        free(temp);
        temp = nxt;
    }
}

//исписивање листе
void list_print(const Node* head)
{
    const Node* temp = head;

    printf("Free blocks:\n");
    while (temp != NULL)
    {
        printf("[%zu – %zu]\n", temp->block.start, temp->block.end);
        temp = temp->next;
    }
}
