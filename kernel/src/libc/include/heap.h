#ifndef HEAP_H
#define HEAP_H

#include <stdint.h>
#include <stddef.h>

void init_memory_pool();
void *malloc(size_t size);
void free(void *ptr);
void *realloc(void *ptr, size_t size);

typedef struct block_header {
    size_t size;
    struct block_header *next;
    int free;
} block_header_t;

#endif