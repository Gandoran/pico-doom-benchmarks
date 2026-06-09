#ifndef _MAP_CREATION_
#define _MAP_CREATION_

#include <stddef.h>

#include "geometry.h"
#include "cpu_bsp.h"

BSPNode* GetMapRoot();
int GetMapSize();
void GetFlatMap(Wall* wall_array);

#endif