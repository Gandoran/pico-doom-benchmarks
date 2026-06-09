#include "mem_zmem_allocator.h"

static mem_zone main_zone;

static void SplitBlock(mem_block* mal_rover, size_t size, size_t extra_space) {
    //Creating the new Header
    mem_block* new_block = (mem_block*)( (char*)mal_rover + sizeof(mem_block) + size );
    
    new_block->size = extra_space - sizeof(mem_block);
    new_block->tag = PU_FREE;
    new_block->user = NULL;

    //Insert the new block
    new_block->next = mal_rover->next;
    new_block->prev = mal_rover;
    mal_rover->next->prev = new_block;
    mal_rover->next = new_block;
}

static void MergeWithNext(mem_block* free_block) {
    if (free_block->next->tag == PU_FREE && free_block->next != &main_zone.blocklist) {
        free_block->size += sizeof(mem_block) + free_block->next->size;
        free_block->next = free_block->next->next;
        free_block->next->prev = free_block;
    }
}

static void MergeWithPrev(mem_block* free_block) {
    if (free_block->prev->tag == PU_FREE && free_block->prev != &main_zone.blocklist) {
        mem_block* prev_block = free_block->prev;
        prev_block->size += sizeof(mem_block) + free_block->size;
        prev_block->next = free_block->next;
        free_block->next->prev = prev_block;
    }
}

static void ZMemInit(void* context, size_t total_size){
    mem_block* first_block = (mem_block*) context;

    main_zone.size = total_size;
    main_zone.rover = first_block;

    main_zone.blocklist.next = main_zone.blocklist.prev = first_block;
    main_zone.blocklist.tag = PU_STATIC;

    first_block->size = total_size - sizeof(mem_block);
    first_block->user = NULL;
    first_block->tag = PU_FREE;

    first_block->next = first_block->prev = &main_zone.blocklist;
}

static void* ZMemMalloc(void* context, size_t size){
    //round the size of a pow of 4 for microcontroller
    size = (size + 3) & ~3;
    mem_block* start = main_zone.rover;
    mem_block* mal_rover = main_zone.rover;
    do{
        mal_rover = mal_rover->next;
        if(mal_rover->tag == PU_FREE && mal_rover->size >= size){
            size_t extra_space = mal_rover->size - size;
            //check if with the round there is still free space for a block
            if (extra_space >= sizeof(mem_block) + 4) SplitBlock(mal_rover, size, extra_space);

            mal_rover->tag = PU_STATIC;
            main_zone.rover = mal_rover->next;

            main_zone.rover = mal_rover->next;
        }
    }while(mal_rover != start);

    return NULL;
}

static void ZMemFree(void* context, void* block_ptr){
    if (!block_ptr) return;
    //adjust the rover
    mem_block* free_block = (mem_block*)block_ptr - 1;

    free_block->tag = PU_FREE;

    MergeWithNext(free_block);
    MergeWithPrev(free_block);
}

allocator CreateZMemAllocator(){
    return (allocator){
        .context = &main_zone,
        .init = ZMemInit,
        .alloc = ZMemMalloc,
        .free_mem = ZMemFree
    };
}