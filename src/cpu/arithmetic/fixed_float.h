#include <stdio.h>
#include "hardware/timer.h"

#include "cpu_fixed.h"
#include "cpu_float.h"

#ifndef FIXED_FLOAT_
#define FIXED_FLOAT_

#define FLOAT_FIRST_NUM     2.5f
#define FLOAT_SECOND_NUM    4.0f

//conversion floating point to fixed point
#define FIXED_FIRST_NUM     (n_fixed)(FLOAT_FIRST_NUM * (1 << FRACBITS))
#define FIXED_SECOND_NUM    (n_fixed)(FLOAT_SECOND_NUM * (1 << FRACBITS))

#define NUMBERTEST 1000

void RunArithBenchmark();
void RunFixedMul();
void RunFloatMul();
void RunFixedDiv();
void RunFloatDiv();

void ReportResult(const char* test_name, unsigned long start, unsigned long end, long long acc);

#endif