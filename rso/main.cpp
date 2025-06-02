#include "heap.h"
#include "patch.h"
#include "version.h"
#include "gpatch.h"

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

namespace main {

void init() {
    patch::patch_loader_function();
    version::init();
    gpatch::init();
}

}  // namespace main
