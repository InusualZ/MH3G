#include "types.h"
#include "heap.h"

void* operator new(u32 size) { return heap::alloc_mem1(size); }

void* operator new[](u32 size) { return heap::alloc_mem1(size); }

void operator delete(void* ptr) { heap::free_mem1(ptr); }

void operator delete[](void* ptr) { heap::free_mem1(ptr); }

void operator delete(void* ptr, u32 size) { heap::free_mem1(ptr); }

void operator delete[](void* ptr, u32 size) { heap::free_mem1(ptr); }