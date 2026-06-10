#include "input_polling.h"

static PollingContext polling_ctx;

static void PollingInit(void* context, I_Hal* hal){
    PollingContext* ctx = (PollingContext*)context;

    ctx->hal = hal;
    ctx->last_pins = 0;
    ctx->has_event = 0;
}

static void PollingUpdate(void* context){
    PollingContext* ctx = (PollingContext*)context;

    uint32_t current_pins = ctx->hal->read_hardware_state(ctx->hal->context);
    uint32_t changed = current_pins ^ ctx->last_pins; //XOR use
    if (changed > 0) {
        ctx->current_event.id = changed; 
        if (current_pins & changed) ctx->current_event.event_type = 0; // PRESSED
        else ctx->current_event.event_type = 1; // RELEASED
        ctx->has_event = 1;
    }
    ctx->last_pins = current_pins;
}

static int PollingPopEvent(void* context, Event* out_event){
    PollingContext* ctx = (PollingContext*)context;

    if(ctx->has_event == 0) return 0;
    *out_event = ctx->current_event;
    return (ctx->has_event = 0, 1);
}

I_Input CreatePollingInput(void){
    return (I_Input){
        .context = &polling_ctx,
        .init = PollingInit,
        .update = PollingUpdate,
        .pop_event = PollingPopEvent,
    };
}