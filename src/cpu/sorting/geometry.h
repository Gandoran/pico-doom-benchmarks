#ifndef _GEOMETRY_
#define _GEOMETRY_

typedef struct Point2D{
    float x;
    float y;
} Point2D;

typedef struct Wall{
    Point2D start;
    Point2D end;
} Wall;

#endif