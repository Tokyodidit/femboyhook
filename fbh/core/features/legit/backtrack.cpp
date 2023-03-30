#include <pch.h>
#include "../features.hpp"

void features::legit::backtrack::initialize() {
	records->clear();
	cvars.updaterate = interfaces::console->get_convar(xorstr("cl_updaterate"));
	cvars.maxupdaterate = interfaces::console->get_convar(xorstr("sv_maxupdaterate"));
	cvars.interp = interfaces::console->get_convar(xorstr("cl_interp"));
	cvars.interpratio = interfaces::console->get_convar(xorstr("cl_interp_ratio"));
	cvars.mininterpratio = interfaces::console->get_convar(xorstr("sv_client_min_interp_ratio"));
	cvars.maxinterpratio = interfaces::console->get_convar(xorstr("sv_client_max_interp_ratio"));
	cvars.maxunlag = interfaces::console->get_convar(xorstr("sv_maxunlag"));
}

void features::legit::backtrack::update() {
	// Sanity checks
	if (!interfaces::engine->is_in_game()) return;

	// Alive check
	if (!csgo::local_player->is_alive()) {
		if (!records->empty()) records->clear();
		return;
	}

	for (int i = 1; i <= interfaces::globals->max_clients; i++) {
		auto entity = reinterpret_cast<player_t*>(interfaces::entity_list->get_client_entity(i));
		if (!entity || entity == csgo::local_player || entity->dormant() || !entity->is_alive() || entity->team() == csgo::local_player->team()) {
			records[i].clear();
			continue;
		}

		if (!records[i].empty() && (records[i].front().simulation_time == entity->simulation_time())) continue;

		stored_records record{ };
		record.origin = entity->abs_origin();
		record.simulation_time = entity->simulation_time();
		entity->setup_bones(record.matrix, 256, 0x7FF00, interfaces::globals->cur_time); // Causing legs to jitter

		records[i].push_front(record);
		while (records[i].size() > 3 && records[i].size() > static_cast<size_t>(time_to_ticks(static_cast<float>(var::legit::backtrack::length) / 1000.f)))
			records[i].pop_back();

		auto invalid = std::find_if(std::cbegin(records[i]), std::cend(records[i]), [](const stored_records& rec) { return !valid(rec.simulation_time); });
		if (invalid != std::cend(records[i]))
			records[i].erase(invalid, std::cend(records[i]));
	}
}

void features::legit::backtrack::run(c_usercmd* cmd) {
	// Sanity checks
	if (!interfaces::engine->is_in_game() || !csgo::local_player->is_alive()) return;

	// Check if we are shooting
	if (!(cmd->buttons & in_attack)) return;

	// Keybind check
	if (!util::bind(var::legit::backtrack::keybind, var::legit::backtrack::kb_style)) return;

	float best_fov = 255.f;
	player_t* best_target{ };
	int best_target_index, best_record{ };
	vec3_t aim_punch = csgo::local_player->get_aim_punch();

	for (int i = 1; i <= interfaces::globals->max_clients; i++) {
		auto entity = reinterpret_cast<player_t*>(interfaces::entity_list->get_client_entity(i));
		if (!entity || entity == csgo::local_player || entity->dormant() || !entity->is_alive() || entity->team() == csgo::local_player->team()) continue;

		auto fov = math::calculate_fov(csgo::local_player->get_eye_pos(), entity->abs_origin(), cmd->viewangles + aim_punch);
		if (fov < best_fov) {
			best_fov = fov;
			best_target = entity;
			best_target_index = i;
		}
	}

	if (best_target) {
		if (records[best_target_index].size() <= 3) return;

		best_fov = 255.f;
		for (size_t i = 0; i < records[best_target_index].size(); i++) {
			auto& record = records[best_target_index][i];
			if (!valid(record.simulation_time)) continue;

			auto fov = math::calculate_fov(csgo::local_player->get_eye_pos(), record.origin, cmd->viewangles + aim_punch);
			if (fov < best_fov) {
				best_fov = fov;
				best_record = i;
			}
		}
	}
	if (best_record) {
		auto record = records[best_target_index][best_record];
		cmd->tick_count = time_to_ticks(record.simulation_time + lerp_time());
	}
}