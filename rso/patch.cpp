#include "patch.h"
#include "heap.h"
#include "log.h"
#include "revolution/stdio.h"

void (*DCFlushRange)(void* addr, u32 nBytes) = (void (*)(void*, u32))0x804cc610;
void (*ICInvalidateRange)(void* addr, u32 nBytes) = (void (*)(void*, u32))0x804cc730;
void* LOADER_FUNCTION_PTR = (void*)0x804da7e4;

u32 LOADER_FUNCTION[] = {
    // (u32)0x3c80aaab, // lis r4,-0x5555
    // (u32)0x80030050, // lwz r0,0x50(r3)
    // (u32)0x3884aaab, // subi r4,r4,0x5555
    // (u32)0x38a00000, // li  r5,0x0
    // (u32)0x7c040016, // mulhwu  r0,r4,r0
    // (u32)0x5400e8ff, // rlwinm. r0,r0,0x1d,0x3,0x1f
    // (u32)0x7c0903a6, // mtspr CTR,r0
    // (u32)0x4081002c, // ble LAB_804da82c
    // (u32)0x8083004c, // lwz r4,0x54(r3)
    // (u32)0x8003002c, // lwz r0,0x2c(r3)
    // (u32)0x7c842a14, // add r4,r4,r5
    // (u32)0x80840004, // lwz r4,0x4(r4)
    // (u32)0x7c040040, // cmplw r4,r0
    // (u32)0x4082000c, // bne LAB_804da824
    // (u32)0x38600000, // li  r3,0x0
    // (u32)0x4e800020, // blr
    // (u32)0x38a5000c, // addi r5,r5,0xc
    // (u32)0x4200ffdc, // bdnz LAB_804da804
    (u32)0x38600001, // li  r3,0x1
    (u32)0x4e800020  // blr
};

namespace patch {

void patch_loader_function() {
    const auto function_size = sizeof(LOADER_FUNCTION);
    memcpy(LOADER_FUNCTION_PTR, reinterpret_cast<void*>(LOADER_FUNCTION), function_size);
    clear_dc_ic_cache(LOADER_FUNCTION_PTR, function_size);
}

void clear_dc_ic_cache(void* ptr, u32 size) {
    DCFlushRange(ptr, size);
    ICInvalidateRange(ptr, size);
}

u32 write_branch(void* ptr, void* destination) {
    u32 branch = 0x48000000;  // b
    return write_branch_main(ptr, destination, branch);
}

u32 write_branch_bl(void* ptr, void* destination) {
    u32 branch = 0x48000001;  // bl
    return write_branch_main(ptr, destination, branch);
}

u32 write_blr(void* ptr) { return write_word(ptr, 0x4e800020); }

u32 write_branch_main(void* ptr, void* destination, u32 branch) {
    u32 delta = reinterpret_cast<u32>(destination) - reinterpret_cast<u32>(ptr);

    branch |= (delta & 0x03FFFFFC);

    u32* p = reinterpret_cast<u32*>(ptr);
    u32 orig_word = *p;
    *p = branch;

    clear_dc_ic_cache(ptr, sizeof(u32));

    return orig_word;
}

u32 write_word(void* ptr, u32 data) {
    u32* p = reinterpret_cast<u32*>(ptr);
    u32 orig_word = *p;
    *p = data;
    clear_dc_ic_cache(ptr, sizeof(u32));

    return orig_word;
}

u32 write_nop(void* ptr) { return write_word(ptr, 0x60000000); }

void* hook_function_internal(void* function, void* destination) {
    u32* instructions = static_cast<u32*>(function);

    // If function has been hooked already, chain the hooks

    constexpr u32 B_OPCODE_MASK = 0xFC000000;
    constexpr u32 B_OPCODE = 0x48000000;
    constexpr u32 B_DEST_MASK = 0x03FFFFFC;

    if ((instructions[0] & B_OPCODE_MASK) == B_OPCODE) {
        // Compute destination currently branched to
        u32 old_dest_offset = instructions[0] & B_DEST_MASK;
        // Sign extend to make it actually a s32
        if (old_dest_offset & (0x02000000)) {
            old_dest_offset |= 0xFC000000;
        }
        u32 old_dest = reinterpret_cast<u32>(function) + old_dest_offset;

        // Hook to our new function instead
        write_branch(&instructions[0], destination);

        // Return the old hooked function as the trampoline
        return reinterpret_cast<void*>(old_dest);
    }

    u32* trampoline = reinterpret_cast<u32*>(0x80000000);
    MOD_ASSERT(trampoline != nullptr);

    // Original instruction
    trampoline[0] = instructions[0];
    clear_dc_ic_cache(&trampoline[0], sizeof(u32));

    // Branch to original function past hook
    write_branch(&trampoline[1], &instructions[1]);

    // Write actual hook
    write_branch(&instructions[0], destination);

    return trampoline;
}

}  // namespace patch