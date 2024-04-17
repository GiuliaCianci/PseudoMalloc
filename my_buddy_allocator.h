#pragma once
#include "bit_map.h"
#include <stdio.h>
#include <stdint.h>

#define MAX_LEVELS 16           //20??

//single buddy

typedef struct{
	struct Block* next;	//puntatore al prossimo blocco
	int size;			//dimensione blocco in byte
}Block;

typedef struct  {
  char* memory;		//memoria gestita dall'allocator
  int memory_size;		//dimensione memoria
  int num_levels;		//numero di livelli
  Block* free_list[MAX_LEVELS];	//lista dei blocchi liberi
  BitMap* bitmap;       // Bitmap per tenere traccia dello stato dei blocchi (libero o allocato)
} BuddyAllocator;


// initializes the buddy allocator, and checks that the buffer is large enough
void BuddyAllocator_init(BuddyAllocator* alloc, char* memory, int num_levels,
						BitMap* bitmap);

//allocates memory
void* BuddyAllocator_malloc(BuddyAllocator* alloc, int size);

//releases allocated memory
void BuddyAllocator_free(BuddyAllocator* alloc, void* mem);
