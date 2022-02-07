#pragma once

#include <types.h>

typedef void* MEMHeapHandle;
typedef struct MEMAllocator MEMAllocator;

EXPORTED void* MEMDestroyExpHeap(MEMHeapHandle heap);

EXPORTED void MEMInitAllocatorForExpHeap(MEMAllocator* allocator, MEMHeapHandle heap, s32 alignment);

EXPORTED MEMHeapHandle MEMCreateExpHeapEx(void* addr, u32 size, u16 opt);

EXPORTED void MEMFreeToAllocator(MEMAllocator* allocator, void* addr);

EXPORTED void* MEMAllocFromAllocator(MEMAllocator* allocator, u32 size);