#pragma once

#include "types.h"

namespace heap {

/* 
 * Allocate from the game memory heap in the MEM1 section
 * You should only really use this not very often and not
 * too large. Since it may cause problem with the other
 * modules that the game load
 */
void* alloc_mem1(size_t size);

/*
 * Allocate from the game's work memory heap in the 
 * MEM2 section. This can be used a lot more.
 */
void* alloc_mem2(size_t size);

void free_mem1(void* addr);

void free_mem2(void* addr);

}  // namespace heap