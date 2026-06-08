#include <stdio.h>
#include "hardware/timer.h"

#include "cpu_math.h"
#include "cpu_lut.h"

#ifndef LUT_MATH
#define LUT_MATH

#define PI	3.141592657

#define RADIANT_NUM     2.5f

//conversion double to BAM
#define BAM_NUM  ((RADIANT_NUM * 180) / PI) / 360 * 8192

#define TRIGTEST 1000

void RunTrigBenchmark();
void RunSin();
void RunTan();
void RunATan();

#endif