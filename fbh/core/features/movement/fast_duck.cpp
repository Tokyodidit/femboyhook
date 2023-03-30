#include <pch.h>
#include "../features.hpp"

void features::movement::fast_duck(c_usercmd* cmd) {
	// Sanity checks
	if (!interfaces::engine->is_in_game() || !csgo::local_player->is_alive()) return;

	// Remove duck cooldown
	cmd->buttons |= in_bullrush;
}