#ifndef _HAL_
#define _HAL_

#include <stdint.h>

typedef struct i_hal{
    void* context;
    uint32_t (*read_hardware_state)(void* context);
}i_hal;

#endif