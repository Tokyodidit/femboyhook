#include <pch.h>
#include "../features.hpp"

void features::movement::blockbot(c_usercmd* cmd) {
	// Sanity checks
	if (!interfaces::engine->is_in_game() || !csgo::local_player->is_alive()) return;

	// Movement checks
	if (csgo::local_player->move_type() == movetype_ladder || csgo::local_player->move_type() == movetype_noclip) return;

	// Keybind
	if (!util::bind(var::movement::blockbot::keybind, var::movement::blockbot::kb_style)) return;

	float bestdistance = 200.0f;
	int bestindex = -1;

	for (auto i = 1; i < interfaces::globals->max_clients; i++) {
		auto entity = (player_t*)interfaces::entity_list->get_client_entity(i);
		if (!entity || entity->dormant() || !entity->is_alive() || entity == csgo::local_player) continue;

		float distance = csgo::local_player->origin().distance_to(entity->origin());
		if (distance < bestdistance)
		{
			bestdistance = distance;
			bestindex = i;
		}
	}

	auto entity = (player_t*)interfaces::entity_list->get_client_entity(bestindex);
	if (!entity) return;

	float bestspeed = entity->velocity().length();
	vec3_t local_angle;
	interfaces::engine->get_view_angles(local_angle);
	vec3_t vecforward = entity->origin() - csgo::local_player->origin();

	if (entity->get_hitbox_position(6).z < csgo::local_player->origin().z && csgo::local_player->origin().distance_to(entity->origin()) < 100.0f)
	{
		// Head blockbot
		cmd->forwardmove = ((sin(DEG2RAD(local_angle.y)) * vecforward.y) + (cos(DEG2RAD(local_angle.y)) * vecforward.x)) * bestspeed;
		cmd->sidemove = ((cos(DEG2RAD(local_angle.y)) * -vecforward.y) + (sin(DEG2RAD(local_angle.y)) * vecforward.x)) * bestspeed;
	}
	else
	{
		// Ground blockbot
		auto yaw_delta = (atan2(vecforward.y, vecforward.x) * 180.0f / M_PI) - local_angle.y;
		if (yaw_delta > 180) { yaw_delta -= 360; }
		else if (yaw_delta < -180) { yaw_delta += 360; }
		if (yaw_delta > 0.25) { cmd->sidemove = -bestspeed; }
		else if (yaw_delta < -0.25) { cmd->sidemove = bestspeed; }
	}
}