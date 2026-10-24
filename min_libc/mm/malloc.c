#include <internal/mm/mem_list.h>
#include <internal/types.h>
#include <internal/essentials.h>
#include <sys/mman.h>
#include <string.h>
#include <stdlib.h>

void *malloc(size_t size)
{
    if (size == 0) {
        return NULL;  // Return NULL for zero-sized allocation
    }

    // Calculate the total size needed, including the mem_list structure
    size_t total_size = size + sizeof(struct mem_list);

    // Allocate memory for the block
    struct mem_list *block = mmap(NULL, total_size, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);

    if (block == MAP_FAILED) {
        // Handle mmap failure
        return NULL;
    }

    // Set the 'start' and 'len' fields within the block
    block->start = (void *)block + sizeof(struct mem_list);
    block->len = size;

    // Add the block to the memory list
    if (mem_list_add(block->start, size) != 0) {
        // Handle mem_list_add failure
        munmap(block, total_size);
        return NULL;
    }

    // Check for NULL start field
    if (block->start == NULL) {
        // Handle NULL start field
        munmap(block, total_size);
        return NULL;
    }

    return block->start;
}


void *calloc(size_t nmemb, size_t size)
{
	/* TODO: Implement calloc(). */

    size_t total_size = nmemb * size;
    void *ptr = malloc(total_size);

    if (ptr) {
        memset(ptr, 0, total_size);

        return ptr;
    }

	return NULL;
}

void free(void *ptr) {
    if (ptr == NULL) {
        return;
    }

    struct mem_list *block = (struct mem_list *)((char *)ptr - sizeof(struct mem_list));

    int res = mem_list_del(block->start);

    if (res == 0)
        munmap(block, block->len + sizeof(struct mem_list));
}

void *realloc(void *ptr, size_t size)
{
	/* TODO: Implement realloc(). */

    if (size == 0) {
        free(ptr);  // If size is 0, it's equivalent to calling free
        return NULL;
    }

    if (ptr == NULL) {
        // If ptr is NULL, it's equivalent to calling malloc
        return malloc(size);
    }

    void *new_ptr = malloc(size);

    if (new_ptr) {
        // Copy data from the old block to the new block
        size_t old_size = *((size_t*)ptr - 1);
        size_t copy_size;

        if (size < old_size) {
            copy_size = size;
        } else {
            copy_size = old_size;
        }

        if (memcpy(new_ptr, ptr, copy_size) == NULL) {
            // Copy operation failed, free the new block and return NULL
            free(new_ptr);
            return NULL;
        }

        free(ptr);
        return new_ptr;
    }

    return NULL;
}

void *reallocarray(void *ptr, size_t nmemb, size_t size)
{
	/* TODO: Implement reallocarray(). */

    if (nmemb == 0 || size == 0) {
        // If either nmemb or size is 0, return a NULL pointer.
        free(ptr);
        return NULL;
    }

    // Calculate the total size of the requested memory
    size_t total_size = nmemb * size;

    // Use realloc to adjust the size of the existing memory block if ptr is not NULL
    void *new_ptr;

    if (ptr == NULL) {
        new_ptr = malloc(total_size);
    } else {
        new_ptr = realloc(ptr, total_size);
    }

    return new_ptr;
}

