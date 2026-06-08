#include <stdio.h>
#include "hardware/timer.h"

#include "src/cpu/arithmetic/cpu_fixed.h"

#include "cpu_math.h"
#include "cpu_lut.h"

#ifndef LUT_MATH
#define LUT_MATH

#define PI	3.141592657

#define RADIANT_NUM     2.5f

//conversion double to BAM with a parametric macro
#define RAD_TO_BAM(rad)  (angle_bam)((rad) * (8192.0f / (2.0f * PI)))

#define TRIGTEST 1000

void InitializeAngles();

void RunTrigBenchmark();

unsigned long RunSinLut();
unsigned long RunTanLut();
unsigned long RunATanLut();

unsigned long RunSinMath();
unsigned long RunTanMath();
unsigned long RunATanMath();

double CalculateDifferences(double *math_array, n_fixed *lut_array);

void ReportResult(const char* test_name, unsigned long delta_lut, unsigned long delta_math, double error);

#endif