#ifndef _IO_HAL_BENCHMARK_
#define _IO_HAL_BENCHMARK_

#include <stdio.h>
#include "hardware/timer.h"

#include "hal_pico_sdk.h"

#include "input_polling.h"
#include "input_event_queue.h"

#define INPUT_STRESS_COUNT 5000

void RunIoHalBenchmark();

#endif