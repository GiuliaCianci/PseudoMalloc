#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <unistd.h>

#define PAGE_SIZE 4096 // Assuming a page size of 4KB
#define SMALL_THRESHOLD (PAGE_SIZE / 4)
#define SMALL_BITMAP_SIZE (1024 * 1024) // 1 MB
#define BLOCK_SIZE 16 // Example block size for the buddy allocator

int main() {
    // Example usage
    void* small_ptr = pseudo_malloc(100); // Small allocation
    printf("Small pointer: %p\n", small_ptr);
    
    void* large_ptr = pseudo_malloc(5000); // Large allocation
    printf("Large pointer: %p\n", large_ptr);

    pseudo_free(small_ptr); // Free small allocation
    pseudo_free(large_ptr); // Free large allocation

    return 0;
}
