#ifndef LIST_H
#define LIST_H

#include <stddef.h>

//једноструко спрегнута листа
typedef struct {
    size_t start;
    size_t end;
} Block;

typedef struct Node {
    Block block;
    struct Node* next;
} Node;

//фје листе
Node* list_create(size_t start, size_t end);
Node* list_insert(Node* head, size_t start, size_t end);
Node* list_remove(Node* head, Node* target);
void list_print(const Node* head);
void list_free(Node* head);

#endif
