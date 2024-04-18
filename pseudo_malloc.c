#include "pseudo_malloc.h"
#include <sys/mman.h>
#include <assert.h>
#include <stdio.h>

/*Pseudo Malloc:
   This is a malloc replacement
   The system relies on mmap for the physical allocation of memory, but handles the requests in
   2 ways:
   - for small requests (< 1/4 of the page size) it uses a buddy allocator.
     Clearly, such a buddy allocator can manage at most page-size bytes
     For simplicity use a single buddy allocator, implemented with a bitmap
     that manages 1 MB of memory for these small allocations.

   - for large request (>=1/4 of the page size) uses a mmap.
*/
//if request < 1/4 page_size
	//buddy_allocator
//else
	//mmap
	
/*memory request
  check size
  if small use buddy
	search for free block with bitmap
	if found, mark the block as allocated in the bitmap and return a pointer to that block
	if not found, handle fragmentation or return an error if unable to allocate
	
  if large use mmap
	Call mmap to allocate the requested size of memory
	Return a pointer to the allocated memory region
	Handle errors if mmap fails
	
*/

void* mem;
int shm_fd;
// initializes the ????
void pseudo_init();

//allocates
void pseudo_malloc(){
	if(req <0 ) error;
	
	if(req < 1/4 page_size){
		BuddyAllocator_malloc(BuddyAllocator* alloc, int size)
	}else if(req >= 1/4 page_size){
		//anonymous mapping, not connected to a file. filedes and offset are ignored, its contents are initialized to zero.
		mem = mmap(0, size_t size_memory, PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
	}
}

//releases allocated memory
void pseudo_free(void* mem);
