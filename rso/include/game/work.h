#pragma once

#include "types.h"

/// @brief 
/// size: 0xB20
struct _PLW {
    char padding1[0x16];  /* 0x00 */
    unsigned char area;   /* 0x16 */
    unsigned char area2;  /* 0x17 */
    char padding2[0x24];  /* 0x18 */

    // They probably are part of a VEC3
    float XPos;           /* 0x3C */
    float YPos;           /* 0x40 */
    float ZPos;           /* 0x44 */

    void* unk1;           /* 0x48 */
    void* unk2;           /* 0x4c */
    void* unk3;           /* 0x50 */

    s16 unk19;            /* 0x54 */
    s16 rotX;             /* 0x56 */
    s16 rotY;             /* 0x58 */
    s16 rotZ;             /* 0x5A */
    void* unk20;           /* 0x5C */
    float unk4;           /* 0x60 */
    float unk5;           /* 0x64 */
    float unk6;           /* 0x68 */
    float unk7;           /* 0x6c */
    float unk8;           /* 0x70 */
    u8 unk9;              /* 0x74 */
    u8 unk10;             /* 0x75 */
    u8 unk11;             /* 0x76 */
    u8 unk12;             /* 0x77 */
    float unk13;          /* 0x78 */
    float unk14;          /* 0x7c */
    float unk15;          /* 0x80 */
    float unk16;          /* 0x84 */
    float unk17;          /* 0x88 */
    float unk18;          /* 0x8c */

    char padding3[0xA90]; /* 0x90 */
};

static_assert(sizeof(_PLW) == 0xB20);


/// size: 0x2C
struct MoveWork {
    short move_work_max[7];
    char padding[2];
    void* move_work[7];
};

static_assert(sizeof(MoveWork) == 0x2C);
