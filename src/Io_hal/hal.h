#ifndef _HAL_
#define _HAL_

#include <stdint.h>

typedef struct I_Hal{
    void* context;
    uint32_t (*read_hardware_state)(void* context);
}I_Hal;

#endif