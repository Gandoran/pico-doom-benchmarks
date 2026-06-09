#ifndef _HAL_PICO_SDK_
#define _HAL_PICO_SDK_

#include "hal.h"

typedef struct HalContext{
    uint32_t virtual_pins;
}HalContext;

I_Hal CreatePicoHal();

void HAL_SimulateButtonPress(uint32_t button_mask);

#endif