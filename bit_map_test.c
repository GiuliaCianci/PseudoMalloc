#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <assert.h>
#include <math.h>
#include <assert.h>
#include "bit_map.h"
#include "my_buddy_allocator.h"

int main() {
    // Example usage
    uint8_t bitmap_buffer[BitMap_getBytes(1024)]; // Allocate space for 1024 bits
    BitMap bitmap;
    BitMap_init(&bitmap, bitmap_buffer, 1024); // Initialize the bitmap

    char memory[1024]; // Allocate memory for the buddy allocator
    BuddyAllocator buddyAllocator;
    buddyAllocator.memory = memory;
    buddyAllocator.memory_size = sizeof(memory);
    buddyAllocator.num_levels = MAX_LEVELS;
    buddyAllocator.bitmap = &bitmap;

    // Test allocation and deallocation
    void* ptr1 = BuddyAllocator_malloc(&buddyAllocator, 64);
    printf("Allocated memory at address: %p\n", ptr1);

    void* ptr2 = BuddyAllocator_malloc(&buddyAllocator, 128);
    printf("Allocated memory at address: %p\n", ptr2);

    BuddyAllocator_free(&buddyAllocator, ptr1);
    printf("Freed memory at address: %p\n", ptr1);

    void* ptr3 = BuddyAllocator_malloc(&buddyAllocator, 32);
    printf("Allocated memory at address: %p\n", ptr3);

    return 0;
}
