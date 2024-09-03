#include "../../libc/include/heap.h"
#include "../../libc/include/debug.h"

// Pointer to the start of the free list
static block_header_t *free_list = NULL;

#define MEMORY_POOL_SIZE 1024 * 1024 * 600 // 1 MB for example

static uint8_t memory_pool[MEMORY_POOL_SIZE];

void init_memory_pool() {
    free_list = (block_header_t *)memory_pool;
    free_list->size = MEMORY_POOL_SIZE - sizeof(block_header_t);
    free_list->next = NULL;
    free_list->free = 1;
}

void *malloc(size_t size) {
    block_header_t *current = free_list;
    block_header_t *prev = NULL;

    // Align size to the nearest multiple of 8
    size = (size + 7) & ~7;

    while (current) {
        if (current->free && current->size >= size) {
            // If the block is too large, split it
            if (current->size > size + sizeof(block_header_t)) {
                block_header_t *new_block = (block_header_t *)((uint8_t *)current + sizeof(block_header_t) + size);
                new_block->size = current->size - size - sizeof(block_header_t);
                new_block->next = current->next;
                new_block->free = 1;

                current->size = size;
                current->next = new_block;
            }

            current->free = 0;
            return (void *)((uint8_t *)current + sizeof(block_header_t));
        }

        prev = current;
        current = current->next;
    }

    // No suitable block found
    return NULL;
}

void free(void *ptr) {
    if (!ptr) {
        return;
    }

    block_header_t *block = (block_header_t *)((uint8_t *)ptr - sizeof(block_header_t));
    block->free = 1;

    // Coalesce adjacent free blocks
    block_header_t *current = free_list;
    while (current) {
        if (current->free && current->next && current->next->free) {
            current->size += current->next->size + sizeof(block_header_t);
            current->next = current->next->next;
        }
        current = current->next;
    }
}

void *realloc(void *ptr, size_t size) {
    // If size is zero, free the memory and return NULL
    if (size == 0) {
        free(ptr);
        return NULL;
    }

    // If ptr is NULL, simply use malloc
    if (ptr == NULL) {
        return malloc(size);
    }

    // Allocate new memory block
    void *new_ptr = malloc(size);
    if (new_ptr == NULL) {
        // malloc failed
        return NULL;
    }

    // Get the old block header and size
    block_header_t *old_block = (block_header_t *)((uint8_t *)ptr - sizeof(block_header_t));
    size_t old_size = old_block->size;

    // Copy the smaller of the old and new sizes
    if (size < old_size) {
        memcpy(new_ptr, ptr, size);
    } else {
        memcpy(new_ptr, ptr, old_size);
    }

    // Free the old memory block
    free(ptr);

    return new_ptr;
}