#include <pch.h>
#include "../features.hpp"

void features::movement::bunnyhop(c_usercmd* cmd) {
	// Sanity checks
	if (!interfaces::engine->is_in_game() || !csgo::local_player->is_alive()) return;

	// Jump and movement check
	if (!(cmd->buttons & in_jump) || csgo::local_player->move_type() == movetype_ladder || csgo::local_player->move_type() == movetype_noclip) return;

	// Jumpbug check
	if (GetAsyncKeyState(var::movement::jumpbug::keybind) && var::movement::jumpbug::enabled) return;

	static bool fail = false;
	if (!(csgo::local_player->flags() & fl_onground)) {
		if (rand() % 100 > var::movement::bunnyhop::hitchance) {
			fail = true;
		}
		else {
			fail = false;
			cmd->buttons &= ~in_jump;
		}
	}
	else {
		if (fail) {
			cmd->buttons &= ~in_jump;
			fail = false;
		}
	}
}