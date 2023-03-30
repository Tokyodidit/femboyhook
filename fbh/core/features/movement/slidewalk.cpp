#include <pch.h>
#include "../features.hpp"

void features::movement::slide_walk(c_usercmd* cmd) {
	// Sanity checks
	if (!interfaces::engine->is_in_game() || !csgo::local_player->is_alive()) return;

	// Movement checks
	if (csgo::local_player->move_type() == movetype_ladder || csgo::local_player->move_type() == movetype_noclip) return;

	// Slide legs
	cmd->buttons ^= in_forward | in_back | in_moveleft | in_moveright;
}
