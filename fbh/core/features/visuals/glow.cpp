#include <pch.h>
#include "../features.hpp"

void features::visuals::glow::run() {
	// Sanity checks
	if (!interfaces::engine->is_in_game() || !csgo::local_player) return;

	for (auto i = 0; i < interfaces::glow_manager->size; i++) {
		if (interfaces::glow_manager->objects[i].unused() || !interfaces::glow_manager->objects[i].entity || interfaces::glow_manager->objects[i].entity->dormant()) continue;
		auto glow = &interfaces::glow_manager->objects[i];
		//auto clr = csgo::local_player->can_see_player_pos(glow->entity, glow->entity->get_bone_position(8)) ? var::visuals::glow::color : var::visuals::glow::color2; // Visble color glow

		// Keybind check
		if (!util::bind(var::visuals::glow::keybind, var::visuals::glow::kb_style)) continue;

		if (var::visuals::glow::player && (glow->entity->team() != csgo::local_player->team() && glow->entity->client_class()->class_id == ccsplayer)) {
			glow->set(var::visuals::glow::color);
		}
		else if (var::visuals::glow::bomb && (glow->entity->client_class()->class_id == cplantedc4 || glow->entity->client_class()->class_id == cc4)) {
			glow->set(var::visuals::glow::bomb_color);
		}
		else if (var::visuals::glow::chicken && glow->entity->client_class()->class_id == cchicken) {
			glow->set(var::visuals::glow::chicken_color);
		}
		else if (var::visuals::glow::weapon && glow->entity->is_weapon()) {
			glow->set(var::visuals::glow::weapon_color);
		}
		glow->glow_style = var::visuals::glow::style;
	}
}