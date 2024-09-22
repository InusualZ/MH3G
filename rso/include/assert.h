#pragma once

#include "types.h"

namespace assert {
    void mod_assert(const char* file, s32 line, bool exp);
}

#define MOD_ASSERT(exp) (assert::mod_assert(__FILE__, __LINE__, (exp)))