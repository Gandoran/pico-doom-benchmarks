#include "mem_hash_table.h"

static struct HashContext hash_context;

static int HashFunction(const char* name){
    unsigned long hash = 5381;
    for (int i = 0; i < 8; i++){
        hash = ((hash << 5) + hash) + name[i];
    }
    return hash % TABLE_MAX_SIZE;
}

static void HashtableInit(void* context, const v_lump* directory, int total_lumps){
    struct HashContext* hc = (struct HashContext*) context;
    for (int i = 0; i < TABLE_MAX_SIZE; i++){
        hc->table[i] = -1;
    }
    for (int i = 0; i<total_lumps; i++){
        int slot =  HashFunction(directory[i].name);
        while (hc->table[slot] != -1){
            slot = (slot + 1) % 1024;
        }
        hc->table[slot] = i;
    }   
}

static int HashTableFinder(void* context, const v_lump* directory, int total_lumps, const char* name){
    struct HashContext* hc = (struct HashContext*) context;
    int v1, v2;
    ConvertNameToInts(name, &v1, &v2);
    int slot = HashFunction(name);
    while(hc->table[slot] != -1){
        int lump_idx = hc->table[slot];
        int* lump_ints = (int*)directory[lump_idx].name;
        if (lump_ints[0] == v1 && lump_ints[1] == v2) return lump_idx;
        slot = (slot + 1) % TABLE_MAX_SIZE;
    }
    return -1;
}

wad CreateHashTable(){
    return (wad){
        .context = &hash_context,
        .init = HashtableInit,
        .find_lump = HashTableFinder,
    };
}