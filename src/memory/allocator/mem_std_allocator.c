#include "mem_std_allocator.h"

static void StdInit(void* context, size_t total_size){}

static void* StdMalloc(void* context, size_t size){
    return (void *) malloc (size);
}

static void StdFree(void* context, void* block_ptr){
    free(block_ptr);
}

Allocator CreateStdAllocator(){
    return (Allocator){
        .context = NULL,
        .init = StdInit,
        .alloc = StdMalloc,
        .free_mem = StdFree
    };
}