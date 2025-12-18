#ifndef MEM_H
#define MEM_H

#include <stddef.h>
#include "list.h"

/* Ove funkcije menjaju listu, pa ne sme const */
Node* mem_init(size_t totalSize);
Node* mem_alloc(Node* head, size_t address, size_t size);
Node* mem_free(Node* head, size_t start, size_t size);

#endif

