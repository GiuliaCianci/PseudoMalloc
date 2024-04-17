#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <assert.h>
#include <math.h>
#include <assert.h>
#include "my_buddy_allocator.h"
#include "bit_map.h"

int main() {
    char memory[1024]; // Memory for the buddy allocator
    BitMap bitmap; // Bitmap for tracking block allocation
    BitMap_init(&bitmap, (uint8_t*)memory, 1024); // Initialize the bitmap

    BuddyAllocator buddyAllocator;
    BuddyAllocator_init(&buddyAllocator, memory, 10, &bitmap); // Initialize the buddy allocator

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
