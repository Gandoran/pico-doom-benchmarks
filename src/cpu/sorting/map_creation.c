#include "map_creation.h"

static Wall wall_left  = {{0.0f, 0.0f}, {0.0f, 10.0f}};
static Wall wall_right = {{10.0f, 0.0f}, {10.0f, 10.0f}};
static Wall wall_root  = {{5.0f, 0.0f}, {5.0f, 10.0f}};

static BSPNode node_left  = { .divider = {{0.0f, 0.0f}, {0.0f, 10.0f}}, .front = NULL, .back = NULL };
static BSPNode node_right = { .divider = {{10.0f, 0.0f}, {10.0f, 10.0f}}, .front = NULL, .back = NULL };
static BSPNode node_root  = { .divider = {{5.0f, 0.0f}, {5.0f, 10.0f}}, .front = &node_left, .back = &node_right };

BSPNode* GetMapRoot() {
    return &node_root;
}

int GetMapSize() {
    return 3; 
}

void GetFlatMap(Wall* wall_array) {
    wall_array[0] = wall_left;
    wall_array[1] = wall_right;
    wall_array[2] = wall_root;
}