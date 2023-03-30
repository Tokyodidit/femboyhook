#include <pch.h>
#include "../features.hpp"

void features::visuals::speclist() {
	// Sanity checks
	if (!interfaces::engine->is_in_game() || !csgo::local_player->is_alive()) return;

	gui::SetNextWindowSize({ 150,-1 });
	gui::Begin(xorstr("spectators"), NULL, ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize);

	// Get specs
	for (int i = 1; i <= interfaces::globals->max_clients; i++) {
		auto entity = reinterpret_cast<player_t*>(interfaces::entity_list->get_client_entity(i));
		if (!entity || entity->dormant() || entity->is_alive() || reinterpret_cast<player_t*>(interfaces::entity_list->get_client_entity_handle(entity->observer_target())) != csgo::local_player) continue;

		player_info_t info;
		interfaces::engine->get_player_info(entity->index(), &info);
		std::string player_name = info.name;

		if (!info.name || info.ishltv || player_name.empty()) continue;

		gui::Text(player_name.append(xorstr(" \n")).c_str());
	}
	gui::End();
}

void features::visuals::skybox() {
	// Sanity checks
	if (!interfaces::engine->is_in_game() || !csgo::local_player) return;

	// Set skybox
	switch (var::visuals::sky_changer) {
		case 1: util::load_skybox(xorstr("sky_csgo_night02")); break;
		case 2: util::load_skybox(xorstr("sky_lunacy")); break;
		case 3: util::load_skybox(xorstr("custom")); break;
	}
}

void features::visuals::local_dlight() {
	// Sanity checks
	if (!interfaces::engine->is_in_game() || !csgo::local_player->is_alive()) return;

	// Render local dlight
	render::draw_dlight(csgo::local_player, color(var::visuals::local_dlight::color), var::visuals::local_dlight::radius);
}

void features::visuals::trail() {
	// Sanity checks
	if (!interfaces::engine->is_in_game() || !csgo::local_player->is_alive()) return;

	// Render trail beam
	static vec3_t lastpos;
	render::draw_beam(color(var::visuals::bullet_tracers::color), 2, var::visuals::trail::life, FBEAM_ONLYNOISEONCE, csgo::local_player->origin(), lastpos);
	lastpos = csgo::local_player->origin();
}

void features::visuals::watermark() {
	// Get spotify song
	std::string song_title = xorstr("");
	static HWND spotify_hwnd = nullptr;
	static float last_hwnd_time = 0.f;
	if ((!spotify_hwnd || spotify_hwnd == INVALID_HANDLE_VALUE) && last_hwnd_time < interfaces::globals->realtime + 2.f) {
		for (HWND hwnd = GetTopWindow(0); hwnd; hwnd = GetWindow(hwnd, GW_HWNDNEXT)) {

			last_hwnd_time = interfaces::globals->realtime;

			if (!(IsWindowVisible)(hwnd))
				continue;

			int length = (GetWindowTextLengthW)(hwnd);
			if (length == 0)
				continue;

			WCHAR filename[300];
			DWORD pid;
			(GetWindowThreadProcessId)(hwnd, &pid);

			const auto spotify_handle = (OpenProcess)(PROCESS_QUERY_INFORMATION, FALSE, pid);
			(K32GetModuleFileNameExW)(spotify_handle, nullptr, filename, 300);

			std::wstring sane_filename{ filename };

			(CloseHandle)(spotify_handle);

			if (sane_filename.find((L"Spotify.exe")) != std::string::npos)
				spotify_hwnd = hwnd;
		}
	}
	else if (spotify_hwnd && spotify_hwnd != INVALID_HANDLE_VALUE) {
		WCHAR title[300];

		if (!(GetWindowTextW)(spotify_hwnd, title, 300)) {
			spotify_hwnd = nullptr;
		}
		else {
			std::wstring sane_title{ title };
			std::string Title = xorstr(" | ");
			std::string Song(sane_title.begin(), sane_title.end());
			Title += Song;
			if (sane_title.find((L"-")) != std::string::npos) {
				song_title = Title;
			}
			else if (sane_title.find((L"Advertisment")) != std::string::npos) {
				song_title = xorstr(" | advertisment");
			}
			else if (sane_title.find((L"Spotify")) != std::string::npos) {
				song_title = xorstr(" | paused");
			}
			else {
				song_title = xorstr(" | advertisment");
			}
		}
	}

	// Text
	std::string name = xorstr("femboyhook") + song_title;

	// Get text size
	const auto size = render::get_text_size(render::fonts::watermark_font, name);

	// Render box
	render::draw_filled_rect(3, 3, 6 + size.x, 4 + size.y, color(10, 10, 10, 255));
	// Render gradient line
	render::draw_rect_fade_horizontal(3, 3, 3 + size.x / 2, 1, color(10, 10, 10, 255), color(var::menu::accent));
	render::draw_rect_fade_horizontal(6 + size.x / 2, 3, 3 + size.x / 2, 1, color(var::menu::accent), color(10, 10, 10, 255));
	// Render text
	render::text(6, 6, render::fonts::watermark_font, name, false, color(225, 225, 225, 255));
}

void features::visuals::flash_opacity() {
	// Sanity checks
	if (!interfaces::engine->is_in_game() || !csgo::local_player) return;

	// Flash alpha
	csgo::local_player->flash_alpha() = (var::visuals::flash_opacity / 100.f) * 255.f;
}

void features::visuals::wireframe_smoke() {
	// Sanity checks
	if (!interfaces::engine->is_in_game() || !csgo::local_player->is_alive()) return;

	static auto smoke_count = *reinterpret_cast<uint32_t**>(util::pattern_scan(xorstr("client.dll"), xorstr("A3 ? ? ? ? 57 8B CB")) + 1);
	auto material = interfaces::material_system->find_material(xorstr("particle\\vistasmokev1\\vistasmokev1_smokegrenade"), TEXTURE_GROUP_OTHER);
	material->set_material_var_flag(material_var_wireframe, var::visuals::wireframe_smoke);
	if (var::visuals::wireframe_smoke) {
		*(int*)smoke_count = 0;
	}
}

void features::visuals::disable_postprocess() {
	// Sanity checks
	if (!interfaces::engine->is_in_game() || !csgo::local_player) return;

	static bool* disable_postprocessing = *reinterpret_cast<bool**>(util::pattern_scan(xorstr("client.dll"), xorstr("83 EC 4C 80 3D")) + 0x5);
	*disable_postprocessing = var::visuals::disable_postprocess;
}

void features::visuals::remove_scope() {
	// Sanity checks
	if (!interfaces::engine->is_in_game() || !csgo::local_player->is_alive()) return;

	// Scope check
	if (!csgo::local_player->is_scoped()) return;

	// Check for active weapon
	auto weapon = csgo::local_player->active_weapon();
	if (!weapon) return;

	// Check if we are using sniper
	auto weapon_data = weapon->get_weapon_data();
	if (!weapon_data || !weapon->is_sniper()) return;

	// Get screen size
	int w, h;
	interfaces::engine->get_screen_size(w, h);

	// Render scope lines
	render::draw_line(0, h / 2, w, h / 2, color(var::visuals::remove_scope::color));
	render::draw_line(w / 2, 0, w / 2, h, color(var::visuals::remove_scope::color));
}

void features::visuals::sniper_crosshair() {
	// Sanity checks
	if (!interfaces::engine->is_in_game() || !csgo::local_player->is_alive()) return;

	// Scope check
	if (csgo::local_player->is_scoped()) return;

	// Check for active weapon
	auto weapon = csgo::local_player->active_weapon();
	if (!weapon) return;

	// Check if we are using sniper
	auto weapon_data = weapon->get_weapon_data();
	if (!weapon_data || !weapon->is_sniper()) return;

	// Get screen size
	int w, h;
	interfaces::engine->get_screen_size(w, h);

	// Render crosshair
	render::draw_line(w / 2 - 2, h / 2, w / 2 + 2, h / 2, color(var::visuals::snipercrosshair::color));
	render::draw_line(w / 2, h / 2 - 2, w / 2, h / 2 + 2, color(var::visuals::snipercrosshair::color));
}

void features::visuals::recoil_crosshair() {
	// Sanity checks
	if (!interfaces::engine->is_in_game() || !csgo::local_player->is_alive()) return;

	// Scope check
	if (csgo::local_player->is_scoped()) return;

	// Get screen size
	int w, h;
	interfaces::engine->get_screen_size(w, h);
	int x = w / 2;
	int y = h / 2;

	// Recoil calc
	vec3_t aim_punch = csgo::local_player->aim_punch_angle();
	x -= (w / var::visuals::view::fov) * aim_punch.y;
	y += (h / var::visuals::view::fov) * aim_punch.x;

	// Render crosshair
	if (csgo::local_player->shots_fired() > 1) {
		render::draw_line(x - 2, y, x + 2, y, color(var::visuals::recoilcrosshair::color));
		render::draw_line(x, y - 2, x, y + 2, color(var::visuals::recoilcrosshair::color));
	}
}

void features::visuals::indicators() {
	// Sanity checks
	if (!interfaces::engine->is_in_game() || !csgo::local_player->is_alive()) return;
	
	// Get screen size
	int w, h;
	interfaces::engine->get_screen_size(w, h);

	// Speed variables
	std::string velocity = std::format("{:.0f}", csgo::local_player->velocity().length_2d());
	std::string stamina = std::format("{:.1f}", csgo::local_player->stamina().length_2d());
	static float pre_speed, pre_stamina, last_set;
	static bool on_ground;

	if (var::visuals::indicators::pre) {
		// Get pre
		if (!(csgo::local_player->flags() & fl_onground) && on_ground) {
			pre_speed = csgo::local_player->velocity().length_2d();
			pre_stamina = csgo::local_player->stamina().length_2d();
			last_set = interfaces::globals->cur_time + 3.0f;
		}
		on_ground = csgo::local_player->flags() & fl_onground;

		// Render pre
		if (last_set > interfaces::globals->cur_time) {
			velocity += std::format(" ({:.0f})", pre_speed);
			stamina += std::format(" ({:.1f})", pre_stamina);
		}
	}
	// fonts
	unsigned long font;
	switch (var::visuals::indicators::font) {
		case 0: font = render::fonts::indicators_font; break;
		case 1: font = render::fonts::indicators_font2; break;
		case 2: font = render::fonts::indicators_font3; break;
		case 3: font = render::fonts::indicators_font4; break;
		case 4: font = render::fonts::indicators_font5; break;

	}

	// Render indicators
	if (var::visuals::indicators::velocity)
		render::text(w / 2, h - 146, font, velocity, true, math::color_lerpa(color(var::visuals::indicators::color), color(var::visuals::indicators::color2), std::clamp(csgo::local_player->velocity().length_2d() / 325.f, 0.f, 1.f)));
	if (var::visuals::indicators::stamina)
		render::text(w / 2, h - 117, font, stamina, true, math::color_lerpa(color(var::visuals::indicators::color), color(var::visuals::indicators::color2), std::clamp(csgo::local_player->stamina().length_2d() / 35.f, 0.f, 1.f)));

	// Render speed loss bar
	if (var::visuals::indicators::loss && csgo::local_player->velocity_loss() < 1) {
		render::draw_filled_rect(w / 2 - 51, h - 84, 96, 4, color(1, 1, 1, 200));
		render::draw_rect_fade_horizontal(w / 2 - 50, h - 83, csgo::local_player->velocity_loss() * 100, 2, color(var::visuals::indicators::color), color(var::visuals::indicators::color2));
	}

	// TODO: rework this missery ~ weird
	auto indicator_col = color(var::visuals::indicators::color);
	if (var::visuals::indicators::keybinds) {

	 if (var::movement::fakebackwards::enabled && util::bind(var::movement::fakebackwards::keybind, var::movement::fakebackwards::kb_style)) {
		render::text(w / 2, h - 79, font, xorstr("fb"), true, indicator_col);
	}
	 else if (var::movement::edgebug::enabled && util::bind(var::movement::edgebug::keybind, var::movement::edgebug::kb_style)) {
			if (features::movement::edgebug::is_detected()) indicator_col = color(var::visuals::indicators::color2);
			render::text(w / 2, h - 79, font, xorstr("eb"), true, indicator_col);
		}
		else if (var::movement::blockbot::enabled && util::bind(var::movement::blockbot::keybind, var::movement::blockbot::kb_style)) {
			render::text(w / 2, h - 79, font, xorstr("bb"), true, indicator_col);
		}
		else if (var::movement::pixelsurf::enabled && util::bind(var::movement::pixelsurf::keybind, var::movement::pixelsurf::kb_style)) {
			if (features::movement::pixelsurf::is_detected()) indicator_col = color(var::visuals::indicators::color2);
			render::text(w / 2, h - 79, font, xorstr("ps"), true, indicator_col);
		}
		else if (var::movement::jumpbug::enabled && util::bind(var::movement::jumpbug::keybind, var::movement::jumpbug::kb_style)) {
			render::text(w / 2, h - 79, font, xorstr("jb"), true, indicator_col);
		}
		else if (var::movement::longjump::enabled && util::bind(var::movement::longjump::keybind, var::movement::longjump::kb_style)) {
			render::text(w / 2, h - 79, font, xorstr("lj"), true, indicator_col);
		}
		else if (var::movement::edgejump::enabled && util::bind(var::movement::edgejump::keybind, var::movement::edgejump::kb_style)) {
			render::text(w / 2, h - 79, font, xorstr("ej"), true, indicator_col);
		}
		else if (var::movement::minijump::enabled && util::bind(var::movement::minijump::keybind, var::movement::minijump::kb_style)) {
			render::text(w / 2, h - 79, font, xorstr("mj"), true, indicator_col);
		}
		else if (var::movement::ladderglide::enabled && util::bind(var::movement::ladderglide::keybind, var::movement::ladderglide::kb_style)) {
			render::text(w / 2, h - 79, font, xorstr("lg"), true, indicator_col);
		}
	}
}