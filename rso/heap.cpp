#include "heap.h"

#include "game\memory.h"

static void*(*GAME_MEM1_ALLOCATOR_FUNC)(size_t) = (void*(*)(size_t))0x80040420;
static void(*GAME_MEM1_DEALLOCATOR_FUNC)(void*) = (void(*)(void*))0x80040460;

namespace heap {

void* alloc_mem1(size_t size) {
    return GAME_MEM1_ALLOCATOR_FUNC(size);
}

void* alloc_mem2(size_t size) {
    return work_mem_alloc__FUl(size);
}

void free_mem1(void* addr) {
    GAME_MEM1_DEALLOCATOR_FUNC(addr);
}

void free_mem2(void* addr) {
    work_mem_free__FPv(addr);
}

}  // namespace heap
