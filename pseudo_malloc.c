#define _GNU_SOURCE // For map_anonymous
#include "pseudo_malloc.h"
#include "my_buddy_allocator.h"
#include <sys/mman.h>
#include <assert.h>
#include <stdio.h>
#include <math.h>
#include <stdlib.h>


extern BuddyAllocator alloc;
largeMem stored = {NULL, 0};
void* req;


//allocates
void* pseudo_malloc(size_t request){
	if(request < 0 ) fprintf(stderr, "Request can't be less than 0\n");
	
	if(request == 0) return NULL;
	
	//small request ---> buddy allocator
	if(request < PAGE_SIZE/4){
		printf("Small request, use BuddyAllocator..\n");
		req = BuddyAllocator_malloc(&alloc, request);
		return req;		
	}
	//large request ---> mmap
	else if(request >= PAGE_SIZE/4){
		printf("Large request, use mmap...\n");
		//anonymous mapping, not connected to a file. filedes and offset are ignored, its contents are initialized to zero.
		req = mmap(0, request, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
		if (req == MAP_FAILED) {
			perror("mmap");
			exit(EXIT_FAILURE);
		}
		//storing allocated memory
		 stored.size = request;
		 stored.memory = req;
		 
		return stored.memory;
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
		
		if(munmap(stored.memory, stored.size) == -1) {
            perror("munmap");
            exit(EXIT_FAILURE);
        }
	}
    printf("DONE\n");
}
