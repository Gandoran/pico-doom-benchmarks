#include "sorting_benchmark.h"

static BenchmarkStats qs_stats;
static BenchmarkStats bsp_stats;

static void UpdateStats(BenchmarkStats* stats, unsigned long delta) {
    if (delta < stats->min_time) stats->min_time = delta;
    if (delta > stats->max_time) stats->max_time = delta;
    stats->total_time += delta;
}

static void RunQuickSort(Point2D current_pos){
    unsigned long start_qs = time_us_32();
    QuickSort(current_pos, brute_force_walls, map_size);
    unsigned long end_qs = time_us_32();
    UpdateStats(&qs_stats, end_qs - start_qs);
}

static void RunBspSort(Point2D current_pos){
    BSPNode* bsp_root = GetMapRoot();
    int bsp_counter = 0; 

    unsigned long start_bsp = time_us_32();
    BspSort(bsp_root, current_pos, bsp_sorted_walls, &bsp_counter);
    unsigned long end_bsp = time_us_32();
    UpdateStats(&bsp_stats, end_bsp - start_bsp);
}

static void ResetStats(BenchmarkStats* stats) {
    stats->min_time = ULONG_MAX;
    stats->max_time = 0;
    stats->total_time = 0;
}

static void PrintReport(const char* test_name, BenchmarkStats* stats) {
    unsigned long avg_time = stats->total_time / PATH_STEPS;
    unsigned long jitter = stats->max_time - stats->min_time;

    printf("\nTest: %s\n", test_name);
    printf("  -> Average Time: %lu us\n", avg_time);
    printf("  -> Max Time (Worst Case): %lu us\n", stats->max_time);
    printf("  -> Min Time (Best Case):  %lu us\n", stats->min_time);
    printf("  -> Jitter (Variability):  %lu us\n", jitter);
}

void RunSortingBenchmark() {
    map_size = GetMapSize();
    GetFlatMap(brute_force_walls);

    ResetStats(&qs_stats);
    ResetStats(&bsp_stats);

    for (int i = 0; i < PATH_STEPS; i++) {
        Point2D current_pos = test_path[i];

        RunQuickSort(current_pos);

        RunBspSort(current_pos);
    }
    PrintReport("QuickSort Traversal", &qs_stats);
    PrintReport("BSP Traversal", &bsp_stats);
}