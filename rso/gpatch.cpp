#include "gpatch.h"
#include "patch.h"
#include "revolution\os.h"

namespace gpatch {

    /// @brief This patch allows you to eat after you have joined a quest
    void apply_eat_after_quest_join_patch() {
        patch::write_nop((void*)0x80324FBC);
        patch::write_nop((void*)0x8020AB8C);
        OSReport("[MH3G] Applied Patch: Eat After Quest Join\n");
    }

    /// @brief Apply all the assembly patch
    void init() {
        apply_eat_after_quest_join_patch();
    }
}
