#include "map_creation.h"

static BSPNode nodes[63] = {
    [0] = {
        .divider = { { 50.0f, 0.0f }, { 50.0f, 100.0f } },
        .front = &nodes[1],
        .back = &nodes[32]
    },
    [1] = {
        .divider = { { 50.0f, 50.0f }, { 100.0f, 50.0f } },
        .front = &nodes[2],
        .back = &nodes[17]
    },
    [2] = {
        .divider = { { 75.0f, 50.0f }, { 75.0f, 100.0f } },
        .front = &nodes[3],
        .back = &nodes[10]
    },
    [3] = {
        .divider = { { 75.0f, 75.0f }, { 100.0f, 75.0f } },
        .front = &nodes[4],
        .back = &nodes[7]
    },
    [4] = {
        .divider = { { 87.5f, 75.0f }, { 87.5f, 100.0f } },
        .front = &nodes[5],
        .back = &nodes[6]
    },
    [5] = {
        .divider = { { 87.5f, 87.5f }, { 100.0f, 87.5f } },
        .front = NULL,
        .back = NULL
    },
    [6] = {
        .divider = { { 75.0f, 87.5f }, { 87.5f, 87.5f } },
        .front = NULL,
        .back = NULL
    },
    [7] = {
        .divider = { { 87.5f, 50.0f }, { 87.5f, 75.0f } },
        .front = &nodes[8],
        .back = &nodes[9]
    },
    [8] = {
        .divider = { { 87.5f, 62.5f }, { 100.0f, 62.5f } },
        .front = NULL,
        .back = NULL
    },
    [9] = {
        .divider = { { 75.0f, 62.5f }, { 87.5f, 62.5f } },
        .front = NULL,
        .back = NULL
    },
    [10] = {
        .divider = { { 50.0f, 75.0f }, { 75.0f, 75.0f } },
        .front = &nodes[11],
        .back = &nodes[14]
    },
    [11] = {
        .divider = { { 62.5f, 75.0f }, { 62.5f, 100.0f } },
        .front = &nodes[12],
        .back = &nodes[13]
    },
    [12] = {
        .divider = { { 62.5f, 87.5f }, { 75.0f, 87.5f } },
        .front = NULL,
        .back = NULL
    },
    [13] = {
        .divider = { { 50.0f, 87.5f }, { 62.5f, 87.5f } },
        .front = NULL,
        .back = NULL
    },
    [14] = {
        .divider = { { 62.5f, 50.0f }, { 62.5f, 75.0f } },
        .front = &nodes[15],
        .back = &nodes[16]
    },
    [15] = {
        .divider = { { 62.5f, 62.5f }, { 75.0f, 62.5f } },
        .front = NULL,
        .back = NULL
    },
    [16] = {
        .divider = { { 50.0f, 62.5f }, { 62.5f, 62.5f } },
        .front = NULL,
        .back = NULL
    },
    [17] = {
        .divider = { { 75.0f, 0.0f }, { 75.0f, 50.0f } },
        .front = &nodes[18],
        .back = &nodes[25]
    },
    [18] = {
        .divider = { { 75.0f, 25.0f }, { 100.0f, 25.0f } },
        .front = &nodes[19],
        .back = &nodes[22]
    },
    [19] = {
        .divider = { { 87.5f, 25.0f }, { 87.5f, 50.0f } },
        .front = &nodes[20],
        .back = &nodes[21]
    },
    [20] = {
        .divider = { { 87.5f, 37.5f }, { 100.0f, 37.5f } },
        .front = NULL,
        .back = NULL
    },
    [21] = {
        .divider = { { 75.0f, 37.5f }, { 87.5f, 37.5f } },
        .front = NULL,
        .back = NULL
    },
    [22] = {
        .divider = { { 87.5f, 0.0f }, { 87.5f, 25.0f } },
        .front = &nodes[23],
        .back = &nodes[24]
    },
    [23] = {
        .divider = { { 87.5f, 12.5f }, { 100.0f, 12.5f } },
        .front = NULL,
        .back = NULL
    },
    [24] = {
        .divider = { { 75.0f, 12.5f }, { 87.5f, 12.5f } },
        .front = NULL,
        .back = NULL
    },
    [25] = {
        .divider = { { 50.0f, 25.0f }, { 75.0f, 25.0f } },
        .front = &nodes[26],
        .back = &nodes[29]
    },
    [26] = {
        .divider = { { 62.5f, 25.0f }, { 62.5f, 50.0f } },
        .front = &nodes[27],
        .back = &nodes[28]
    },
    [27] = {
        .divider = { { 62.5f, 37.5f }, { 75.0f, 37.5f } },
        .front = NULL,
        .back = NULL
    },
    [28] = {
        .divider = { { 50.0f, 37.5f }, { 62.5f, 37.5f } },
        .front = NULL,
        .back = NULL
    },
    [29] = {
        .divider = { { 62.5f, 0.0f }, { 62.5f, 25.0f } },
        .front = &nodes[30],
        .back = &nodes[31]
    },
    [30] = {
        .divider = { { 62.5f, 12.5f }, { 75.0f, 12.5f } },
        .front = NULL,
        .back = NULL
    },
    [31] = {
        .divider = { { 50.0f, 12.5f }, { 62.5f, 12.5f } },
        .front = NULL,
        .back = NULL
    },
    [32] = {
        .divider = { { 0.0f, 50.0f }, { 50.0f, 50.0f } },
        .front = &nodes[33],
        .back = &nodes[48]
    },
    [33] = {
        .divider = { { 25.0f, 50.0f }, { 25.0f, 100.0f } },
        .front = &nodes[34],
        .back = &nodes[41]
    },
    [34] = {
        .divider = { { 25.0f, 75.0f }, { 50.0f, 75.0f } },
        .front = &nodes[35],
        .back = &nodes[38]
    },
    [35] = {
        .divider = { { 37.5f, 75.0f }, { 37.5f, 100.0f } },
        .front = &nodes[36],
        .back = &nodes[37]
    },
    [36] = {
        .divider = { { 37.5f, 87.5f }, { 50.0f, 87.5f } },
        .front = NULL,
        .back = NULL
    },
    [37] = {
        .divider = { { 25.0f, 87.5f }, { 37.5f, 87.5f } },
        .front = NULL,
        .back = NULL
    },
    [38] = {
        .divider = { { 37.5f, 50.0f }, { 37.5f, 75.0f } },
        .front = &nodes[39],
        .back = &nodes[40]
    },
    [39] = {
        .divider = { { 37.5f, 62.5f }, { 50.0f, 62.5f } },
        .front = NULL,
        .back = NULL
    },
    [40] = {
        .divider = { { 25.0f, 62.5f }, { 37.5f, 62.5f } },
        .front = NULL,
        .back = NULL
    },
    [41] = {
        .divider = { { 0.0f, 75.0f }, { 25.0f, 75.0f } },
        .front = &nodes[42],
        .back = &nodes[45]
    },
    [42] = {
        .divider = { { 12.5f, 75.0f }, { 12.5f, 100.0f } },
        .front = &nodes[43],
        .back = &nodes[44]
    },
    [43] = {
        .divider = { { 12.5f, 87.5f }, { 25.0f, 87.5f } },
        .front = NULL,
        .back = NULL
    },
    [44] = {
        .divider = { { 0.0f, 87.5f }, { 12.5f, 87.5f } },
        .front = NULL,
        .back = NULL
    },
    [45] = {
        .divider = { { 12.5f, 50.0f }, { 12.5f, 75.0f } },
        .front = &nodes[46],
        .back = &nodes[47]
    },
    [46] = {
        .divider = { { 12.5f, 62.5f }, { 25.0f, 62.5f } },
        .front = NULL,
        .back = NULL
    },
    [47] = {
        .divider = { { 0.0f, 62.5f }, { 12.5f, 62.5f } },
        .front = NULL,
        .back = NULL
    },
    [48] = {
        .divider = { { 25.0f, 0.0f }, { 25.0f, 50.0f } },
        .front = &nodes[49],
        .back = &nodes[56]
    },
    [49] = {
        .divider = { { 25.0f, 25.0f }, { 50.0f, 25.0f } },
        .front = &nodes[50],
        .back = &nodes[53]
    },
    [50] = {
        .divider = { { 37.5f, 25.0f }, { 37.5f, 50.0f } },
        .front = &nodes[51],
        .back = &nodes[52]
    },
    [51] = {
        .divider = { { 37.5f, 37.5f }, { 50.0f, 37.5f } },
        .front = NULL,
        .back = NULL
    },
    [52] = {
        .divider = { { 25.0f, 37.5f }, { 37.5f, 37.5f } },
        .front = NULL,
        .back = NULL
    },
    [53] = {
        .divider = { { 37.5f, 0.0f }, { 37.5f, 25.0f } },
        .front = &nodes[54],
        .back = &nodes[55]
    },
    [54] = {
        .divider = { { 37.5f, 12.5f }, { 50.0f, 12.5f } },
        .front = NULL,
        .back = NULL
    },
    [55] = {
        .divider = { { 25.0f, 12.5f }, { 37.5f, 12.5f } },
        .front = NULL,
        .back = NULL
    },
    [56] = {
        .divider = { { 0.0f, 25.0f }, { 25.0f, 25.0f } },
        .front = &nodes[57],
        .back = &nodes[60]
    },
    [57] = {
        .divider = { { 12.5f, 25.0f }, { 12.5f, 50.0f } },
        .front = &nodes[58],
        .back = &nodes[59]
    },
    [58] = {
        .divider = { { 12.5f, 37.5f }, { 25.0f, 37.5f } },
        .front = NULL,
        .back = NULL
    },
    [59] = {
        .divider = { { 0.0f, 37.5f }, { 12.5f, 37.5f } },
        .front = NULL,
        .back = NULL
    },
    [60] = {
        .divider = { { 12.5f, 0.0f }, { 12.5f, 25.0f } },
        .front = &nodes[61],
        .back = &nodes[62]
    },
    [61] = {
        .divider = { { 12.5f, 12.5f }, { 25.0f, 12.5f } },
        .front = NULL,
        .back = NULL
    },
    [62] = {
        .divider = { { 0.0f, 12.5f }, { 12.5f, 12.5f } },
        .front = NULL,
        .back = NULL
    },
};

static Wall flat_map[63] = {
    { { 87.5f, 87.5f }, { 100.0f, 87.5f } },
    { { 75.0f, 87.5f }, { 87.5f, 87.5f } },
    { { 87.5f, 75.0f }, { 87.5f, 100.0f } },
    { { 87.5f, 62.5f }, { 100.0f, 62.5f } },
    { { 75.0f, 62.5f }, { 87.5f, 62.5f } },
    { { 87.5f, 50.0f }, { 87.5f, 75.0f } },
    { { 75.0f, 75.0f }, { 100.0f, 75.0f } },
    { { 62.5f, 87.5f }, { 75.0f, 87.5f } },
    { { 50.0f, 87.5f }, { 62.5f, 87.5f } },
    { { 62.5f, 75.0f }, { 62.5f, 100.0f } },
    { { 62.5f, 62.5f }, { 75.0f, 62.5f } },
    { { 50.0f, 62.5f }, { 62.5f, 62.5f } },
    { { 62.5f, 50.0f }, { 62.5f, 75.0f } },
    { { 50.0f, 75.0f }, { 75.0f, 75.0f } },
    { { 75.0f, 50.0f }, { 75.0f, 100.0f } },
    { { 87.5f, 37.5f }, { 100.0f, 37.5f } },
    { { 75.0f, 37.5f }, { 87.5f, 37.5f } },
    { { 87.5f, 25.0f }, { 87.5f, 50.0f } },
    { { 87.5f, 12.5f }, { 100.0f, 12.5f } },
    { { 75.0f, 12.5f }, { 87.5f, 12.5f } },
    { { 87.5f, 0.0f }, { 87.5f, 25.0f } },
    { { 75.0f, 25.0f }, { 100.0f, 25.0f } },
    { { 62.5f, 37.5f }, { 75.0f, 37.5f } },
    { { 50.0f, 37.5f }, { 62.5f, 37.5f } },
    { { 62.5f, 25.0f }, { 62.5f, 50.0f } },
    { { 62.5f, 12.5f }, { 75.0f, 12.5f } },
    { { 50.0f, 12.5f }, { 62.5f, 12.5f } },
    { { 62.5f, 0.0f }, { 62.5f, 25.0f } },
    { { 50.0f, 25.0f }, { 75.0f, 25.0f } },
    { { 75.0f, 0.0f }, { 75.0f, 50.0f } },
    { { 50.0f, 50.0f }, { 100.0f, 50.0f } },
    { { 37.5f, 87.5f }, { 50.0f, 87.5f } },
    { { 25.0f, 87.5f }, { 37.5f, 87.5f } },
    { { 37.5f, 75.0f }, { 37.5f, 100.0f } },
    { { 37.5f, 62.5f }, { 50.0f, 62.5f } },
    { { 25.0f, 62.5f }, { 37.5f, 62.5f } },
    { { 37.5f, 50.0f }, { 37.5f, 75.0f } },
    { { 25.0f, 75.0f }, { 50.0f, 75.0f } },
    { { 12.5f, 87.5f }, { 25.0f, 87.5f } },
    { { 0.0f, 87.5f }, { 12.5f, 87.5f } },
    { { 12.5f, 75.0f }, { 12.5f, 100.0f } },
    { { 12.5f, 62.5f }, { 25.0f, 62.5f } },
    { { 0.0f, 62.5f }, { 12.5f, 62.5f } },
    { { 12.5f, 50.0f }, { 12.5f, 75.0f } },
    { { 0.0f, 75.0f }, { 25.0f, 75.0f } },
    { { 25.0f, 50.0f }, { 25.0f, 100.0f } },
    { { 37.5f, 37.5f }, { 50.0f, 37.5f } },
    { { 25.0f, 37.5f }, { 37.5f, 37.5f } },
    { { 37.5f, 25.0f }, { 37.5f, 50.0f } },
    { { 37.5f, 12.5f }, { 50.0f, 12.5f } },
    { { 25.0f, 12.5f }, { 37.5f, 12.5f } },
    { { 37.5f, 0.0f }, { 37.5f, 25.0f } },
    { { 25.0f, 25.0f }, { 50.0f, 25.0f } },
    { { 12.5f, 37.5f }, { 25.0f, 37.5f } },
    { { 0.0f, 37.5f }, { 12.5f, 37.5f } },
    { { 12.5f, 25.0f }, { 12.5f, 50.0f } },
    { { 12.5f, 12.5f }, { 25.0f, 12.5f } },
    { { 0.0f, 12.5f }, { 12.5f, 12.5f } },
    { { 12.5f, 0.0f }, { 12.5f, 25.0f } },
    { { 0.0f, 25.0f }, { 25.0f, 25.0f } },
    { { 25.0f, 0.0f }, { 25.0f, 50.0f } },
    { { 0.0f, 50.0f }, { 50.0f, 50.0f } },
    { { 50.0f, 0.0f }, { 50.0f, 100.0f } },
};

BSPNode* GetMapRoot() {
    return &nodes[0];
}

int GetMapSize() {
    return 63;
}

void GetFlatMap(Wall* wall_array) {
    for(int i = 0; i < 63; i++) {
        wall_array[i] = flat_map[i];
    }
}
