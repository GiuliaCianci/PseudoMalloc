#pragma once
#include "my_buddy_allocator.h"
#include <stdio.h>
#include <stdint.h>
#include <math.h>

#define PAGE_SIZE 4096		//stackoverflow bytes
#define BITMAP_MEMORY (1024*1024)	//1MB in bytes

//struct to save requested memory values
typedef struct{
	void* memory;
	size_t size;
}largeMem;

//allocates size_t bytes of memory requested
void* pseudo_malloc(size_t request);

//releases allocated memory
void pseudo_free(void* req);
