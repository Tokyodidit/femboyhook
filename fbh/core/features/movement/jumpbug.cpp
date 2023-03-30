#include <pch.h>
#include "../features.hpp"

void features::movement::jumpbug(c_usercmd* cmd, int pre_flags) {
	// Sanity checks
	if (!interfaces::engine->is_in_game() || !csgo::local_player->is_alive()) return;

	// Movement checks
	if (csgo::local_player->move_type() == movetype_ladder || csgo::local_player->move_type() == movetype_noclip) return;

	// Keybind check
	if (!util::bind(var::movement::jumpbug::keybind, var::movement::jumpbug::kb_style)) return;

	if (!(pre_flags & fl_onground) && csgo::local_player->flags() & fl_onground) {
		cmd->buttons |= in_duck;
		cmd->buttons &= ~in_jump;
	}
}