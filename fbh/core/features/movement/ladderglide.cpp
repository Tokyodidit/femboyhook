#include <pch.h>
#include "../features.hpp"

void features::movement::ladderglide(c_usercmd* cmd) {
	// Sanity checks
	if (!interfaces::engine->is_in_game() || !csgo::local_player->is_alive()) return;

	// ladder and movement checks
	if (csgo::local_player->move_type() != movetype_ladder || csgo::local_player->move_type() == movetype_noclip) return;

	// Keybind check
	if (!util::bind(var::movement::ladderglide::keybind, var::movement::ladderglide::kb_style)) return;

	cmd->buttons |= in_jump;
}