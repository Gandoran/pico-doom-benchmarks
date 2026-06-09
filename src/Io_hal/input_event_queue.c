#include "input_event_queue.h"

static EventQueueContext queue_ctx;

static void EventQueueInit(void* context, I_Hal* hal){
    queue_ctx.hal = hal;
    queue_ctx.last_pins = 0;
    queue_ctx.head = 0;
    queue_ctx.tail = 0;
}

static void EventQueueUpdate(void* context){
    uint32_t current_pins = queue_ctx.hal->read_hardware_state(queue_ctx.hal->context);
    uint32_t changed = current_pins ^ queue_ctx.last_pins;  //XOR use
    if (changed > 0) {
        queue_ctx.events[queue_ctx.head].id = changed;
        if (current_pins & changed) queue_ctx.events[queue_ctx.head].event_type = 0; //Pressed
        else queue_ctx.events[queue_ctx.head].event_type = 1; //Released
        queue_ctx.head = (queue_ctx.head + 1) % QUEUE_SIZE;
    }
    queue_ctx.last_pins = current_pins;
}

static int EventQueuePopEvent(void* context, Event* out_event){
    if (queue_ctx.head == queue_ctx.tail) return 0;
    *out_event = queue_ctx.events[queue_ctx.tail];
    return (queue_ctx.tail = (queue_ctx.tail + 1) % QUEUE_SIZE, 1);
}

I_Input CreateEventQueueInput(void){   
    return (I_Input){
        .context = &queue_ctx,
        .init = EventQueueInit,
        .update = EventQueueUpdate,
        .pop_event = EventQueuePopEvent,
    };
}