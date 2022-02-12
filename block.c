/*
** EPITECH PROJECT, 2022
** Alloc
** File description:
** Block
*/

#include "malloc.h"
#include <errno.h>

struct malloc_header *head = NULL;

static size_t page_size_required(size_t *size, size_t *rest)
{
    const size_t pagesize = getpagesize() * 2;
    const size_t aligned =
        1 << (32 - __builtin_clz(*size + sizeof(struct malloc_header) - 1));
    size_t npage = 1;

    for (; pagesize * npage < aligned; npage++);
    *size = aligned - sizeof(struct malloc_header);
    *rest = pagesize * npage - aligned;
    return npage * pagesize;
}

static struct malloc_header *resize_heap(size_t size)
{
    struct malloc_header *block = sbrk(size);

    return block == (void *)-1 ? NULL : block;
}

static struct malloc_header *make_default_block(size_t size,
        struct malloc_header *header)
{
    header->size = size;
    header->free = 0;
    header->next = NULL;
    return header;
}

struct malloc_header *allocate_block(size_t size, struct malloc_header *header)
{
    static size_t left_space = 0;
    size_t tmp = 0;
    struct malloc_header *block = NULL;
    const size_t aligned_size = page_size_required(&size, &tmp);

    if (header == NULL) {
        block = resize_heap(aligned_size);
        if (block == NULL)
            return NULL;
        left_space = tmp;
        return make_default_block(size, block);
    } else if (left_space < size + sizeof(struct malloc_header)) {
        if (resize_heap(aligned_size) == NULL)
            return NULL;
        left_space += aligned_size;
    }
    left_space -= size + sizeof(struct malloc_header);
    header->next = (void *)((char *)header + header->size +
            sizeof(struct malloc_header));
    return make_default_block(size, header->next);
}
