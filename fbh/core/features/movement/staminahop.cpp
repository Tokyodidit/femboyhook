#include <pch.h>
#include "../features.hpp"

void features::movement::staminahop(c_usercmd* cmd) {
    // Sanity checks
    if (!interfaces::engine->is_in_game() || !csgo::local_player->is_alive()) return;

    // Movement checks
    if (csgo::local_player->move_type() == movetype_ladder || csgo::local_player->move_type() == movetype_noclip) return;

    // Keybind check
    if (!GetAsyncKeyState(var::movement::staminahop::keybind)) return;

    // Staminahop
    static int sh_tick = 0;
    if (!(csgo::local_player->flags() & fl_onground)) {
        sh_tick = cmd->tick_count + 2;
    }
    else if (sh_tick < cmd->tick_count) {
        cmd->buttons |= in_jump;
    }
}