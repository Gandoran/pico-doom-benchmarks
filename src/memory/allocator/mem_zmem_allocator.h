#ifndef _MEM_ZMEM_
#define _MEM_ZMEM_

#include "allocator.h"

#define PURGE_LEVEL 100
#define PU_STATIC 1
#define PU_FREE 0
#define PU_CACHE 100

typedef struct mem_block{
    int			size;
    void**		user;
    int			tag;

    struct mem_block*	next;
    struct mem_block*	prev;
}mem_block;

typedef struct mem_zone{
    int		size;
    mem_block	blocklist;
    mem_block*	rover;   
}mem_zone;

Allocator CreateZMemAllocator();

#endif