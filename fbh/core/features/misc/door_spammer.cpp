#include <pch.h>
#include "../features.hpp"

void features::misc::door_spammer(c_usercmd* cmd) {
	// Sanity checks
	if (!interfaces::engine->is_in_game() || !csgo::local_player->is_alive()) return;

	// Keybind check
	if (!util::bind(var::misc::doorspammer::keybind, var::misc::doorspammer::kb_style)) return;

	// Spam use every other tick
	if (cmd->tick_count % 2 == 0) {
		cmd->buttons |= in_use;
	}
	else {
		cmd->buttons &= ~in_use;
	}
}