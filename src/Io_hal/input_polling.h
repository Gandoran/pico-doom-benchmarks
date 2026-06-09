#ifndef _INPUT_POLLING_
#define _INPUT_POLLING_

#include "input.h"

typedef struct PollingContext{
    I_Hal* hal;
    uint32_t last_pins;
    int has_event;
    Event current_event;
}PollingContext;

I_Input CreatePollingInput(void);

#endif