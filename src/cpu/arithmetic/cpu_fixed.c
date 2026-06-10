#include "cpu_fixed.h"

n_fixed FixedMul(n_fixed a, n_fixed b){
    return ((long long) a * (long long) b) >> FRACBITS;
}

n_fixed FixedDiv(n_fixed a, n_fixed b){
     if (b == 0) return (a >= 0) ? MAXINT : MININT;
    if( (llabs(a) >> 15) >= llabs(b) ) return (a^b)<0 ? MININT : MAXINT;
    return ((long long) a << FRACBITS) / (long long) b ;
}