#include <pch.h>
#include "../features.hpp"

void features::legit::triggerbot::run(c_usercmd* cmd) {
	// Sanity checks
	if (!interfaces::engine->is_in_game() || !csgo::local_player->is_alive()) return;

	auto weapon = csgo::local_player->active_weapon();
	if (!weapon || weapon->clip1_count() <= 0) return;

	auto weapon_data = weapon->get_weapon_data();
	if (!weapon_data) return;

	if (weapon->next_primary_attack() > csgo::local_player->get_tick_base() * interfaces::globals->interval_per_tick) return;

	// Menu check
	if (menu::opened) return;

	// Keybind check
	if (!util::bind(var::legit::triggerbot::keybind, var::legit::triggerbot::kb_style)) return;

	vec3_t src, dst, forward;
	trace_t trace;
	ray_t ray;
	trace_filter filter;

	math::angle_vectors(cmd->viewangles + csgo::local_player->get_aim_punch(), &forward);
	forward *= weapon->get_weapon_data()->weapon_range;
	filter.skip = csgo::local_player;
	src = csgo::local_player->get_eye_pos();
	dst = src + forward;

	ray.initialize(src, dst);
	interfaces::trace_ray->run(ray, 0x46004003, &filter, &trace);

	if (!trace.entity || !trace.entity->is_alive() || trace.entity->team() == csgo::local_player->team() || trace.entity->has_gun_game_immunity() || trace.entity->dormant() || !trace.entity->is_player())
		return;

	if (trace.hitgroup == hitgroup_head || trace.hitgroup == hitgroup_chest || trace.hitgroup == hitgroup_stomach) {
		cmd->buttons |= in_attack;
	}
}