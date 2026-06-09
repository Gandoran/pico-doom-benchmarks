#ifndef _ALLOCATOR_
#define _ALLOCATOR_

//for size_t use
#include <stddef.h>

typedef struct Allocator{
    void* context;
    //init
    void (*init)(void* context, size_t total_size);
    //alloc
    void* (*alloc)(void* context, size_t size);
    //free
    void (*free_mem)(void* context, void* block_ptr);
}Allocator;

void* AllocMalloc(size_t dimension);
void  AllocFree(void* block_ptr);

#endif