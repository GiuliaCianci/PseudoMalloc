CC=gcc
CCOPTS=--std=gnu99 -Wall -D_LIST_DEBUG_ 
AR=ar

OBJS=my_buddy_allocator.o\
     bit_map.o\
     pseudo_malloc.o

HEADERS=my_buddy_allocator.h  bit_map.h pseudo_malloc.h

LIBS=libbuddy.a

BINS=pseudo_malloc_test bit_map_test my_buddy_allocator_test

.phony: clean all


all:	$(LIBS) $(BINS)

%.o:	%.c $(HEADERS)
	$(CC) $(CCOPTS) -c -o $@  $<

libbuddy.a: $(OBJS) 
	$(AR) -rcs $@ $^
	$(RM) $(OBJS)

pseudo_malloc_test: pseudo_malloc_test.o $(LIBS)
	$(CC) $(CCOPTS) -o $@ $^ -lm

bit_map_test: bit_map_test.o $(LIBS)
	$(CC) $(CCOPTS) -o $@ $^ -lm

my_buddy_allocator_test: my_buddy_allocator_test.o $(LIBS)
	$(CC) $(CCOPTS) -o $@ $^ -lm

clean:
	rm -rf *.o *~ $(LIBS) $(BINS)
