#ifndef _ALLOCATOR_BENCHMARK_
#define _ALLOCATOR_BENCHMARK_

#include <stdio.h>
#include "hardware/timer.h"

#include "mem_std_allocator.h"
#include "mem_zmem_allocator.h"

#define MEMORY_SIZE_TEST (1024 * 16) //16kb 

#define FRAG_BLOCKS_COUNT   10

#define MAX_CAPACITY_BLOCKS 1000

static uint8_t zmem_arena[MEMORY_SIZE_TEST];

void RunAllocatorBenchmark();

#endif