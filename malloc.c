/*
** EPITECH PROJECT, 2022
** malloc
** File description:
** alloc
*/

#include "malloc.h"

static pthread_mutex_t malloc_mutex = PTHREAD_MUTEX_INITIALIZER;

void *malloc(size_t size)
{
    struct malloc_header *block = NULL;

    pthread_mutex_lock(&malloc_mutex);
    if (head == NULL) {
        head = allocate_block(size, NULL);
        pthread_mutex_unlock(&malloc_mutex);
        return head ? (char *)head + sizeof(struct malloc_header) : NULL;
    } else if (find_block(size, &block) == 0) {
        block = allocate_block(size, block);
        pthread_mutex_unlock(&malloc_mutex);
        return block ? (char *)block + sizeof(struct malloc_header) : NULL;
    } else {
        block->free = 0;
        pthread_mutex_unlock(&malloc_mutex);
        return (char *)block + sizeof(struct malloc_header);
    }
}

void free(void *ptr)
{
    struct malloc_header *current = NULL;

    if (ptr == NULL)
        return;
    pthread_mutex_lock(&malloc_mutex);
    current = (void *)((char *)ptr - sizeof(struct malloc_header));
    current->free = 1;
    pthread_mutex_unlock(&malloc_mutex);
}

void *realloc(void *ptr, size_t size)
{
    struct malloc_header *block = NULL;
    void *new_ptr = NULL;

    block = (void *)((char *)ptr - sizeof(struct malloc_header));
    if (ptr == NULL)
        return malloc(size);
    if (block->size >= size)
        return ptr;
    new_ptr = malloc(size);
    free(ptr);
    if (new_ptr == NULL)
        return NULL;
    pthread_mutex_lock(&malloc_mutex);
    memcpy(new_ptr, ptr, block->size);
    pthread_mutex_unlock(&malloc_mutex);
    return new_ptr;
}

void *calloc(size_t nmemb, size_t size)
{
    const size_t total_size = nmemb * size;
    void *ptr = malloc(total_size);

    if (ptr != NULL)
        memset(ptr, 0, total_size);
    return ptr;
}

void *reallocarray(void *ptr, size_t nmemb, size_t size)
{
    return realloc(ptr, nmemb * size);;
}
