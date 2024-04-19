#define _GNU_SOURCE // For map_anonymous
#include "pseudo_malloc.h"
#include "my_buddy_allocator.h"
#include <sys/mman.h>
#include <assert.h>
#include <stdio.h>
#include <math.h>
#include <stdlib.h>




extern BuddyAllocator alloc;
void* req;
size_t request;

//allocates
void* pseudo_malloc(size_t request){
	if(request < 0 ) fprintf(stderr, "Request can't be less than 0\n");
	if(request == 0) return NULL;
	if(request < PAGE_SIZE/4){
		printf("Small request, use BuddyAllocator..\n");
		req = BuddyAllocator_malloc(&alloc, request);
		return req;
	}else if(request >= PAGE_SIZE/4){
		printf("Large request, use mmap...\n");
		//anonymous mapping, not connected to a file. filedes and offset are ignored, its contents are initialized to zero.
		req = mmap(0, request, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
		if (req == MAP_FAILED) {
			perror("mmap");
			exit(EXIT_FAILURE);
		}
		return req;
	}
	return NULL;
}

//releases allocated memory

void pseudo_free(void* mem) {
    if (mem == NULL) return;

    // Check if the memory was allocated by the buddy allocator or mmap
    if (req == mem) {
        // If allocated by the buddy allocator, free using BuddyAllocator_free
        BuddyAllocator_free(&alloc, mem);
    } else{
		//i need to store size of allocated memory
		size_t size_to_free;
		
		
		if(munmap(mem, size_to_free) == -1) {
            perror("munmap");
            exit(EXIT_FAILURE);
        }
	}
    printf("DONE\n");
}
