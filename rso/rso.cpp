#include "revolution\os.h"
#include "types.h"

typedef void (*PFN_voidfunc)();
EXPORTED __attribute__((section(".ctors"))) PFN_voidfunc _ctors_start[];
EXPORTED __attribute__((section(".ctors"))) PFN_voidfunc _ctors_end[];
EXPORTED __attribute__((section(".dtors"))) PFN_voidfunc _dtors_start[];
EXPORTED __attribute__((section(".dtors"))) PFN_voidfunc _dtors_end[];

namespace main {

extern void init();

}

EXPORTED void _prolog() {
    // Run global constructors
    for (PFN_voidfunc* ctor = _ctors_start; ctor != _ctors_end && *ctor; ++ctor) {
        (*ctor)();
    }

    // Run mod init function
    main::init();
}

EXPORTED void _epilog() {
    // In the unlikely event we ever get here, run the global destructors
    for (PFN_voidfunc* dtor = _dtors_start; dtor != _dtors_end && *dtor; ++dtor) {
        (*dtor)();
    }
}

EXPORTED void _unresolved() {
    u32     i;
    u32*    p;

    OSReport("\nError: Unlinked function called in module `MH3G`.\n");
    OSReport("Address:      Back Chain    LR Save\n");
    for (i = 0, p = (u32*) OSGetStackPointer(); // get current sp
         p && (u32) p != 0xffffffff && i++ < 16;
         p = (u32*) *p)                         // get caller sp
    {
        OSReport("0x%08x:   0x%08x    0x%08x\n", p, p[0], p[1]);
    }
    OSReport("\n");
}
