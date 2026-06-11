#ifndef _CPU_LUT_
#define _CPU_LUT_

#include "src/cpu/arithmetic/cpu_fixed.h"

#include <stdint.h>

#define ANGLES		8192
#define MASK		(ANGLES-1)

//use of Binary Angle Measurement (BAM)
typedef unsigned angle_bam;

extern const n_fixed sin_table[ANGLES];
extern const n_fixed tan_table[ANGLES/2];
extern const angle_bam atan_table[ANGLES/2];

n_fixed LutSin(angle_bam a);
n_fixed LutTan(angle_bam a);
angle_bam LutAtan(n_fixed a);

#endif