#include <pch.h>
#include "esp.hpp"
#include "../features.hpp"

void features::visuals::esp::run() {
	// Sanity checks
	if (!interfaces::engine->is_in_game() || !csgo::local_player) return;

	// Esp loop
	for (int i = 0; i < interfaces::entity_list->get_highest_index(); i++) {
		auto entity = interfaces::entity_list->get_client_entity(i);
		if (!entity) continue;

		if (var::visuals::esp::enabled && i <= interfaces::globals->max_clients) {
			auto player = reinterpret_cast<player_t*>(entity);
			if (!player || !player->is_alive() || player == csgo::local_player || player->team() == csgo::local_player->team() || player->dormant()) continue;

			// ESP info
			esp_info info;
			if (!get_box(player, info.box)) continue;

			// Keybind check
			if (util::bind(var::visuals::esp::keybind, var::visuals::esp::kb_style)) {
				// Radar
				if (var::visuals::esp::radar) player->spotted() = true;

				// Player esp
				if (var::visuals::esp::name::enabled) name(player, info);
				if (var::visuals::esp::box::enabled) bounding_box(player, info);
				if (var::visuals::esp::ammo::enabled) ammo(player, info);
				if (var::visuals::esp::weapon::enabled) weapon(player, info);
				if (var::visuals::esp::health::enabled) health(player, info);
				if (var::visuals::esp::flags::enabled) flags(player, info);
				if (var::visuals::esp::snaplines::enabled) snaplines(player, info);
				if (var::visuals::esp::viewangles::enabled) viewangles(player);
				if (var::visuals::esp::skeleton::enabled) skeleton(player);
				if (var::visuals::esp::head::enabled) head(player);
				if (var::visuals::esp::dlight::enabled) dlight(player);
			}
		}

		// World
		auto fog = reinterpret_cast<fogcontroller_t*>(entity);
		if (fog && fog->client_class()->class_id == cfogcontroller) {
			fog->enable() = var::visuals::fog_changer::enabled;
			fog->start() = var::visuals::fog_changer::start;
			fog->end() = 3750.f;
			fog->color() = color(var::visuals::fog_changer::color).convert();
			fog->density() = var::visuals::fog_changer::color[3];
		}
	}
}

void features::visuals::esp::name(player_t* player, esp_info& info) {
	// Get player info
	player_info_t player_info;
	interfaces::engine->get_player_info(player->index(), &player_info);

	// Render name
	render::text(info.box.x + (info.box.w / 2), info.box.y - 12, render::fonts::esp_font, player_info.name, true, color(var::visuals::esp::name::color));
}

void features::visuals::esp::bounding_box(player_t* player, esp_info& info) {
	// Render box
	if (var::visuals::esp::box::corner) {
		render::draw_corner_box(info.box.x - 1, info.box.y - 1, info.box.w + 2, info.box.h + 2, color(1, 1, 1, var::visuals::esp::box::color[3] * 255));
		render::draw_corner_box(info.box.x, info.box.y, info.box.w, info.box.h, color(var::visuals::esp::box::color));
	}
	else {
		render::draw_outline(info.box.x - 1, info.box.y - 1, info.box.w + 2, info.box.h + 2, color(1, 1, 1, var::visuals::esp::box::color[3] * 255));
		render::draw_rect(info.box.x, info.box.y, info.box.w, info.box.h, color(var::visuals::esp::box::color));
	}

	// Render fill
	if (var::visuals::esp::box::fill)
		render::draw_rect_fade_vertical(info.box.x + 1, info.box.y + 1, info.box.w - 2, info.box.h - 2, color(var::visuals::esp::box::fill_color2), color(var::visuals::esp::box::fill_color));
}

void features::visuals::esp::weapon(player_t* player, esp_info& info) {
	auto weapon = player->active_weapon();
	if (!weapon) return;

	auto weapon_data = weapon->get_weapon_data();
	if (!weapon_data) return;

	// Render weapon name
	wchar_t* weapon_name = interfaces::localize->find(weapon_data->weapon_hud_name);
	render::text(info.box.x + (info.box.w / 2), info.box.y + info.box.h + info.offset + 1, render::fonts::esp_font, weapon_name, true, color(var::visuals::esp::weapon::color));
}

void features::visuals::esp::ammo(player_t* player, esp_info& info) {
	// Get active weapon
	auto weapon = player->active_weapon();
	if (!weapon) return;

	auto weapon_data = weapon->get_weapon_data();
	if (!weapon_data) return;

	// Get ammo
	int clip = weapon->clip1_count();
	if (clip < 0) return;

	info.offset += 5;

	// Render background
	render::draw_rect(info.box.x - 1, info.box.y + info.box.h + 2, info.box.w + 2, 4, color(1, 1, 1, 200));
	// Render gradient
	render::draw_rect_fade_horizontal(info.box.x, info.box.y + info.box.h + 3, (info.box.w * clip) / weapon_data->weapon_max_clip, 2, color(var::visuals::esp::ammo::color), color(var::visuals::esp::ammo::color2));
}

void features::visuals::esp::health(player_t* player, esp_info& info) {
	// Health clamp and color
	auto clamped_health = std::clamp(player->health(), 0, 100);
	int g = clamped_health * 2.55;
	int r = 255 - g;

	// Render background
	render::draw_filled_rect(info.box.x - 6, info.box.y - 1, 4, info.box.h + 2, color(1, 1, 1, 200));
	// Render health bar
	if (var::visuals::esp::health::override_color) {
		render::draw_rect_fade_vertical(info.box.x - 5, info.box.y + (info.box.h - info.box.h * clamped_health / 100.f), 2, info.box.h * clamped_health / 100.f, color(var::visuals::esp::health::color), color(var::visuals::esp::health::color2));
	}
	else {
		render::draw_filled_rect(info.box.x - 5, info.box.y + (info.box.h - info.box.h * clamped_health / 100.f), 2, info.box.h * clamped_health / 100.f, color(r, g, 0, 255));
	}
}

void features::visuals::esp::flags(player_t* player, esp_info& info) {
	std::vector<std::pair<std::string, color>> flags;

	// Get player info
	player_info_t player_info;
	interfaces::engine->get_player_info(player->index(), &player_info);

	int distance = csgo::local_player->origin().distance_to(player->origin()) * 0.0254f; // Convert distance to meters and integer

	// Flags
	if (var::visuals::esp::flags::health)
		flags.push_back({ std::to_string(player->health()), color(var::visuals::esp::flags::color) });

	if (var::visuals::esp::flags::money)
		flags.push_back({ std::string(xorstr("$")).append(std::to_string(player->money())), color(var::visuals::esp::flags::color) });

	if (var::visuals::esp::flags::distance)
		flags.push_back({ std::to_string(distance).append(xorstr("m")), color(var::visuals::esp::flags::color) });

	if (var::visuals::esp::flags::armor && player->armor() > 0)
		flags.push_back({ player->has_helmet() ? xorstr("hk") : xorstr("k"), color(var::visuals::esp::flags::color2) });

	if (var::visuals::esp::flags::flashed && player->is_flashed())
		flags.push_back({ xorstr("blind"), color(var::visuals::esp::flags::color2) });

	if (var::visuals::esp::flags::scoped && player->is_scoped())
		flags.push_back({ xorstr("zoom"), color(var::visuals::esp::flags::color2) });

	if (var::visuals::esp::flags::bomb && player->has_bomb())
		flags.push_back({ xorstr("c4"), color(var::visuals::esp::flags::color2) });

	if (var::visuals::esp::flags::defusing && player->is_defusing())
		flags.push_back({ xorstr("defuse"), color(var::visuals::esp::flags::color2) });

	if (var::visuals::esp::flags::kit && player->has_defuser())
		flags.push_back({ xorstr("kit"), color(var::visuals::esp::flags::color2) });

	if (var::visuals::esp::flags::bot && player_info.fakeplayer)
		flags.push_back({ xorstr("bot"), color(var::visuals::esp::flags::color2) });

	auto position = 0;
	for (auto text : flags) {
		render::text(info.box.x + info.box.w + 2, info.box.y + position - 2, render::fonts::esp_flags_font, text.first, false, text.second);
		position += 10;
	}
}

void features::visuals::esp::snaplines(player_t* player, esp_info& info) {
	// Snap lines
	int w, h;
	interfaces::engine->get_screen_size(w, h);

	// Draw lines
	render::draw_line(w / 2, h, info.box.x + info.box.w / 2, info.box.y + info.box.h, color(var::visuals::esp::snaplines::color));
}

void features::visuals::esp::viewangles(player_t* player) {
	vec3_t src;
	vec3_t pos = player->get_bone_position(8);
	math::angle_vectors(player->eye_angles(), &src);
	src *= var::visuals::esp::viewangles::length;
	vec3_t dst = pos + src;

	vec2_t start, end;
	if (!math::world_to_screen(pos, start) || !math::world_to_screen(dst, end)) return;

	// Draw viewangle line
	render::draw_line(start.x, start.y, end.x, end.y, color(var::visuals::esp::viewangles::color));
}

void features::visuals::esp::skeleton(player_t* player) {
	auto p_studio_hdr = interfaces::model_info->get_studio_model(player->model());
	if (!p_studio_hdr) return;

	for (int i = 0; i < p_studio_hdr->bones_count; i++) {
		studio_bone_t* bone = p_studio_hdr->bone(i);
		if (!bone) return;

		if (bone && (bone->flags & BONE_USED_BY_HITBOX) && (bone->parent != -1)) {
			vec3_t child = player->get_bone_position(i);
			vec3_t parent = player->get_bone_position(bone->parent);
			vec2_t start, end;

			// Render skeleton
			if (math::world_to_screen(parent, start) && math::world_to_screen(child, end))
				render::draw_line(start.x, start.y, end.x, end.y, color(var::visuals::esp::skeleton::color));
		}
	}
}

void features::visuals::esp::head(player_t* player) {
	// Render head
	vec2_t head_pos;
	if (var::visuals::esp::head::enabled) {
		if (math::world_to_screen(player->get_bone_position(8), head_pos)) {
			render::draw_circle(head_pos.x, head_pos.y, 4, 4, color(var::visuals::esp::head::color));
		}
	}
}

void features::visuals::esp::dlight(player_t* player) {
	// Dlight
	render::draw_dlight(player, color(var::visuals::esp::dlight::color), var::visuals::esp::dlight::radius);
}

// Calculate bounding box
bool features::visuals::esp::get_box(player_t* player, box_info& b) {
	vec3_t origin, min, max, flb, brt, blb, frt, frb, brb, blt, flt;
	float left, top, right, bottom;
	origin = player->abs_origin();
	min = player->collideable()->mins() + origin;
	max = player->collideable()->maxs() + origin;

	vec3_t points[] = {
		vec3_t(min.x, min.y, min.z),
		vec3_t(min.x, max.y, min.z),
		vec3_t(max.x, max.y, min.z),
		vec3_t(max.x, min.y, min.z),
		vec3_t(max.x, max.y, max.z),
		vec3_t(min.x, max.y, max.z),
		vec3_t(min.x, min.y, max.z),
		vec3_t(max.x, min.y, max.z)
	};

	if (!interfaces::debug_overlay->world_to_screen(points[3], flb) || !interfaces::debug_overlay->world_to_screen(points[5], brt)
		|| !interfaces::debug_overlay->world_to_screen(points[0], blb) || !interfaces::debug_overlay->world_to_screen(points[4], frt)
		|| !interfaces::debug_overlay->world_to_screen(points[2], frb) || !interfaces::debug_overlay->world_to_screen(points[1], brb)
		|| !interfaces::debug_overlay->world_to_screen(points[6], blt) || !interfaces::debug_overlay->world_to_screen(points[7], flt))
		return false;

	vec3_t arr[] = { flb, brt, blb, frt, frb, brb, blt, flt };
	left = flb.x;
	top = flb.y;
	right = flb.x;
	bottom = flb.y;

	for (int i = 1; i < 8; i++) {
		if (left > arr[i].x)
			left = arr[i].x;
		if (bottom < arr[i].y)
			bottom = arr[i].y;
		if (right < arr[i].x)
			right = arr[i].x;
		if (top > arr[i].y)
			top = arr[i].y;
	}

	b.x = static_cast<int>(left);
	b.y = static_cast<int>(top);
	b.w = static_cast<int>(right) - static_cast<int>(left);
	b.h = static_cast<int>(bottom) - static_cast<int>(top);
	return true;
}