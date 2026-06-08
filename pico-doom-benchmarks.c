#include <stdio.h>
#include "pico/stdlib.h"
#include "src/cpu/arithmetic/fixed_float.h"


int main()
{
    stdio_init_all();
    while (1) {
        printf("\n--- STARTING BENCHMARK SESSION ---\n");
        RunArithBenchmark();
        sleep_ms(5000);
    }
}
