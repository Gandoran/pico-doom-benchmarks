#ifndef _BSP_QUICK_SORT_
#define _BSP_QUICK_SORT_

#include <math.h>
#include <stdio.h>
#include "hardware/timer.h"

#include "geometry.h"
#include "map_creation.h"

#include "src/cpu/sorting/cpu_quick_sort.h"
#include "src/cpu/sorting/cpu_bsp.h"

#define ULONG_MAX 0xFFFFFFFFUL
#define MAX_WALLS 1000
#define PATH_STEPS 5

static int map_size;
static Wall brute_force_walls[MAX_WALLS];
static Wall bsp_sorted_walls[MAX_WALLS];

static Point2D test_path[PATH_STEPS] = {
    {2.5f,  5.0f},
    {10.0f, 12.5f},
    {-5.0f, 3.0f},
    {0.0f,  0.0f},
    {15.5f, -2.5f}
};

typedef struct {
    unsigned long min_time;
    unsigned long max_time;
    unsigned long total_time;
} BenchmarkStats;


void RunSortingBenchmark();

#endif