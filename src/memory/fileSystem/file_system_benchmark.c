#include "file_system_benchmark.h"

static uint32_t ExecuteSearchWorkload(wad* engine){
    uint32_t start = time_us_32();
    for(int i = 0; i < FILESYSTEMTEST; i++){
        for(int k = 0; k < TOTAL_QUERIES; k++ ){
            engine->find_lump(engine->context,virtual_wad_directory,TOTAL_LUMPS,search_queries[k]);
        }
    }
    uint32_t end = time_us_32();
    return end - start;
}

static void ReportSortingResult(const char* test_name, uint32_t delta, size_t memory_usage){
    printf("Test: %s | Time spent: %lu us\n | Memory Used: %zu ", test_name, delta, memory_usage);
}

void RunFileSystemBenchmark(){
    wad linear_wad_engine = CreateLinearWad();
    wad hash_table_engine = CreateHashTable();

    linear_wad_engine.init(linear_wad_engine.context, virtual_wad_directory, TOTAL_LUMPS);
    hash_table_engine.init(hash_table_engine.context, virtual_wad_directory, TOTAL_LUMPS);

    ReportSortingResult("Linear Wad",ExecuteSearchWorkload(&linear_wad_engine),0);
    ReportSortingResult("Hash Table",ExecuteSearchWorkload(&hash_table_engine),sizeof(struct HashContext));
}