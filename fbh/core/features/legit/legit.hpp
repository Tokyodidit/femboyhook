#pragma once
#include "../../../dependencies/utilities/csgo.hpp"

struct stored_records {
	vec3_t origin;
	float simulation_time;
	matrix_t matrix[256];
};
struct convars {
	convar* updaterate;
	convar* maxupdaterate;
	convar* interp;
	convar* interpratio;
	convar* mininterpratio;
	convar* maxinterpratio;
	convar* maxunlag;
};
inline convars cvars;
inline std::deque<stored_records> records[65];

constexpr auto time_to_ticks(float time) {
	return static_cast<int>(0.5f + time / interfaces::globals->interval_per_tick);
}

constexpr auto lerp_time() {
	auto ratio = std::clamp(cvars.interpratio->get_float(), cvars.mininterpratio->get_float(), cvars.maxinterpratio->get_float());
	return max(cvars.interp->get_float(), (ratio / ((cvars.maxupdaterate) ? cvars.maxupdaterate->get_float() : cvars.updaterate->get_float())));
}

inline auto valid(float simtime) {
	i_net_channel_info* network = interfaces::engine->get_net_channel_info();
	if (!network) return false;

	auto delta = std::clamp(network->get_latency(0) + network->get_latency(1) + lerp_time(), 0.f, cvars.maxunlag->get_float()) - (interfaces::globals->cur_time - simtime);
	return std::fabsf(delta) <= 0.2f;
}

static float get_damage_multiplier(int hit_group) {
	switch (hit_group) {
		case hitgroup_head:
			return 4.0f;
		case hitgroup_stomach:
			return 1.25f;
		case hitgroup_leftleg:
		case hitgroup_rightleg:
			return 0.75f;
		default:
			return 1.0f;
	}
}

static bool is_armored(int hit_group, bool helmet) {
	switch (hit_group) {
		case hitgroup_head:
			return helmet;
		case hitgroup_chest:
		case hitgroup_stomach:
		case hitgroup_leftarm:
		case hitgroup_rightarm:
			return true;
		default:
			return false;
	}
}