#include "gpatch.h"
#include "patch.h"
#include "revolution\os.h"
#include "game\gui.h"
#include "game\work.h"

void (*zz_02ece28_draw)(_PLW*, short) = (void(*)(_PLW*,short))0x802ece28;
static void (*zz_02ece28_draw_trampoline)(_PLW*, short);

namespace gpatch {

    /// @brief This patch allows you to eat after you have joined a quest
    void apply_eat_after_quest_join_patch() {
        patch::write_nop((void*)0x80324FBC);
        patch::write_nop((void*)0x8020AB8C);
        OSReport("[MH3G] Applied Patch: Eat After Quest Join\n");
    }

    /// @brief This patch display the player position on screen
    void apply_display_player_pos_patch() {
        zz_02ece28_draw_trampoline = patch::hook_function(zz_02ece28_draw, [](_PLW* plw, short unk1) {
            auto moveWork = *((MoveWork**)0x80658684);
            if (moveWork != nullptr) {
                // _PLW array is alway at pos 2
                auto amountPLW = moveWork->move_work_max[2];
                auto plwArray = (_PLW*)moveWork->move_work[2];
                auto yPos = 116;
                for (auto idx = 0; idx < amountPLW; ++idx) {
                    auto plw = plwArray[idx];
                    font_set_size__Fss(18, 18);
                    font_print_ex__FsssPSce(64, yPos + (idx * 20), 0, "POS[%d] %.2f %.2f %.2f", idx, plw.XPos, plw.YPos, plw.ZPos);
                    font_print_ex__FsssPSce(64, yPos + (idx + 1 * 20), 0, "ROT[%d] %d %d %d", idx, plw.rotX, plw.rotY, plw.rotZ);
                    font_print_ex__FsssPSce(64, yPos + (idx + 2 * 20), 0, "Area[%d] %d %d", idx, plw.area, plw.area2);
                }
            }
            zz_02ece28_draw_trampoline(plw, unk1);
        });
        OSReport("[MH3G] Applied Patch: Display Player Pos\n");
    }

    /// @brief Apply all the assembly patch
    void init() {
        // apply_eat_after_quest_join_patch();
        apply_display_player_pos_patch();
    }
}
