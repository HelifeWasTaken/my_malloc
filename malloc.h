/*
** EPITECH PROJECT, 2022
** Malloc
** File description:
** Allocater
*/

#ifndef MY_MALLOC_H
    #define MY_MALLOC_H

    #include <stddef.h>
    #include <string.h>
    #include <stdlib.h>
    #include <unistd.h>
    #include <stdio.h>
    #include <stdarg.h>
    #include <pthread.h>

    void *malloc(size_t size);
    void free(void *ptr);
    void *realloc(void *ptr, size_t size);
    void *calloc(size_t nmemb, size_t size);
    void *reallocarray(void *ptr, size_t nmemb, size_t size);

    struct malloc_header {
        struct malloc_header *next;
        size_t size;
        char free;
    };

    extern struct malloc_header *head;

    struct malloc_header *allocate_block(size_t size,
            struct malloc_header *header);
    int find_block(size_t size, struct malloc_header **header);

#endif
