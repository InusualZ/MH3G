#include "heap.h"
#include "patch.h"
#include "version.h"

#include "revolution\os.h"

typedef void(*MODULE_FUNCTION)(void);

struct RSOModule {
    RSOModule* next_module_link;
    RSOModule* prev_module_link;
    u32 section_count;
    u32 section_info_count;
    char* module_name_offset;
    u32 module_name_size;
    u32 module_version;
    u32 bss_size;
    u8 prolog_section_index;
    u8 epilog_section_index;
    u8 unresolved_section_index;
    u8 bss_section_index;
    MODULE_FUNCTION prolog_function;
    MODULE_FUNCTION epilog_function;
    MODULE_FUNCTION unresolved_function;
};

static void** MODULE_START_PTR = (void**)0x807947b8;
static void** MODULE_END_PTR = (void**)0x807947bc;

void (*net_connect_draw_cb)(void) = (void(*)(void))0x804295cc;
static void (*draw_trampoline)(void);

namespace main {

void init() {
    OSReport("[MH3G] MH3G Mod v%d.%d.%d loaded\n",
                  version::MOD_VERSION.major,
                  version::MOD_VERSION.minor,
                  version::MOD_VERSION.patch);

    patch::patch_loader_function();

    draw_trampoline = patch::hook_function(net_connect_draw_cb, []() {
        OSReport("[MH3G] Draw CallBack\n");
        draw_trampoline();
    });

    OSReport("[MH3G] ModuleStartPtr %p | ModuleEndPtr %p\n", *MODULE_START_PTR, *MODULE_END_PTR);
}

}  // namespace main
