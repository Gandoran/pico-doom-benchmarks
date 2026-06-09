#ifndef _HAL_PICO_SDK_
#define _HAL_PICO_SDK_

#include "hal.h"

typedef struct hal_context{
    uint32_t virtual_pins;
}hal_context;

i_hal CreatePicoHal();

void HAL_SimulateButtonPress(uint32_t button_mask);

#endif