#include "hal_pico_sdk.h"

static hal_context pico_hw_state;

static uint32_t PicoReadHardware(void* context){
    hal_context* hw_context = (hal_context*) context;
    return hw_context->virtual_pins;
}

i_hal CreatePicoHal(){
    return (i_hal){
        .context = &pico_hw_state,
        .read_hardware_state = PicoReadHardware,
    };
}

void HAL_SimulateButtonPress(uint32_t button_mask){
    //Simulate the button pressed
    pico_hw_state.virtual_pins = button_mask;
}