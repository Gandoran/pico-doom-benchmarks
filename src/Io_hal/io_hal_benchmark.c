#include "io_hal_benchmark.h"

typedef struct Benchmark_Result{
    uint32_t time;
    int lost_events;
} Benchmark_Result;

static void SimulateHardwarePulse(I_Input* engine) {
    
    HAL_SimulateButtonPress(0x01);
    engine->update(engine->context);

    HAL_SimulateButtonPress(0x00);
    engine->update(engine->context);
}

static int DrainEventQueue(I_Input* engine) {
    int count = 0;
    Event ev;
    while (engine->pop_event(engine->context, &ev)) count++;
    return count;
}

static Benchmark_Result ExecuteInputWorkload(I_Input* engine){
    int expected_events = 0;
    int processed_events = 0;

    uint32_t start = time_us_32();
    for(int i = 0; i < INPUT_STRESS_COUNT; i++){
        SimulateHardwarePulse(engine);
        expected_events += 2;
        processed_events += DrainEventQueue(engine);
    }
    uint32_t end = time_us_32();
    return (Benchmark_Result){
        .time = end - start,
        .lost_events = ((expected_events - processed_events) < 0)? 0 : expected_events - processed_events
    };
}

static void ReportIoHalResult(const char* test_name, Benchmark_Result result, size_t memory_usage){
    double error_percentage = ((double)result.lost_events / (INPUT_STRESS_COUNT * 2)) * 100.0;
    printf("Test: %s | Time spent: %lu us | Memory Used: %zu | Input Lost: %d eventi | Error Percentage: %.2f\n", test_name, result.time, memory_usage, result.lost_events, error_percentage);
}

void RunIoHalBenchmark(){
    I_Hal hal = CreatePicoHal();
    I_Input polling_input_engine = CreatePollingInput();
    I_Input event_queue_engine = CreateEventQueueInput();

    polling_input_engine.init(polling_input_engine.context,&hal);
    event_queue_engine.init(event_queue_engine.context,&hal);

    ReportIoHalResult("Polling",ExecuteInputWorkload(&polling_input_engine),sizeof(PollingContext));
    ReportIoHalResult("Event Queue",ExecuteInputWorkload(&event_queue_engine),sizeof(EventQueueContext));
}