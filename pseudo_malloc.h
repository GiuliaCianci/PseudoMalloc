#pragma once
#include "my_buddy_allocator.h"
#include <stdio.h>
#include <stdint.h>


// initializes the ????
void pseudo_init();

//allocates
void pseudo_malloc();

//releases allocated memory
void pseudo_free(void* mem);
