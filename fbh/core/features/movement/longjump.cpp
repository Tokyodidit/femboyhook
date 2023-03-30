#include <pch.h>
#include "../features.hpp"

void features::movement::longjump(c_usercmd* cmd) {
	// Sanity checks
	if (!interfaces::engine->is_in_game() || !csgo::local_player->is_alive()) return;


	// Movement checks
	if (csgo::local_player->move_type() == movetype_ladder || csgo::local_player->move_type() == movetype_noclip) return;

	// Keybind check
	if (!util::bind(var::movement::longjump::keybind, var::movement::longjump::kb_style)) return; 

	// Get last tick
	static int last_tick = 0;
	if (csgo::local_player->flags() & fl_onground) {
		last_tick = cmd->tick_count;
	}
	else if (cmd->tick_count - last_tick <= 2) {
		// Do lj
		cmd->buttons |= in_duck;
	}
}