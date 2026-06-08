#include "cpu_brute_force.h"

static Point2D current_robot_pos;

void RunQuickSort(Point2D robot_pos, Wall* walls, int wall_count){
    qsort(walls, wall_count, sizeof(float), GetWallDistance);
}

//Calcolate the Wall Distance Using Pitagora Thoreme
static float GetWallDistance(Point2D robot, Wall wall){
    float mid_x = (wall.start.x + wall.end.x) / 2.0f;
    float mid_y = (wall.start.y + wall.end.y) / 2.0f;
    
    float dx = robot.x - mid_x;
    float dy = robot.y - mid_y;
    
    return sqrtf((dx * dx) + (dy * dy));
}

static int CompareWalls(const void* a, const void* b) {
    const Wall* wallA = (const Wall*)a;
    const Wall* wallB = (const Wall*)b;
    
    float distA = GetWallDistance(current_robot_pos, *wallA);
    float distB = GetWallDistance(current_robot_pos, *wallB);
    
    if (distA < distB) return -1;
    if (distA > distB) return 1;
    return 0;
}

void RunQuickSort(Point2D robot_pos, Wall* walls, int wall_count) {
    current_robot_pos = robot_pos;
    
    //use of C quickSort 
    qsort(walls, wall_count, sizeof(Wall), CompareWalls);
}