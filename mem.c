#include "mem.h"
#include <stdio.h>

//иницијализовање
Node* mem_init(size_t totalSize)
{
    return list_create(0U, totalSize - 1U);
}

//алоцирање меморије, тражимо жељени блок који одговара,
//цепамо га на евентуално 2 дела и враћамо потребне делове
Node* mem_alloc(Node* head, size_t address, size_t size)
{
    const Node* t = head;

    while (t != NULL)
    {
        if ((t->block.start <= address) &&
            (t->block.end >= (address + size - 1U)))
        {
            size_t oldStart = t->block.start;
            size_t oldEnd = t->block.end;

            head = list_remove(head, t);

            if (oldStart < address)
            {
                head = list_insert(head, oldStart, address - 1U);
            }

            if ((address + size) <= oldEnd)
            {
                head = list_insert(head, address + size, oldEnd);
            }

            return head;
        }
        t = t->next;
    }

    (void)printf("Greska: ne postoji slobodan blok za trazenu adresu.\n");
    return head;
}

//ослобађање меморије и спајање суседних блокова
Node* mem_free(Node* head, size_t start, size_t size)
{

    size_t end = start + size - 1U;
    head = list_insert(head, start, end);

    Node* t = head;
    while ((t != NULL) && (t->next != NULL))
    {
        if (t->block.end + 1U == t->next->block.start)
        {
            t->block.end = t->next->block.end;
            head = list_remove(head, t->next);
        }
        else
        {
            t = t->next;
        }
    }

    return head;
}
