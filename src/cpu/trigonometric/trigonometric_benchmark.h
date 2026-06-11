#ifndef LUT_MATH
#define LUT_MATH

#include <stdio.h>
#include "hardware/timer.h"

#include "src/cpu/arithmetic/cpu_fixed.h"

#include "cpu_math.h"
#include "cpu_lut.h"

#define PI	3.141592657

#define RADIANT_NUM     2.5f

//conversion double to BAM with a parametric macro
#define RAD_TO_BAM(rad)  (angle_bam)((rad) * (8192.0f / (2.0f * PI)))

#define TRIGTEST 1000

void RunTrigBenchmark();

#endif