#include <stdio.h>
#include "pico/stdlib.h"

#include "src/cpu/arithmetic/arithmetic_benchmark.h"
#include "src/cpu/trigonometric/trigonometric_benchmark.h"
#include "src/cpu/sorting/sorting_benchmark.h"


int main()
{
    stdio_init_all();
    while (1) {
        printf("\n--- STARTING BENCHMARK SESSION ---\n");
        //RunArithBenchmark();
        //RunTrigBenchmark();
        RunSortingBenchmark();
        sleep_ms(5000);
    }
}
