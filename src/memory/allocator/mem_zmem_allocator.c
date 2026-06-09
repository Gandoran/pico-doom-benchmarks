#include "mem_zmem_allocator.h"

static void ZMemInit(void* context, size_t total_size){

}

static void* ZMemMalloc(void* context, size_t size){

}

static void ZMemFree(void* context, void* block_ptr){

}

allocator CreateZMemAllocator(){
    return {NULL,ZMemInit(),ZMemMalloc(),ZMemFree()};
}