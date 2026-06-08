#ifndef _GEOMETRY_
#define _GEOMETRY_

typedef struct {
    float x;
    float y;
} Point2D;

typedef struct {
    Point2D start;
    Point2D end;
} Wall;

#endif