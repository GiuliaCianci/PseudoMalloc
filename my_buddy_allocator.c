#include <stdio.h>
#include <assert.h>
#include <math.h> // for floor and log2
#include "my_buddy_allocator.h"
#include "bit_map.h"

void BuddyAllocator_init(BuddyAllocator* alloc, char* memory, uint8_t *bitmap){
	
	int num_nodes =(1 << (MAX_LEVELS+1))-1;	//num nodi albero binario
	BitMap_init(&alloc->bitmap, num_nodes, bitmap);

  // we need room also for level 0
  alloc->num_levels=MAX_LEVELS+1;
  alloc->memory=memory;
  
 
  // initialize the number of blocks at each level
    for(int i = 0; i < MAX_LEVELS+1; ++i){
        alloc->free_list[i] = (1 << i);	//2^i
}
  printf("BUDDY INITIALIZED\n");
  printf("\tlevels: %d\n", alloc->num_levels);
 }
  


//allocates memory
void* BuddyAllocator_malloc(BuddyAllocator* buddyAllocator, int size) {
  // we determine the level of the page based on requested size
  int level = MAX_LEVELS - ceil(log2(size));

  // if the level is greater than the max level, we pad it to max
  if (level>buddyAllocator->num_levels)
    level=buddyAllocator->num_levels;

  printf("[BUDDY_MALLOC]requested: %d bytes, level %d \n", size, level);

	int num_nodes = buddyAllocator->free_list[level];
	printf("BUDDY: num_node %d\n", num_nodes);
	
    // Find the first available block of the specified level
    size_t offset = 0;
    while (offset < num_nodes &&
           BitMap_bit(&buddyAllocator->bitmap, (1 << level) + offset)){
        offset++;
    }

    // If no available block is found, return NULL
    if (offset >= num_nodes){
        printf("[BuddyMalloc]: No more memory available, returning NULL\n");
        return NULL;
    }

    // Calculate the starting index of the allocated block in the bitmap
    size_t available_bit = (1 << level) + offset;
	
    // Mark the block as allocated in the BitMap
    
    SetBit_down(&buddyAllocator->bitmap,available_bit, 1);
    
    SetBit_up(&buddyAllocator->bitmap,available_bit, 1);

    // Calculate the starting address of the allocated block
    size_t block_start = (startIdx(available_bit) * (1 << (buddyAllocator->num_levels - levelIdx(available_bit))));
    
    return (void *)(&buddyAllocator->memory + block_start);
    
}



//releases allocated memory
void BuddyAllocator_free(BuddyAllocator* alloc, void* mem) {
	if(mem==NULL) return;
	
	printf("freeing %p\n", mem);
	
	// Calculate the index of the block in the bitmap
    size_t block_idx = (size_t)((char*)mem - alloc->memory)+1;

    // Calculate the level and starting index of the block in the bitmap
    int level = levelIdx(block_idx);
    size_t bit_num = block_idx >> level;
	
    SetBit_down(&alloc->bitmap,bit_num, 0);
    
    SetBit_up(&alloc->bitmap,bit_num, 0);
    
	printf("printing BitMap...\n");
	printBitMap(&alloc->bitmap);
	printf("DONE\n");
  
}
