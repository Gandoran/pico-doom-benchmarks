#ifndef _INPUT_
#define _INPUT_

#include "hal.h"

typedef struct event{
    int event_type;
    int id;
}event;

typedef struct i_input{
    void* context;
    void (*init) (void* context, i_hal* hal);
    void (*update) (void* context);
    int (*pop_event) (void* context, event* out_event);
}i_input;

#endif