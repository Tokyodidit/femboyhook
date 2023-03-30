#include <pch.h>
#include "../features.hpp"

void features::misc::rank_reveal(c_usercmd* cmd) {
	// Sanity checks
	if (!interfaces::engine->is_in_game() || !csgo::local_player) return;

	// Reveal rank if we are in score board
	if (cmd->buttons & in_score)
		interfaces::client->dispatch_user_message(cs_um_serverrankrevealall, 0, 0, nullptr);
}