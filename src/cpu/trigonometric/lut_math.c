#include "lut_math.h"

static float test_angles [TRIGTEST];

static double math_sin_results[TRIGTEST];
static n_fixed lut_sin_results[TRIGTEST];

static double math_tan_results[TRIGTEST];
static n_fixed lut_tan_results[TRIGTEST];

static double math_atan_results[TRIGTEST];
static n_fixed lut_atan_results[TRIGTEST];

//TODO AGGIUNGERE CALCOLO MEMORIA LUT
void RunTrigBenchmark(){
    InitializeAngles();
    
    ReportLutResult("Sin", RunSinLut(), RunSinMath() ,CalculateDifferences(math_sin_results, lut_sin_results));
    
    ReportLutResult("Tan", RunTanLut(), RunTanMath() ,CalculateDifferences(math_tan_results, lut_tan_results));
    
    ReportLutResult("Arc Tan", RunATanLut(), RunATanMath(), CalculateDifferences(math_atan_results, lut_atan_results));
}

unsigned long RunSinLut(){
    unsigned long start = time_us_32();
    for( int i = 0; i < TRIGTEST; i++ ){
        lut_sin_results [i] = LutSin(RAD_TO_BAM(test_angles[i]));
    }
    unsigned long end = time_us_32();
    return (end - start);
}

unsigned long RunTanLut(){
    unsigned long start = time_us_32();
    for( int i = 0; i < TRIGTEST; i++ ){
        lut_tan_results [i] = LutTan(RAD_TO_BAM(test_angles[i]));
    }
    unsigned long end = time_us_32();
    return (end - start);
}

unsigned long RunATanLut(){
    unsigned long start = time_us_32();
    for( int i = 0; i < TRIGTEST; i++ ){
        lut_atan_results [i] = LutAtan(RAD_TO_BAM(test_angles[i]));
    }
    unsigned long end = time_us_32();
    return (end - start);
}

unsigned long RunSinMath(){
    unsigned long start = time_us_32();
    for( int i = 0; i < TRIGTEST; i++ ){
        math_sin_results [i] = MathSin(test_angles[i]);
    }
    unsigned long end = time_us_32();
    return (end - start);
}

unsigned long RunTanMath(){
    unsigned long start = time_us_32();
    for( int i = 0; i < TRIGTEST; i++ ){
        math_tan_results [i] = MathTan(test_angles[i]);
    }
    unsigned long end = time_us_32();
    return (end - start);
}

unsigned long RunATanMath(){
    unsigned long start = time_us_32();
    for( int i = 0; i < TRIGTEST; i++ ){
        math_atan_results [i] = MathAtan(test_angles[i]);
    }
    unsigned long end = time_us_32();
    return (end - start);
}

void InitializeAngles() {
    float current_angle = 0.0f;
    for(int i = 0; i < TRIGTEST; i++) {
        test_angles[i] = current_angle;
        current_angle += 0.00628f;
    }
}

double CalculateDifferences(double *math_array, n_fixed *lut_array){
    double total_error = 0.0;
    for (int i = 0; i < TRIGTEST; i++){
        double lut_double = (double)lut_array[i] / 65536.0;
        total_error += fabs(math_array[i] - lut_double);
    }
    return (total_error / TRIGTEST);
}

void ReportLutResult(const char* test_name, unsigned long delta_lut, unsigned long delta_math, double error) {
    printf("Test: %s | Time spent with Lut: %lu us | Time spent with math: %lu us | Error: %g \n", test_name, delta_lut, delta_math, error);
}
