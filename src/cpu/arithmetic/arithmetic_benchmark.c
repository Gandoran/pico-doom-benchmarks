#include "arithmetic_benchmark.h"

static void ReportArithResult(const char* test_name, unsigned long start, unsigned long end, long long acc) {
    unsigned long delta = end - start;
    printf("\nArithmetic Test: %s\n", test_name);
    printf("  -> Time Spent: %lu us\n", delta);
    printf("  -> Accuracy Level:  %lli \n", acc);
}

static void RunFixedMul(){
    long long acc=0;
    unsigned long start = time_us_32();
    for(int i=0;i<NUMBERTEST;i++){
        acc += FixedMul(FIXED_FIRST_NUM,FIXED_SECOND_NUM);
    }
    unsigned long end = time_us_32();
    ReportArithResult("Fixed Point Moltiplication",start,end,acc>>16);
}

static void RunFloatMul(){
    long long acc=0;
    unsigned long start = time_us_32();
    for(int i=0;i<NUMBERTEST;i++){
        acc += FloatMul(FLOAT_FIRST_NUM,FLOAT_SECOND_NUM);
    }
    unsigned long end = time_us_32();
    ReportArithResult("Floating Point Moltiplication",start,end,acc);
}

static void RunFixedDiv(){
    long long acc=0;
    unsigned long start = time_us_32();
    for(int i=0;i<NUMBERTEST;i++){
        acc += FixedDiv(FIXED_FIRST_NUM,FIXED_SECOND_NUM);
    }
    unsigned long end = time_us_32();
    ReportArithResult("Fixed Point Division",start,end,acc>>16);
}

static void RunFloatDiv(){
    float acc=0.0f;
    unsigned long start = time_us_32();
    for(int i=0;i<NUMBERTEST;i++){
        acc += FloatDiv(FLOAT_FIRST_NUM,FLOAT_SECOND_NUM);
    }
    unsigned long end = time_us_32();
    ReportArithResult("Floating Point Division",start,end, (long long) acc);
}

void RunArithBenchmark(){
    RunFixedMul();
    RunFloatMul();
    RunFixedDiv();
    RunFloatDiv();
}