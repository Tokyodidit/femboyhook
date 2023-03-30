#include <pch.h>
#include "../features.hpp"

void features::movement::minijump(c_usercmd* cmd, int pre_flags) {
	// Sanity checks
	if (!interfaces::engine->is_in_game() || !csgo::local_player->is_alive()) return;

	// Movement checks
	if (csgo::local_player->move_type() == movetype_ladder || csgo::local_player->move_type() == movetype_noclip) return;

	// Keybind check
	if (!util::bind(var::movement::minijump::keybind, var::movement::minijump::kb_style)) return;

	// Crouch before jump
	if (pre_flags & fl_onground && !(csgo::local_player->flags() & fl_onground)) {
		cmd->buttons |= in_duck;
	}
}