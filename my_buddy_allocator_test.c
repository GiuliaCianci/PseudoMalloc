#include "my_buddy_allocator.h"
#include <stdio.h>

#define BUFFER_SIZE 102400
#define BUDDY_LEVELS 9
#define MEMORY_SIZE (1024*1024)

char buffer[BUFFER_SIZE]; // 100 Kb buffer to handle memory should be enough
char memory[MEMORY_SIZE];

BuddyAllocator alloc;
BitMap bitmap;
int main(int argc, char** argv) {

  //1 we see if we have enough memory for the buffers
  int req_size=BuddyAllocator_calcSize(BUDDY_LEVELS);
  printf("size requested for initialization: %d/BUFFER_SIZE\n", req_size);


  //2 we initialize the allocator
  printf("init... \n");
  BuddyAllocator_init(&alloc, memory, BUDDY_LEVELS, &bitmap);
  printf("DONE\n");
  printf("printing BitMap...\n");
  printBitMap(&bitmap);
  printf("DONE\n");

  void* p1=BuddyAllocator_malloc(&alloc, 100);
  void* p2=BuddyAllocator_malloc(&alloc, 100);
  void* p3=BuddyAllocator_malloc(&alloc, 100000);
  BuddyAllocator_free(&alloc, p1);
  BuddyAllocator_free(&alloc, p2);
  BuddyAllocator_free(&alloc, p3);
  
}
