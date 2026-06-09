#ifndef _BSP_QUICK_SORT_
#define _BSP_QUICK_SORT_

#include <math.h>
#include <stdio.h>
#include "hardware/timer.h"

#include "geometry.h"
#include "map_creation.h"

#include "src/cpu/sorting/cpu_quick_sort.h"
#include "src/cpu/sorting/cpu_bsp.h"

#define MAX_WALLS 1000

void InitializeMap();

void RunSortingBenchmark();

void RunQuickSort();
void RunBspSort();

void ReportSortingResult(const char* test_name, unsigned long start, unsigned long end) ;

#endif