#ifndef _INPUT_EVENT_QUEUE_
#define _INPUT_EVENT_QUEUE_

#include "input.h"

#define QUEUE_SIZE 16

typedef struct EventQueueContext{
    I_Hal* hal;
    uint32_t last_pins;
    Event events[QUEUE_SIZE];
    int head;
    int tail;
}EventQueueContext;

I_Input CreateEventQueueInput(void);

#endif