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
void pseudo_free(void* req){
	if(req == NULL) return;
	
	//Buddy_free
	BuddyAllocator_free(&alloc, req);
	
	//munmap
	munmap(req, request);
	printf("DONE\n");
}
