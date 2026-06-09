#ifndef _INPUT_
#define _INPUT_

#include "hal.h"

typedef struct Event{
    int event_type;
    int id;
}Event;

typedef struct I_Input{
    void* context;
    void (*init) (void* context, I_Hal* hal);
    void (*update) (void* context);
    int (*pop_event) (void* context, Event* out_event);
}I_Input;

#endif