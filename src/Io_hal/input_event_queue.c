#include "input_event_queue.h"

static EventQueueContext queue_ctx;

static void EventQueueInit(void* context, I_Hal* hal){
    EventQueueContext* ctx = (EventQueueContext*)context;

    ctx->hal = hal;
    ctx->last_pins = 0;
    ctx->head = 0;
    ctx->tail = 0;
}

static void EventQueueUpdate(void* context){
    EventQueueContext* ctx = (EventQueueContext*)context;

    uint32_t current_pins = ctx->hal->read_hardware_state(ctx->hal->context);
    uint32_t changed = current_pins ^ ctx->last_pins;  //XOR use
    if (changed > 0) {
        ctx->events[ctx->head].id = changed;
        if (current_pins & changed) ctx->events[ctx->head].event_type = 0; //Pressed
        else ctx->events[ctx->head].event_type = 1; //Released
        ctx->head = (ctx->head + 1) % QUEUE_SIZE;
    }
    ctx->last_pins = current_pins;
}

static int EventQueuePopEvent(void* context, Event* out_event){
    EventQueueContext* ctx = (EventQueueContext*)context;
    if (ctx->head == ctx->tail) return 0;
    *out_event = ctx->events[ctx->tail];
    return (ctx->tail = (ctx->tail + 1) % QUEUE_SIZE, 1);
}

I_Input CreateEventQueueInput(void){   
    return (I_Input){
        .context = &queue_ctx,
        .init = EventQueueInit,
        .update = EventQueueUpdate,
        .pop_event = EventQueuePopEvent,
    };
}