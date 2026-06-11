#include "trigonometric_benchmark.h"
#include <limits.h>
#include <math.h>
#include <stdio.h>
#include "hardware/timer.h"

//TODO REFACTOR TO OPTIMIZE
static float test_angles[TRIGTEST];

static double math_sin_results[TRIGTEST];
static n_fixed lut_sin_results[TRIGTEST];

static double math_tan_results[TRIGTEST];
static n_fixed lut_tan_results[TRIGTEST];

static double math_atan_results[TRIGTEST];
static angle_bam lut_atan_results[TRIGTEST];

static void PrintReport(const char* name, unsigned long total_time, unsigned long min, unsigned long max, double error, size_t memory) {
    printf("\nTrigonometric Test: %s\n", name);
    printf("  -> Time Spent: %lu us\n", total_time);
    printf("  -> Jitter: %lu us\n", max - min);
    printf("  -> Error (LUT): %g\n", error);
    printf("  -> Memory Usage (LUT): %zu byte\n", memory);
}

static void InitializeAngles() {
    float current_angle = 0.0f;
    for (int i = 0; i < TRIGTEST; i++) {
        test_angles[i] = current_angle;
        current_angle += 0.00628f;
    }
}

static double CalculateDifferences(double *math_array, n_fixed *lut_array) {
    double total_error = 0.0;
    for (int i = 0; i < TRIGTEST; i++) {
        double lut_double = (double)lut_array[i] / 65536.0;
        total_error += fabs(math_array[i] - lut_double);
    }
    return (total_error / TRIGTEST);
}

static double CalculateDifferencesAtan(double *math_array, angle_bam *lut_array) {
    double total_error = 0.0;
    for (int i = 0; i < TRIGTEST; i++) {
        double lut_radians = ((double)lut_array[i] * (2.0 * M_PI)) / 8192.0;
        total_error += fabs(math_array[i] - lut_radians);
    }
    return (total_error / TRIGTEST);
}

static void RunSinLut(unsigned long* total, unsigned long* min, unsigned long* max) {
    for (int i = 0; i < TRIGTEST; i++) {
        angle_bam bam = RAD_TO_BAM(test_angles[i]);
        unsigned long start = time_us_32();
        lut_sin_results[i] = LutSin(bam);
        unsigned long delta = time_us_32() - start;
        *total += delta;
        if (delta < *min) *min = delta;
        if (delta > *max) *max = delta;
    }
}

static void RunTanLut(unsigned long* total, unsigned long* min, unsigned long* max) {
    for (int i = 0; i < TRIGTEST; i++) {
        angle_bam bam = RAD_TO_BAM(test_angles[i]);
        unsigned long start = time_us_32();
        lut_tan_results[i] = LutTan(bam);
        unsigned long delta = time_us_32() - start;
        *total += delta;
        if (delta < *min) *min = delta;
        if (delta > *max) *max = delta;
    }
}

static void RunATanLut(unsigned long* total, unsigned long* min, unsigned long* max) {
    for (int i = 0; i < TRIGTEST; i++) {
        n_fixed ratio_fixed = (n_fixed)(test_angles[i] * 65536.0);
        unsigned long start = time_us_32();
        lut_atan_results[i] = LutAtan(ratio_fixed);
        unsigned long delta = time_us_32() - start;
        *total += delta;
        if (delta < *min) *min = delta;
        if (delta > *max) *max = delta;
    }
}

static void RunSinMath(unsigned long* total, unsigned long* min, unsigned long* max) {
    for (int i = 0; i < TRIGTEST; i++) {
        unsigned long start = time_us_32();
        math_sin_results[i] = MathSin(test_angles[i]);
        unsigned long delta = time_us_32() - start;
        *total += delta;
        if (delta < *min) *min = delta;
        if (delta > *max) *max = delta;
    }
}

static void RunTanMath(unsigned long* total, unsigned long* min, unsigned long* max) {
    for (int i = 0; i < TRIGTEST; i++) {
        unsigned long start = time_us_32();
        math_tan_results[i] = MathTan(test_angles[i]);
        unsigned long delta = time_us_32() - start;
        *total += delta;
        if (delta < *min) *min = delta;
        if (delta > *max) *max = delta;
    }
}

static void RunATanMath(unsigned long* total, unsigned long* min, unsigned long* max) {
    for (int i = 0; i < TRIGTEST; i++) {
        unsigned long start = time_us_32();
        math_atan_results[i] = MathAtan(test_angles[i]);
        unsigned long delta = time_us_32() - start;
        
        *total += delta;
        if (delta < *min) *min = delta;
        if (delta > *max) *max = delta;
    }
}

void RunTrigBenchmark() {
    InitializeAngles();
    unsigned long total, min, max;
    total = 0; min = ULONG_MAX; max = 0;
    RunSinLut(&total, &min, &max);
    PrintReport("SIN (LUT)", total, min, max, CalculateDifferences(math_sin_results, lut_sin_results), sizeof(sin_table));
    total = 0; min = ULONG_MAX; max = 0;
    RunTanLut(&total, &min, &max);
    PrintReport("TAN (LUT)", total, min, max, CalculateDifferences(math_tan_results, lut_tan_results), sizeof(tan_table));
    total = 0; min = ULONG_MAX; max = 0;
    RunATanLut(&total, &min, &max);
    PrintReport("ARC TAN (LUT)", total, min, max, CalculateDifferencesAtan(math_atan_results, lut_atan_results), sizeof(atan_table));
    total = 0; min = ULONG_MAX; max = 0;
    RunSinMath(&total, &min, &max);
    PrintReport("SIN (MATH)", total, min, max, 0 ,0);
    total = 0; min = ULONG_MAX; max = 0;
    RunTanMath(&total, &min, &max);
    PrintReport("TAN (MATH)", total, min, max, 0, 0);
    total = 0; min = ULONG_MAX; max = 0;
    RunATanMath(&total, &min, &max);
    PrintReport("ARC TAN (MATH)", total, min, max, 0, 0);
}