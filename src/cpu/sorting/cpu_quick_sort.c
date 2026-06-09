#include "cpu_quick_sort.h"

static Point2D current_item_pos;

//Calcolate the Wall Distance Using Pitagora Thoreme
static float GetWallDistance(Point2D item, Wall wall){
    float mid_x = (wall.start.x + wall.end.x) / 2.0f;
    float mid_y = (wall.start.y + wall.end.y) / 2.0f;
    
    float dx = item.x - mid_x;
    float dy = item.y - mid_y;
    
    return sqrtf((dx * dx) + (dy * dy));
}

static int CompareWalls(const void* a, const void* b) {
    const Wall* wallA = (const Wall*)a;
    const Wall* wallB = (const Wall*)b;
    
    float distA = GetWallDistance(current_item_pos, *wallA);
    float distB = GetWallDistance(current_item_pos, *wallB);
    
    if (distA < distB) return -1;
    if (distA > distB) return 1;
    return 0;
}

void QuickSort(Point2D item_pos, Wall* walls, int wall_count) {
    current_item_pos = item_pos;
    
    //use of C quickSort 
    qsort(walls, wall_count, sizeof(Wall), CompareWalls);
}