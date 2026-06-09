#ifndef _MEM_HASH_TABLE
#define _MEM_HASH_TABLE

#include "wad.h"

#define TABLE_MAX_SIZE 1024

struct HashContext{
    int table[TABLE_MAX_SIZE];
};

wad CreateHashTable();

#endif