#ifndef _ALLOCATOR_BENCHMARK_
#define _ALLOCATOR_BENCHMARK_

#include <stdio.h>
#include "hardware/timer.h"

#include "mem_standard_allocator.h"
#include "mem_zmem_allocator.h"

#define ALLOCATOR_TEST 1000

void RunAllocatorBenchmark();

#endif