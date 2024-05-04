#include <assert.h>
#include <stdio.h>
#include "bit_map.h"
#include "my_buddy_allocator.h"


// returns the number of bytes to store bits booleans
int BitMap_getBytes(int bits){
  return bits/8 + (bits%8!=0);
}

// initializes a bitmap on an external array
void BitMap_init(BitMap *bit_map, int num_bits, uint8_t *buffer) {
  bit_map->buffer = buffer;
  bit_map->num_bits = num_bits;
  bit_map->buffer_size = BitMap_getBytes(num_bits);
}


// sets a the bit bit_num in the bitmap
void BitMap_setBit(BitMap *bit_map, int bit_num, int status) {
  // get byte
  int byte_num = bit_num >> 3;
  assert(byte_num <= bit_map->buffer_size);
  int bit_in_byte = bit_num % 8;
  if (status) {
    bit_map->buffer[byte_num] |= (1 << bit_in_byte);
  } else {
    bit_map->buffer[byte_num] &= ~(1 << bit_in_byte);
  }
}

// inspects the status of the bit bit_num
int BitMap_bit(const BitMap* bit_map, int bit_num){ //bit_num: index of the bit to inspect
  int byte_num=bit_num>>3; 	
  assert(byte_num <= bit_map->buffer_size);       
  int bit_in_byte=bit_num % 8;
  return (bit_map->buffer[byte_num] & (1<<bit_in_byte))!=0;
}


void printBitMap(BitMap *bitmap){
    for(int i = 0; i < bitmap->num_bits; ++i){
        
        if(BitMap_bit(bitmap, i)==1){
            printf("bit num %d   value = %d\n", i ,BitMap_bit(bitmap, i));
        }
    }
}


//bitmap implementation
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




void SetBit_down(BitMap* bit_map, int bit_num, int status){

	BitMap_setBit(bit_map, bit_num , status);
    int left_child_bit = (bit_num * 2);
	int right_child_bit = (bit_num * 2)+1;
	
	if(left_child_bit <= bit_map->num_bits){
		SetBit_down(bit_map, left_child_bit, status);
	}
	
	if(right_child_bit <= bit_map->num_bits){
		SetBit_down(bit_map, right_child_bit, status);
	}
}

void SetBit_up(BitMap* bit_map, int bit_num, int status){
    
    if(status){
		if(bit_num == 1) return; //root
		BitMap_setBit(bit_map, bit_num, 1); // Set or clear the current bit
		SetBit_up(bit_map, parentIdx(bit_num), status);
		return;
	}
    else{
		if(bit_num== 1) return; //root
		BitMap_setBit(bit_map, bit_num, 0);
		if(!BitMap_bit(bit_map, bit_num) && !BitMap_bit(bit_map, buddyIdx(bit_num))){
		    SetBit_up(bit_map, parentIdx(bit_num), status);
            
        }
        return;
	}

}

