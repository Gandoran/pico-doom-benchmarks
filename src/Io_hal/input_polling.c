#include "input_polling.h"

static PollingContext polling_ctx;

static void PollingInit(void* context, I_Hal* hal){
    polling_ctx.hal = hal;
    polling_ctx.last_pins = 0;
    polling_ctx.has_event = 0;
}

static void PollingUpdate(void* context){
    uint32_t current_pins = polling_ctx.hal->read_hardware_state(polling_ctx.hal->context);
    uint32_t changed = current_pins ^ polling_ctx.last_pins; //XOR use
    if (changed > 0) {
        polling_ctx.current_event.id = changed; 
        if (current_pins & changed) polling_ctx.current_event.event_type = 0; // PRESSED
        else polling_ctx.current_event.event_type = 1; // RELEASED
        polling_ctx.has_event = 1;
    }
    polling_ctx.last_pins = current_pins;
}

static int PollingPopEvent(void* context, Event* out_event){
    if(polling_ctx.has_event == 0) return 0;
    *out_event = polling_ctx.current_event;
    return (polling_ctx.has_event = 0, 1);
}

I_Input CreatePollingInput(void){
    return (I_Input){
        .context = &polling_ctx,
        .init = PollingInit,
        .update = PollingUpdate,
        .pop_event = PollingPopEvent,
    };
}