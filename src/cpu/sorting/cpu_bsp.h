#ifndef _CPU_BSP_
#define _CPU_BSP_

#include "pico/stdlib.h"

#include "geometry.h"

typedef struct BSPNode {
    Wall divider;
    struct BSPNode* front;
    struct BSPNode* back;
} BSPNode;

void BspSort(BSPNode* node, Point2D viewer, Wall* output_walls, int* output_index);

#endif  