#ifndef _FILE_SYSTEM_BENCHMARK_
#define _FILE_SYSTEM_BENCHMARK_

#include <stdio.h>
#include "hardware/timer.h"

#include "mem_hash_table.h"
#include "mem_linear_wad.h"

#include "wad_benchmark_data.h"

#define FILESYSTEMTEST 1000

void RunFileSystemBenchmark();

#endif