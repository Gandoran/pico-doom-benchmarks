#include <stdio.h>
#include "pico/stdlib.h"
#include "src/cpu/fixed_float.h"


int main()
{
    stdio_init_all();
    while (1) {
        printf("\n--- STARTING BENCHMARK SESSION ---\n");
        RunBenchmark();
        sleep_ms(5000);
    }
}
