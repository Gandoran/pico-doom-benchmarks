#include "mem_linear_wad.h"

static void LinearInit(void* context, const v_lump* directory, int total_lumps){}

static int LinearFinder(void* context, const v_lump* directory, int total_lumps, const char* name){
    int v1, v2;
    ConvertNameToInts(name, &v1, &v2);

    for(int i=total_lumps-1; i>=0; i--){
        int* lump_ints = (int*)directory[i].name;
        if (lump_ints[0] == v1 && lump_ints[1] == v2) return i; 
    }
    return -1;
}

wad CreateLinearWad(){
    return (wad){
        .context = NULL,
        .init =  LinearInit,
        .find_lump = LinearFinder,
    };
}