#include <pch.h>
#include "../features.hpp"

void features::legit::aimbot::run(c_usercmd* cmd) {
	// Sanity checks
	if (!interfaces::engine->is_in_game() || !csgo::local_player->is_alive()) { has_target = false; return; }

	// Check if we have weapon with ammo
	auto weapon = csgo::local_player->active_weapon();
	if (menu::opened || !weapon || weapon->clip1_count() <= 0) { has_target = false; return; }

	// Menu check
	if (menu::opened) { has_target = false; return; }

	// Keybind check
	if (!util::bind(var::legit::aimbot::keybind, var::legit::aimbot::kb_style)) { has_target = false; return; }

	// Variables
	int best_fov = var::legit::aimbot::fov;
	auto best_target = vec3_t(0, 0, 0);
	vec3_t aim_punch = csgo::local_player->get_aim_punch();
	aim_punch *= var::legit::aimbot::rcs / 100;

	// Hitboxes
	std::vector<int> bones;
	if (var::legit::aimbot::head) {
		bones.push_back(8);
	}
	if (var::legit::aimbot::chest) {
		bones.push_back(6);
	}
	if (var::legit::aimbot::stomach) {
		bones.push_back(3);
	}

	for (int i = 1; i <= interfaces::globals->max_clients; i++) {
		auto entity = reinterpret_cast<player_t*>(interfaces::entity_list->get_client_entity(i));

		// Entity checks
		if (!entity || entity == csgo::local_player || entity->team() == csgo::local_player->team() || entity->has_gun_game_immunity() || entity->dormant() || !entity->is_alive() || !entity->is_player()) 
			continue;

		// Loop hitboxes
		for (auto bone : bones) {
			auto bone_position = entity->get_bone_position(bone);

			// Auto wall
			if (!csgo::local_player->can_see_player_pos(entity, bone_position) && (!var::legit::aimbot::autowall || !features::legit::autowall::run(csgo::local_player, entity, bone_position, weapon->get_weapon_data())))
				continue;

			auto fov = math::calculate_fov(csgo::local_player->get_eye_pos(), bone_position, cmd->viewangles + aim_punch);
			if (fov < best_fov) {
				best_target = bone_position;
				best_fov = fov;
			}
		}
	}

	// Check for target
	if (best_target.is_zero()) return;

	// Calculate angle
	vec3_t angle = math::calculate_angle(csgo::local_player->get_eye_pos(), best_target, cmd->viewangles + aim_punch);
	if (!var::legit::aimbot::silent)
		angle /= var::legit::aimbot::smooth;

	// Set view angles
	cmd->viewangles += angle.clamped();
	if (!var::legit::aimbot::silent)
		interfaces::engine->set_view_angles(cmd->viewangles);
	has_target = true;
}

void features::legit::aimbot::draw_fov() {
	// Sanity checks
	if (!interfaces::engine->is_in_game() || !csgo::local_player) return;

	// Scope check
	if (csgo::local_player->is_scoped()) return;

	// Get screen size
	int w, h;
	interfaces::engine->get_screen_size(w, h);

	// Draw fov
	float radius = tan(DEG2RAD(var::legit::aimbot::fov)) / tan(DEG2RAD(var::visuals::view::fov) / 2) * (w / 2);
	gui::GetBackgroundDrawList()->AddCircle(ImVec2(w / 2, h / 2), radius, ImColor(var::legit::aimbot::fov_color));
}