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

//static void* (*game_load_rso)(const char*, void*, int) = (void*(*)(const char*, void*, int))0x80040598;
static void** MODULE_START_PTR = (void**)0x807947b8;
static void** MODULE_END_PTR = (void**)0x807947bc;
//static void** hbm_data_module = (void**)0x807947d4;
//static void* my_module;

namespace main {

void init() {
    OSReport("[MH3G] MH3G Mod v%d.%d.%d loaded\n",
                  version::MOD_VERSION.major,
                  version::MOD_VERSION.minor,
                  version::MOD_VERSION.patch);

    patch::patch_loader_function();

    // void* next_module_addr = *MODULE_START_PTR;
    
    // OSReport("[MH3G] ModuleStartPtr %p\n", next_module_addr);
 
    // auto my_module = (RSOModule*)game_load_rso("01/hbm_data.rso", next_module_addr, 0xff);

    // *hbm_data_module = my_module;

    // my_module->prolog_function();

    // *MODULE_END_PTR = (void*)((u32)(*MODULE_START_PTR) + 0x170000);

    OSReport("[MH3G] ModuleStartPtr %p | ModuleEndPtr %p\n", *MODULE_START_PTR, *MODULE_END_PTR);
}

}  // namespace main
