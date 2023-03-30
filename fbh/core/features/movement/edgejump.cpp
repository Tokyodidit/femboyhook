#include <pch.h>
#include "../features.hpp"

void features::movement::edgejump(c_usercmd* cmd, int pre_flags) {
	// Sanity checks
	if (!interfaces::engine->is_in_game() || !csgo::local_player->is_alive()) return;
	

	// Movement checks
	if (csgo::local_player->move_type() == movetype_ladder || csgo::local_player->move_type() == movetype_noclip) return;

	// Keybind check
	if (!util::bind(var::movement::edgejump::keybind, var::movement::edgejump::kb_style)) return;

	// Jump on edge
	if (pre_flags & fl_onground && !(csgo::local_player->flags() & fl_onground)) {
		cmd->buttons |= in_jump;

		// -w 
		interfaces::engine->execute_cmd(xorstr("-forward"));
	}
}