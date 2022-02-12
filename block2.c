/*
** EPITECH PROJECT, 2022
** block
** File description:
** block
*/

#include "malloc.h"

static void best_fit(size_t size, struct malloc_header **best,
        struct malloc_header *current)
{
    if (current->free && current->size >= size)
        if (*best == NULL || (*best)->size - size > current->size - size)
            *best = current;
}

int find_block(size_t size, struct malloc_header **header)
{
    struct malloc_header *block = head;
    struct malloc_header *best = NULL;

    for (; block->next; block = block->next)
        best_fit(size, &best, block);
    best_fit(size, &best, block);
    if (best == NULL) {
        *header = block;
        return 0;
    }
    *header = best;
    return 1;
}
