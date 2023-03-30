#include <pch.h>
#include "../features.hpp"

static bool trace_to_exit(vec3_t& end, trace_t& tr, float x, float y, float z, float x2, float y2, float z2, trace_t* trace) {
	typedef bool(__fastcall* fn)(vec3_t&, trace_t&, float, float, float, float, float, float, trace_t*);
	static auto trace_to_exit = reinterpret_cast<fn>(util::pattern_scan(xorstr("client.dll"), xorstr("55 8B EC 83 EC 4C F3 0F 10 75")));
	if (!trace_to_exit) return false;

	_asm {
		push 0
		push 0
		push 0
		push trace
		push z2
		push y2
		push x2
		push z
		push y
		push x
		mov edx, tr
		mov ecx, end
		call trace_to_exit
		add esp, 40
	}
}

static float handle_bullet_penetration(surface_data* enter_surface_data, trace_t& enter_trace, vec3_t& direction, vec3_t& result, float penetration, float damage) {
	trace_t exit_trace;
	vec3_t dummy;

	if (!trace_to_exit(dummy, enter_trace, enter_trace.end.x, enter_trace.end.y, enter_trace.end.z, direction.x, direction.y, direction.z, &exit_trace))
		return -1.0f;

	auto exit_surface_data = interfaces::surface_props_physics->get_surface_data(exit_trace.surface.surfaceProps);
	float damage_modifier = 0.16f;
	float penetration_modifier = (enter_surface_data->penetrationmodifier + exit_surface_data->penetrationmodifier) / 2.0f;
	if (enter_surface_data->material == 71 || enter_surface_data->material == 89) {
		damage_modifier = 0.05f;
		penetration_modifier = 3.0f;
	}
	else if (enter_trace.contents >> 3 & 1 || enter_trace.surface.flags >> 7 & 1) {
		penetration_modifier = 1.0f;
	}

	if (enter_surface_data->material == exit_surface_data->material) {
		if (exit_surface_data->material == 85 || exit_surface_data->material == 87)
			penetration_modifier = 3.0f;
		else if (exit_surface_data->material == 76)
			penetration_modifier = 2.0f;
	}

	damage -= 11.25f / penetration / penetration_modifier + damage * damage_modifier + (exit_trace.end - enter_trace.end).length_sqr() / 24.0f / penetration_modifier;
	result = exit_trace.end;
	return damage;
}

bool features::legit::autowall::run(player_t* local_player, entity_t* entity, vec3_t& destination, weapon_info_t* weapon_data) {
	vec3_t start = local_player->get_eye_pos();
	vec3_t direction = (destination - start);
	direction /= direction.length();
	static trace_t trace;
	ray_t ray;
	trace_filter filter;

	int hits_left = 4;
	float damage = static_cast<float>(weapon_data->weapon_damage);
	while (damage >= 1.0f && hits_left) {
		filter.skip = csgo::local_player;
		ray.initialize(start, destination);
		interfaces::trace_ray->run(ray, 0x4600400B, &filter, &trace);

		if (trace.flFraction == 1.0f) break;

		if (trace.entity == entity && trace.hitgroup > hitgroup_generic && trace.hitgroup <= hitgroup_rightleg) {
			damage = get_damage_multiplier(trace.hitgroup) * damage * powf(weapon_data->weapon_range_mod, trace.flFraction * weapon_data->weapon_range / 500.0f);

			if (float armor_ratio{ weapon_data->weapon_armor_ratio / 2.0f }; is_armored(trace.hitgroup, trace.entity->has_helmet()))
				damage -= (trace.entity->armor() < damage * armor_ratio / 2.0f ? trace.entity->armor() * 4.0f : damage) * (1.0f - armor_ratio);

			return damage >= 1.f;
		}

		auto surface_data = interfaces::surface_props_physics->get_surface_data(trace.surface.surfaceProps);
		if (surface_data->penetrationmodifier < 0.1f) break;

		damage = handle_bullet_penetration(surface_data, trace, direction, start, weapon_data->weapon_penetration, damage);
		hits_left--;
	}
	return false;
}