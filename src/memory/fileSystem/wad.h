#ifndef _WAD_
#define _WAD_

#include <stdlib.h>
#include <stdint.h>
#include <string.h>

typedef struct v_lump{
    char name[8];
    uint32_t size;
}v_lump;

typedef struct wad{
    void* context;
    void (*init)(void* context, const v_lump* directory, int total_lumps);
    int (*find_lump)(void* context, const v_lump* directory, int total_lumps, const char* name);
}wad;

static inline void ConvertNameToInts(const char* name, int* v1, int* v2) {
    //using the compare trick from doom without strcmp
    union {
        char s[9]; 
        int  x[2];
    } name8;

    //byte clear
    strncpy(name8.s, name, 8);
    name8.s[8] = '\0'; 

    *v1 = name8.x[0];
    *v2 = name8.x[1];
}

#endif