#include "hal_pico_sdk.h"

static HalContext pico_hw_state;

static uint32_t PicoReadHardware(void* context){
    HalContext* hw_context = (HalContext*) context;
    return hw_context->virtual_pins;
}

I_Hal CreatePicoHal(){
    return (I_Hal){
        .context = &pico_hw_state,
        .read_hardware_state = PicoReadHardware,
    };
}

void HAL_SimulateButtonPress(uint32_t button_mask){
    //Simulate the button pressed
    pico_hw_state.virtual_pins = button_mask;
}