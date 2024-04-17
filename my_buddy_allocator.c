#include <stdio.h>
#include <assert.h>
#include <math.h> // for floor and log2
#include "my_buddy_allocator.h"

// these are trivial helpers to support you in case you want
// to do a bitmap implementation
int levelIdx(size_t idx){
  return (int)floor(log2(idx));
};

int buddyIdx(int idx){
  if (idx&0x1){
    return idx-1;
  }
  return idx+1;
}

int parentIdx(int idx){
  return idx/2;
}

int startIdx(int idx){
  return (idx-(1<<levelIdx(idx)));
}


void BuddyAllocator_init(BuddyAllocator* alloc, char* memory, int num_levels,
						BitMap* bitmap){

  // we need room also for level 0
  alloc->num_levels=num_levels;
  alloc->memory=memory;
  assert (num_levels<MAX_LEVELS);
  int num_nodes =(1 << (MAX_LEVELS+1))-1;	//num nodi albero binario
  BitMap_init(bitmap, (uint8_t*)memory, num_nodes);

  printf("BUDDY INITIALIZING\n");
  printf("\tlevels: %d", num_levels);
 }
  


//allocates memory
void* BuddyAllocator_malloc(BuddyAllocator* buddyAllocator, int size) {
  // we determine the level of the page based on requested size
  int level = 0;
  int blockSize = 1;
  while (blockSize < size) {
	  blockSize <<= 1; // Equivalent to multiplying by 2, shifts the bits left
	  level++;
	}
	level = MAX_LEVELS - level;

  // if the level is too small, we pad it to max
  if (level>buddyAllocator->num_levels)
    level=buddyAllocator->num_levels;

  printf("requested: %d bytes, level %d \n", size, level);


    // Find the first available block of the specified level
    size_t available_bit = 0;
    while (available_bit < buddyAllocator->num_levels[level] &&
           BitMap_bit(buddyAllocator->bitmap, (1 << level) + available_bit)){
        available_bit++;
    }

    // If no available block is found, return NULL
    if (available_bit >= buddyAllocator->num_levels[level]){
        printf("[BuddyMalloc]: No more memory available, returning NULL\n");
        return NULL;
    }

    // Calculate the starting index of the allocated block in the bitmap
    available_bit = (1 << level) + available_bit;

    // Mark the block as allocated in the BitMap
    BitMap_setBit(&buddyAllocator->bitmap, available_bit, 1);
    
    // Find and mark the buddy index as allocated if it's available
    size_t buddy_bit = buddyIdx(available_bit);
    if (buddy_bit < buddyAllocator->num_levels[level] &&
        !BitMap_bit(&buddyAllocator->bitmap, buddy_bit)) {
        BitMap_setBit(&buddyAllocator->bitmap, buddy_bit, 1);
    }

    // Calculate the starting address of the allocated block
    size_t block_start = (startIdx(available_bit) * (1 << (buddyAllocator->num_levels - levelIdx(available_bit))));
    
    return (void *)(buddyAllocator->memory + block_start);

}


//releases allocated memory
void BuddyAllocator_free(BuddyAllocator* alloc, void* mem) {
	printf("freeing %p", mem);
	// Calculate the index of the block in the bitmap
    size_t block_idx = (size_t)((char*)mem - alloc->memory);

    // Calculate the level and starting index of the block in the bitmap
    int level = levelIdx(block_idx);
    size_t start_bit = block_idx >> level;

    // Mark the block as free in the bitmap
    BitMap_setBit(&alloc->bitmap, start_bit, 0);

    // Check if the buddy of the freed block is also free
    while (level < alloc->num_levels - 1) {
        size_t buddy_idx = buddyIdx(start_bit);
        size_t parent_idx = parentIdx(start_bit);
        int buddy_free = !BitMap_bit(&alloc->bitmap, buddy_idx);

        if (buddy_free) {
            // Merge the buddy block with the freed block
            BitMap_setBit(&alloc->bitmap, parent_idx, 0);
            start_bit = parent_idx;
            level++;
        } else {
            break; // Buddy block is not free, stop merging
        }
    }
}
