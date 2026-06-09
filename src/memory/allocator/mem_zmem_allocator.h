#ifndef _MEM_ZMEM_
#define _MEM_ZMEM_

#include "allocator.h"

typedef struct mem_zone{
    int		size;
    mem_block	blocklist;
    mem_block*	rover;   
}mem_zone;

typedef struct mem_block{
    int			size;
    void**		user;
    int			tag;
    int			id;

    struct mem_block*	next;
    struct mem_block*	prev;
}mem_block;

allocator CreateZMemAllocator();

#endif