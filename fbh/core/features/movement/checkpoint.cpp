#include <pch.h>
#include "../features.hpp"

vec3_t pos, ang;
void features::movement::checkpoint() {
	// Sanity checks
	if (!interfaces::engine->is_in_game() || !csgo::local_player->is_alive()) return;

	// Save position
	if (GetAsyncKeyState(var::movement::checkpoint::keybind)) {
		pos = csgo::local_player->origin();
		ang = csgo::local_player->eye_angles();
	}

	// Load position
	if (GetAsyncKeyState(var::movement::checkpoint::keybind_teleport) && !pos.is_zero()) {
		interfaces::engine->execute_cmd(std::format("setpos {} {} {};setang {} {} {}", pos.x, pos.y, pos.z, ang.x, ang.y, ang.z).c_str());
	}
}