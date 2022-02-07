#include "heap.h"
#include "revolution\os.h"
#include <cinttypes>

EXPORTED void memset(void* dest, int value, u32 size);

inline u32 OSRoundUp32B(u32 x) { return (x + 31) & ~31; }
inline u32 OSRoundDown32B(u32 x) { return x & ~31; }

namespace heap {

struct ChunkInfo {
    struct ChunkInfo * prev;
    struct ChunkInfo * next;
    u32 size;
    u8 padding[20]; /* This is to make the data portion of the chunk 32-bit aligned */
} __attribute__((__packed__));

struct HeapInfo {
    u32 capacity;
    struct ChunkInfo * first_free;
    struct ChunkInfo * first_used;
} __attribute__((__packed__));

static HeapInfo s_local_heap_info;  // Use our own HeapInfo if Workshop Mod isn't loaded
static HeapInfo* s_heap_info;  // Pointer to either our HeapInfo or Workshop Mod's

ChunkInfo* extract_chunk(ChunkInfo* list, ChunkInfo* chunk) {
    if (chunk->next) {
        chunk->next->prev = chunk->prev;
    }

    if (!chunk->prev) {
        return chunk->next;
    } else {
        chunk->prev->next = chunk->next;
        return list;
    }
}

ChunkInfo* add_chunk_to_front(ChunkInfo* list, ChunkInfo* chunk) {
    chunk->next = list;
    chunk->prev = nullptr;

    if (list) {
        list->prev = chunk;
    }

    return chunk;
}

ChunkInfo* find_chunk_in_list(ChunkInfo* list, ChunkInfo* chunk) {
    for (; list; list = list->next) {
        if (list == chunk) {
            return list;
        }
    }
    return nullptr;
}

static void make_heap() {
    u32 start = OSRoundUp32B(*reinterpret_cast<u32*>(0x8000452C));
    void* end_ptr = (void*)(0x8000452C + 0x8000); // TODO: Remove!
    u32 end = OSRoundDown32B(reinterpret_cast<u32>(end_ptr));
    u32 size = end - start;

    memset(reinterpret_cast<void*>(start), 0, size);

    s_heap_info->capacity = size;
    s_heap_info->first_free = reinterpret_cast<ChunkInfo*>(start);
    s_heap_info->first_free->next = nullptr;
    s_heap_info->first_free->prev = nullptr;
    s_heap_info->first_free->size = size;
    s_heap_info->first_used = nullptr;
}

void* alloc(u32 size) {
    // Enlarge size to the smallest possible chunk size
    u32 new_size = size + OSRoundUp32B(sizeof(ChunkInfo));
    new_size = OSRoundUp32B(new_size);

    ChunkInfo* temp_chunk = nullptr;

    // Find a memory area large enough
    for (temp_chunk = s_heap_info->first_free; temp_chunk; temp_chunk = temp_chunk->next) {
        if (new_size <= temp_chunk->size) {
            break;
        }
    }

    // Make sure the found region is valid
    if (!temp_chunk) {
        return nullptr;
    }

    s32 leftover_size = temp_chunk->size - new_size;

    s32 min_size = OSRoundUp32B(sizeof(ChunkInfo)) + 32;

    // Check if the current chunk can be split into two pieces
    if (leftover_size < min_size) {
        // Too small to split, so just extract it
        s_heap_info->first_free = extract_chunk(s_heap_info->first_free, temp_chunk);
    } else {
        // Large enough to split
        temp_chunk->size = static_cast<s32>(new_size);

        // Create a new chunk
        ChunkInfo* new_chunk =
            reinterpret_cast<ChunkInfo*>(reinterpret_cast<u32>(temp_chunk) + new_size);

        new_chunk->size = leftover_size;

        new_chunk->prev = temp_chunk->prev;
        new_chunk->next = temp_chunk->next;

        if (new_chunk->next) {
            new_chunk->next->prev = new_chunk;
        }

        if (new_chunk->prev) {
            new_chunk->prev->next = new_chunk;
        } else {
            s_heap_info->first_free = new_chunk;
        }
    }

    // Add the chunk to the allocated list
    s_heap_info->first_used = add_chunk_to_front(s_heap_info->first_used, temp_chunk);

    // Add the header size to the chunk
    void* allocated_memory = reinterpret_cast<void*>(reinterpret_cast<u32>(temp_chunk) +
                                                     OSRoundUp32B(sizeof(ChunkInfo)));

    memset(allocated_memory, 0, size);
    return allocated_memory;
}

bool free(void* ptr) {
    u32 ptr_raw = reinterpret_cast<u32>(ptr);

    u32 header_size = OSRoundUp32B(sizeof(ChunkInfo));

    // Remove the header size from ptr, as the value stored in the list does not include it
    ChunkInfo* temp_chunk = reinterpret_cast<ChunkInfo*>(ptr_raw - header_size);

    // Make sure ptr is actually allocated
    if (!find_chunk_in_list(s_heap_info->first_used, temp_chunk)) {
        return false;
    }

    // Extract the chunk from the allocated list
    s_heap_info->first_used = extract_chunk(s_heap_info->first_used, temp_chunk);

    // Add in sorted order to the free list
    //s_heap_info->first_free = DLInsert(s_heap_info->first_free, temp_chunk);
    return true;
}

u32 get_free_space() {
    u32 space = 0;
    for (ChunkInfo* chunk = s_heap_info->first_free; chunk; chunk = chunk->next) {
        space += chunk->size - 32;  // Don't count the ChunkInfo
    }
    return space;
}

u32 get_total_space() { return s_heap_info->capacity; }

void check_integrity() {
    bool valid = true;

    ChunkInfo* current_chunk = nullptr;
    ChunkInfo* prev_chunk = nullptr;
    for (current_chunk = s_heap_info->first_used; current_chunk;
         current_chunk = current_chunk->next) {
        // Check pointer sanity
        auto check_if_pointer_is_valid = [](void* ptr) {
            u32 ptr_raw = reinterpret_cast<u32>(ptr);
            return (ptr_raw >= 0x80000000) && (ptr_raw < 0x81800000);
        };

        if (!check_if_pointer_is_valid(current_chunk)) {
            valid = false;
            break;
        }

        // Sanity check size
        if (current_chunk->size >= 0x1800000) {
            valid = false;
            break;
        }

        // Check linked list integrity
        if (prev_chunk != current_chunk->prev) {
            valid = false;
            break;
        }

        prev_chunk = current_chunk;
    }

    if (!valid) {
        // Print the error message to the console
        OSReport("Heap corrupt at 0x%08" PRIx32 "\n", reinterpret_cast<u32>(current_chunk));
    }
}

void init() {
        s_heap_info = &s_local_heap_info;
        make_heap();
}

}  // namespace heap
