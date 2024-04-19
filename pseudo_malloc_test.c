#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <unistd.h>
#include "my_buddy_allocator.h"
#include "pseudo_malloc.h"
#include "bit_map.h"


#define PAGE_SIZE 4096		//stackoverflow bytes
#define BITMAP_MEMORY (1024*1024)	//1MB in bytes


BuddyAllocator alloc;
BitMap bitmap;

char buffer[PAGE_SIZE]; 
char memory[BITMAP_MEMORY];


int main(int agrc, char **argv) {
	
	printf("Main: buddy_init...\n");
	BuddyAllocator_init(&alloc, memory, &bitmap);
	printf("Main: Done\n");
	
    printf("[MAIN]: Initialized BuddyAllocator:\n\tBitMap length in bits --> %d \n", (&alloc)->bitmap.num_bits);

    printf("[MAIN]: Beginning of memory: %p\n", memory);

    // Example usage
    printf("Main: small allocation...\n");
    void* small_ptr = pseudo_malloc(100); // Small allocation
    printf("MainDone: Small pointer: %p\n", small_ptr);
    
    printf("Main: large allocation...\n");
    void* large_ptr = pseudo_malloc(5000); // Large allocation
    printf("MainDone: Large pointer: %p\n", large_ptr);

    pseudo_free(small_ptr); // Free small allocation
    pseudo_free(large_ptr); // Free large allocation

	
    printf("[MAIN]: Allocating all memory with blocks of 1024 size... and 5 more\n");

    void *ptrs[1029];

    for(int i = 0; i < 1029; ++i){
        ptrs[i] = pseudo_malloc(1024);
        printf("Allocated ptr %d  %p\n", i, ptrs[i]);
    }

    printf("End of memory %p\n", memory + BITMAP_MEMORY - 1);

    printf("[MAIN]: Now freeing ptr1023 %p\n", ptrs[1023]);
    pseudo_free(ptrs[1023]);

	
    printf("[MAIN]: Now allocating 2 of half the size of the freed ptr\n");
    void *new1 = pseudo_malloc(512);
    void *new2 = pseudo_malloc(512);
    printf("[MAIN]: Allocated 2 new pointers:\n\tnew1: %p\n\tnew2: %p\n", new1, new2);

    printf("[MAIN]: Allocating size 1\n");
    void *one = pseudo_malloc(1);
    printf("[MAIN]: Allocated new ptr of size 1:\n\tone: %p\n", one);


    printf("[MAIN]: Freeing half of the first 1024 ptrs\n");
    
    for(int i = 0; i < 512; ++i){
        pseudo_free(ptrs[i]);
        printf("[MAIN]: Freed ptr %d  %p\n", i, ptrs[i]);
    }

    printf("[MAIN]: Allocating back the memory with smaller size (256)\n");
    
    void *half[BITMAP_MEMORY/2/256];
    for(int i = 0; i < BITMAP_MEMORY/2/256; ++i){
        half[i] = pseudo_malloc(256);
        printf("Allocated ptr %d  %p\n", i, half[i]);
    }

    printf("Freeing the same ptr twice\n");
    pseudo_free(half[0]);
    pseudo_free(half[0]);

    printf("[MAIN]: Freeing all memory\n");
    for (int i = 0; i < BITMAP_MEMORY/2/256; ++i){
        pseudo_free(half[i]);
    }

    for (int i = 0; i < 1029; ++i){
        pseudo_free(ptrs[i]);
    }

    pseudo_free(new1);
    pseudo_free(new2);
 

    printf("[MAIN]: Freed all memory, sanity check, printing all 1's in the bitmap, there sould be no prints\n");
    printf("[MAIN]: printing... ");
    printBitMap(&alloc.bitmap);
    printf("\n");

    printf("[MAIN]: Now let's do some fragmentation: 1024 allocations of 513\n");
    for(int i = 0; i < 1024; ++i){
        ptrs[i] = pseudo_malloc(513);
        printf("Allocated ptr %d  %p\n", i, ptrs[i]);
    }

    printf("[MAIN]: Now one allocation should return out of memory\n");
    printf("[MAIN]: Allocating 1 byte...\n");
    void *oom = pseudo_malloc(1);

    printf("[MAIN]: testing mmap\n");
    void *ptr = pseudo_malloc(8198);
    printf("[MAIN]: Allocated ptr %p\n", ptr);
    printf("[MAIN]: Unmapping ptr %p\n", ptr);
    pseudo_free(ptr);

    printf("[MAIN]: Freeing all memory... again\n");

    for(int i = 0; i < 1024; ++i){
        pseudo_free(ptrs[i]);
        printf("[MAIN]: Freed ptr %d  %p\n", i, ptrs[i]);
    }

    printf("[MAIN]: Freed all memory, sanity check, printing all 1's in the bitmap, there sould be no prints\n");
    printf("[MAIN]: printing... ");
    printBitMap(&alloc.bitmap);
    printf("\n");


    printf("[MAIN]: Allocating ptrs of random size:\n");
    for(int i = 0; i < 1024; ++i){
        size_t size = rand() % 1024;
        ptrs[i] = pseudo_malloc(size);
        printf("Allocated ptr %d  %p of size %ld\n", i, ptrs[i], size);
    }

    for(int i = 0; i < 1024; ++i){
        printf("Freeing ptr %i  %p\n", i, ptrs[i]);
        pseudo_free(ptrs[i]);
    }

    printf("END\n");

}

