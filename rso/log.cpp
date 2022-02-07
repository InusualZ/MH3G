#include "log.h"

#include "revolution\os.h"

namespace log {

void mod_assert(const char* file, s32 line, bool exp) {
    if (!(exp)) {
        OSPanic(const_cast<char*>(file), line, "[MH3G] Assertion failed");
        while (true)
            ;
    }
}

}  // namespace log