#pragma once
#include "bit_map.h"
#include <stdio.h>
#include <stdint.h>

#define MAX_LEVELS 20 		//1MB            

//single buddy

typedef struct  {
  char* memory;		//memoria gestita dall'allocator
  int memory_size;		//dimensione memoria
  int num_levels;		//numero di livelli
  size_t free_list[MAX_LEVELS+1];	//lista dei blocchi liberi
  BitMap bitmap;       // Bitmap per tenere traccia dello stato dei blocchi (libero o allocato)
} BuddyAllocator;

int BuddyAllocator_calcSize(int num_levels);

// initializes the buddy allocator, and checks that the buffer is large enough
void BuddyAllocator_init(BuddyAllocator* alloc, char* memory, BitMap *bitmap);

//allocates memory
void* BuddyAllocator_malloc(BuddyAllocator* alloc, int size);

//releases allocated memory
void BuddyAllocator_free(BuddyAllocator* alloc, void* mem);
