#include "bsp_quick_sort.h"

static int map_size;
static Point2D item_pos = {2.5f, 5.0f};

static Wall brute_force_walls[MAX_WALLS];
static Wall bsp_sorted_walls[MAX_WALLS];

void RunSortingBenchmark() {
    map_size = GetMapSize();

    GetFlatMap(brute_force_walls);

    RunQuickSort();
    RunBspSort();
}

void RunQuickSort(){
    unsigned long start_qs = time_us_32();
    QuickSort(item_pos, brute_force_walls, map_size);
    unsigned long end_qs = time_us_32();
    ReportSortingResult("QuickSort Traversal", start_qs, end_qs);
}

void RunBspSort(){
    BSPNode* bsp_root = GetMapRoot();
    int bsp_counter = 0; 

    unsigned long start_bsp = time_us_32();
    BspSort(bsp_root, item_pos, bsp_sorted_walls, &bsp_counter);
    unsigned long end_bsp = time_us_32();
    ReportSortingResult("BSP Traversal", start_bsp, end_bsp);
}

void ReportSortingResult(const char* test_name, unsigned long start, unsigned long end) {
    unsigned long delta = end - start;
    printf("Test: %s | Time spent: %lu us\n", test_name, delta);
}