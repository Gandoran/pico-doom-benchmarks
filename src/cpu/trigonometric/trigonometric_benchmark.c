#include "trigonometric_benchmark.h"

static float test_angles [TRIGTEST];

static double math_sin_results[TRIGTEST];
static n_fixed lut_sin_results[TRIGTEST];

static double math_tan_results[TRIGTEST];
static n_fixed lut_tan_results[TRIGTEST];

static double math_atan_results[TRIGTEST];
static angle_bam lut_atan_results[TRIGTEST];

static unsigned long RunSinLut(){
    unsigned long start = time_us_32();
    for( int i = 0; i < TRIGTEST; i++ ){
        lut_sin_results [i] = LutSin(RAD_TO_BAM(test_angles[i]));
    }
    unsigned long end = time_us_32();
    return (end - start);
}

static unsigned long RunTanLut(){
    unsigned long start = time_us_32();
    for( int i = 0; i < TRIGTEST; i++ ){
        lut_tan_results [i] = LutTan(RAD_TO_BAM(test_angles[i]));
    }
    unsigned long end = time_us_32();
    return (end - start);
}

static unsigned long RunATanLut(){
    unsigned long start = time_us_32();
    for( int i = 0; i < TRIGTEST; i++ ){
        n_fixed ratio_fixed = (n_fixed)(test_angles[i] * 65536.0);
        lut_atan_results[i] = LutAtan(ratio_fixed);
    }
    unsigned long end = time_us_32();
    return (end - start);
}

static unsigned long RunSinMath(){
    unsigned long start = time_us_32();
    for( int i = 0; i < TRIGTEST; i++ ){
        math_sin_results [i] = MathSin(test_angles[i]);
    }
    unsigned long end = time_us_32();
    return (end - start);
}

static unsigned long RunTanMath(){
    unsigned long start = time_us_32();
    for( int i = 0; i < TRIGTEST; i++ ){
        math_tan_results [i] = MathTan(test_angles[i]);
    }
    unsigned long end = time_us_32();
    return (end - start);
}

static unsigned long RunATanMath(){
    unsigned long start = time_us_32();
    for( int i = 0; i < TRIGTEST; i++ ){
        math_atan_results [i] = MathAtan(test_angles[i]);
    }
    unsigned long end = time_us_32();
    return (end - start);
}

static void InitializeAngles() {
    float current_angle = 0.0f;
    for(int i = 0; i < TRIGTEST; i++) {
        test_angles[i] = current_angle;
        current_angle += 0.00628f;
    }
}

static double CalculateDifferences(double *math_array, n_fixed *lut_array){
    double total_error = 0.0;
    for (int i = 0; i < TRIGTEST; i++){
        double lut_double = (double)lut_array[i] / 65536.0;
        total_error += fabs(math_array[i] - lut_double);
    }
    return (total_error / TRIGTEST);
}

static double CalculateDifferencesAtan(double *math_array, angle_bam *lut_array){
    double total_error = 0.0;
    for (int i = 0; i < TRIGTEST; i++){
        double bam_angle = (double)lut_array[i] / 65536.0;
        double lut_radians = (bam_angle * (2.0 * M_PI)) / 8192.0;
        total_error += fabs(math_array[i] - lut_radians);
    }
    return (total_error / TRIGTEST);
}

static void ReportLutResult(const char* test_name, unsigned long delta_lut, unsigned long delta_math, double error, size_t memory_usage ) {
    printf("Test: %s | Time spent with Lut: %lu us | Time spent with math: %lu us | Memory Used by tables: %zu | Error: %g \n", test_name, delta_lut, delta_math, memory_usage,error);
}

void RunTrigBenchmark(){
    InitializeAngles();
    
    ReportLutResult("Sin", RunSinLut(), RunSinMath() ,CalculateDifferences(math_sin_results, lut_sin_results), sizeof(sin_table));
    
    ReportLutResult("Tan", RunTanLut(), RunTanMath() ,CalculateDifferences(math_tan_results, lut_tan_results), sizeof(tan_table));
    
    ReportLutResult("Arc Tan", RunATanLut(), RunATanMath(), CalculateDifferencesAtan(math_atan_results, (angle_bam*)lut_atan_results), sizeof(atan_table));
}