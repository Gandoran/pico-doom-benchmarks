#include "allocator_benchmark.h"

static uint32_t ExecuteAllocatorWorkload(Allocator* engine) {
    void* temp_ptrs[50];
    uint32_t start = time_us_32();
    for (int i = 0; i < 100; i++) {
        for (int k = 0; k < 50; k++) {
            size_t fake_size = 16 + (k % 4) * 8;
            temp_ptrs[k] = engine->alloc(engine->context, fake_size);
        }
        for (int k = 0; k < 50; k++) {
            if (temp_ptrs[k]) {
                engine->free_mem(engine->context, temp_ptrs[k]);
            }
        }
    }
    uint32_t end = time_us_32();
    return end - start;
}

static void ReportAllocatorResult(const char* test_name, uint32_t delta, int max_blocks, const char* frag_status){
    printf("Test: %s | Time spent: %lu us | Max 8-byte Blocks Bounded: %d | Coalescing Fragmentation: %s \n", test_name, delta, max_blocks, frag_status);
}


void RunAllocatorBenchmark(){
    Allocator std_allocator_engine = CreateStdAllocator();
    Allocator zmem_allocator_engine = CreateZMemAllocator();
    
    std_allocator_engine.init(std_allocator_engine.context,0);
    zmem_allocator_engine.init(zmem_allocator_engine.context,MEMORY_SIZE_TEST);

    uint32_t std_stress_time = 0;
    int std_max_blocks = 0;
    const char* std_frag_status = "FAILED";

    uint32_t zmem_stress_time = 0;
    int zmem_max_blocks = 0;
    const char* zmem_frag_status = "FAILED";

    void* ptr_array[FRAG_BLOCKS_COUNT];

    // Invio dei dati accumulati al report unificato
    ReportAllocatorResult("Standard Allocator ", std_stress_time, std_max_blocks, std_frag_status);
    ReportAllocatorResult("ZMemory Allocator ", zmem_stress_time, zmem_max_blocks, zmem_frag_status);
}