#include <pch.h>
#include "../features.hpp"

void features::movement::fast_stop(c_usercmd* cmd) {
	// Sanity checks
	if (!interfaces::engine->is_in_game() || !csgo::local_player->is_alive()) return;

	// Movement checks
	if (!(csgo::local_player->flags() & fl_onground) || csgo::local_player->move_type() == movetype_ladder || csgo::local_player->move_type() == movetype_noclip) return;

	// Check if we are moving
	if (cmd->buttons & (in_jump | in_forward | in_back | in_moveleft | in_moveright)) return;

	// Check for eb or ps
	if (features::movement::edgebug::is_detected() || features::movement::pixelsurf::is_detected()) return;

	vec3_t direction, forward;
	math::vector_angles(csgo::local_player->velocity(), direction);
	direction.y = cmd->viewangles.y - direction.y;
	math::angle_vectors(direction, &forward);

	auto forward_direction = forward * -csgo::local_player->velocity().length_2d();
	cmd->forwardmove = forward_direction.x;
	cmd->sidemove = forward_direction.y;
}