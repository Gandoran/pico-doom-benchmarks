#include "sorting_benchmark.h"
#include <stdio.h>
#include <limits.h>

#define PATH_STEPS 5

static int map_size;
static Wall brute_force_walls[MAX_WALLS];
static Wall bsp_sorted_walls[MAX_WALLS];

// Definiamo un percorso di posizioni per simulare il movimento della telecamera
static Point2D test_path[PATH_STEPS] = {
    {2.5f,  5.0f},
    {10.0f, 12.5f},
    {-5.0f, 3.0f},
    {0.0f,  0.0f},
    {15.5f, -2.5f}
};

// Struttura per raccogliere i dati statistici del benchmark
typedef struct {
    unsigned long min_time;
    unsigned long max_time;
    unsigned long total_time;
} BenchmarkStats;

// Prototipi delle funzioni interne
static void ResetStats(BenchmarkStats* stats);
static void UpdateStats(BenchmarkStats* stats, unsigned long delta);
static void PrintReport(const char* test_name, BenchmarkStats* stats);

void RunSortingBenchmark() {
    map_size = GetMapSize();
    GetFlatMap(brute_force_walls);

    BenchmarkStats qs_stats;
    BenchmarkStats bsp_stats;

    ResetStats(&qs_stats);
    ResetStats(&bsp_stats);

    // Eseguiamo il benchmark lungo tutta la traiettoria
    for (int i = 0; i < PATH_STEPS; i++) {
        Point2D current_pos = test_path[i];

        // 1. Benchmark QuickSort
        unsigned long start_qs = time_us_32();
        QuickSort(current_pos, brute_force_walls, map_size);
        unsigned long end_qs = time_us_32();
        UpdateStats(&qs_stats, end_qs - start_qs);

        // 2. Benchmark BSP
        BSPNode* bsp_root = GetMapRoot();
        int bsp_counter = 0; 

        unsigned long start_bsp = time_us_32();
        BspSort(bsp_root, current_pos, bsp_sorted_walls, &bsp_counter);
        unsigned long end_bsp = time_us_32();
        UpdateStats(&bsp_stats, end_bsp - start_bsp);
    }

    // Stampa dei risultati comparativi finali
    printf("\n=== RUNNING SORTING BENCHMARK SESSION ===\n");
    PrintReport("QuickSort Traversal (Dynamic)", &qs_stats);
    PrintReport("BSP Traversal (Static Tree)", &bsp_stats);
    printf("=========================================\n");
}

static void ResetStats(BenchmarkStats* stats) {
    stats->min_time = ULONG_MAX;
    stats->max_time = 0;
    stats->total_time = 0;
}

static void UpdateStats(BenchmarkStats* stats, unsigned long delta) {
    if (delta < stats->min_time) stats->min_time = delta;
    if (delta > stats->max_time) stats->max_time = delta;
    stats->total_time += delta;
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