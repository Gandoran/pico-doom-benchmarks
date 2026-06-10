#ifndef _FIXED_
#define _FIXED_

#include <stdlib.h>

#define MAXINT ((int)0x7fffffff)
#define MININT ((int)0x80000000)

#define FRACBITS		16
#define FRACUNIT		(1<<FRACBITS)

typedef int n_fixed;

n_fixed FixedMul	(n_fixed a, n_fixed b);
n_fixed FixedDiv	(n_fixed a, n_fixed b);

#endif