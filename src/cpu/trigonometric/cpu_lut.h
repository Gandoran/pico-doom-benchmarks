#include "fixed.h"

#ifndef _CPU_LUT_
#define _CPU_LUT_

//use of Binary Angle Measurement (BAM)
typedef unsigned angle_bam;

#define ANGLES		8192
#define MASK		(ANGLES-1)

n_fixed LutSin(angle_bam a);
n_fixed LutTan(angle_bam a);
n_fixed LutAtan(angle_bam a);

#endif