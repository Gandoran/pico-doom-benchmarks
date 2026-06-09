#include "cpu_bsp.h"

static float CalcDet(Point2D item_pos, Wall divider){
    float det_x = (divider.start.x - divider.end.x) * (item_pos.y - divider.start.y);
    float det_y =  (divider.start.y - divider.end.y) * (item_pos.x - divider.start.x);
    return  det_x - det_y;
}

void BspSort(BSPNode* node, Point2D viewer, Wall* output_walls, int* output_index) {
    if (node == NULL) return;

    float det = CalcDet(viewer, node->divider);

    if (det > 0) {
        BspSort(node->front, viewer, output_walls, output_index);

        output_walls[(*output_index)++] = node->divider;

        BspSort(node->back, viewer, output_walls, output_index);
    } 
    else {
        BspSort(node->back, viewer, output_walls, output_index);

        output_walls[(*output_index)++] = node->divider;

        BspSort(node->front, viewer, output_walls, output_index);
    }
}
