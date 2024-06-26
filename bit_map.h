#pragma once
#include <stdint.h>
#include <math.h>
#include <stdio.h>

// simple bit array
typedef struct  {
  uint8_t *buffer;  // externally allocated buffer
  int buffer_size;
  int num_bits; 	//num of bits used
} BitMap;

// returns the number of bytes to store bits booleans
int BitMap_getBytes(int bits);

// initializes a bitmap on an external array
void BitMap_init(BitMap *bit_map, int num_bits, uint8_t *buffer);
	
// sets the bit bit_num in the bitmap
// status= 0 or 1
void BitMap_setBit(BitMap* bit_map, int bit_num, int status);

// inspects the status of the bit bit_num
int BitMap_bit(const BitMap* bit_map, int bit_num);

void printBitMap(BitMap *bitmap);

void SetBit_down(BitMap* bit_map, int bit_num, int status);

void SetBit_up(BitMap* bit_map, int bit_num, int status);
// to do a bitmap implementation
int levelIdx(size_t idx);

int buddyIdx(int idx);

int parentIdx(int idx);

int startIdx(int idx);

int childIdx(int idx, int left_child);
