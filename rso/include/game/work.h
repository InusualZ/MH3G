#pragma once

#include "types.h"

/// @brief 
/// size: 0xB20
struct _PLW {
    char padding1[0x3C];

    // They probably are part of a VEC3
    float XPos;
    float YPos;
    float ZPos;

    char padding2[0xAD8];
};

static_assert(sizeof(_PLW) == 0xB20);


/// size: 0x2C
struct MoveWork {
    short move_work_max[7];
    char padding[2];
    void* move_work[7];
};

static_assert(sizeof(MoveWork) == 0x2C);
