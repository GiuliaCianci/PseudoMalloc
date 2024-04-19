#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <unistd.h>
#include "my_buddy_allocator.h"
#include "pseudo_malloc.h"
#include "bit_map.h"


#define PAGE_SIZE 4096		//stackoverflow bytes
#define BITMAP_MEMORY (1024*1024)	//1MB in bytes

#define BUFFER_SIZE 102400
#define BUDDY_LEVELS 9


BuddyAllocator alloc;
BitMap bitmap;

char buffer[PAGE_SIZE]; 
char memory[BITMAP_MEMORY];


int main(int agrc, char **argv) {
	
	printf("Main: buddy_init...\n");
	BuddyAllocator_init(&alloc, memory, BUDDY_LEVELS, &bitmap);
	printf("Main: Done\n");
	
    // Example usage
    printf("Main: small allocation...\n");
    void* small_ptr = pseudo_malloc(100); // Small allocation
    printf("MainDone: Small pointer: %p\n", small_ptr);
    
    printf("Main: large allocation...\n");
    void* large_ptr = pseudo_malloc(5000); // Large allocation
    printf("MainDone: Large pointer: %p\n", large_ptr);

    pseudo_free(small_ptr); // Free small allocation
    pseudo_free(large_ptr); // Free large allocation

    return 0;
}
