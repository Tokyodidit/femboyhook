#include <pch.h>
#include "../features.hpp"

bool predicted_ps, pixelsurfing, pixelducking = false;
int ps_counter, pixeltick = 0;
float ps_last_set = 0;
c_usercmd* pixelsurf_cmd;
vec3_t ps_pos;

bool features::movement::pixelsurf::is_detected() {
	return pixelsurfing && !predicted_ps;
}

void features::movement::pixelsurf::lock(c_usercmd* cmd) {
	// Sanity checks
	if (!interfaces::engine->is_in_game() || !csgo::local_player->is_alive()) return;

	// Is in pixelsurf
	if (pixelsurfing) {
		prediction::restore(interfaces::prediction->Split->nCommandsPredicted - 1);
		if (!predicted_ps) {
			if (pixeltick < cmd->tick_count) {
				//ps_counter++;
				notify::run(xorstr("ps assisted"), false, var::misc::movement_notify);
				// Play sound
				switch (var::misc::detection_sound) {
					case 1: interfaces::surface->play_sound(xorstr("buttons\\arena_switch_press_02.wav")); break;
					case 2: interfaces::surface->play_sound(xorstr("survival\\money_collect_05.wav")); break;
					case 3: interfaces::surface->play_sound(xorstr("custom.wav")); break;
				}
				// Spark effect
				if (var::misc::effects::detection_sparks) interfaces::local_effects->Sparks(csgo::local_player->origin(), 4, 4);
				// Boost effect
				if (var::misc::effects::detection_boost) csgo::local_player->health_boost_time() = interfaces::globals->cur_time + 0.5f;
				// Beam effect
				if (var::misc::effects::detection_beam) render::draw_beam_circle(color(var::misc::effects::color), 3, ps_pos);
				// Stop predicted ps
				ps_last_set = interfaces::globals->cur_time + 3.0f;
				predicted_ps = true;
			}
			// Lock movement
			cmd->buttons = pixelsurf_cmd->buttons;
			cmd->viewangles = pixelsurf_cmd->viewangles;
			cmd->sidemove = pixelsurf_cmd->sidemove;
			cmd->forwardmove = pixelsurf_cmd->forwardmove;
			cmd->upmove = pixelsurf_cmd->upmove;
		}

		if (pixelducking) {
			cmd->buttons |= in_duck; // Force duck
		}
		else {
			cmd->buttons &= ~in_duck; // Force stand
		}

		if (predicted_ps && !(csgo::local_player->velocity().z == -6.25)) {
			// Release movement
			pixelsurfing = false;
			predicted_ps = false;
			return;
		}
		return;
	}
}

void features::movement::pixelsurf::run(c_usercmd* cmd) {
	// Return if we are pixelsurfing
	if (pixelsurfing) return;

	// Check for player
	if (!interfaces::engine->is_in_game() || !csgo::local_player->is_alive()) return;

	// Keybind check
	if (!util::bind(var::movement::pixelsurf::keybind, var::movement::pixelsurf::kb_style)) return;
	
	// Feature check
	if (var::movement::jumpbug::enabled && util::bind(var::movement::jumpbug::keybind, var::movement::jumpbug::kb_style)) return;
    if (var::movement::longjump::enabled && util::bind(var::movement::longjump::keybind, var::movement::longjump::kb_style)) return;

	// Movement checks
	if ((csgo::local_player->flags() & fl_onground || csgo::local_player->move_type() == movetype_ladder || csgo::local_player->move_type() == movetype_noclip)) return;

	// Check if we are using eb
	if (csgo::local_player->velocity().z == -6.25 || features::movement::edgebug::is_detected() || GetAsyncKeyState(var::movement::edgebug::keybind) && var::movement::edgebug::enabled) return;

	for (int s = 0; s < 2; s++) {
		// Break if found in first scenario
		if (pixelsurfing) break;

		// Restore to first tick
		prediction::restore(interfaces::prediction->Split->nCommandsPredicted - 1);

		int flags = csgo::local_player->flags();
		vec3_t velocity = csgo::local_player->velocity();

		for (int i = 0; i < var::movement::ticks; i++) {
			c_usercmd* scenario = new c_usercmd(*cmd);

			// Send duck for scenario
			if (s == 0) {
				scenario->buttons |= in_duck;
			}
			else {
				scenario->buttons &= ~in_duck;
			}

			// start the prediction
			prediction::start(scenario);

			if (flags & fl_onground) break;

			if (csgo::local_player->velocity().z == -6.25 && velocity.z == -6.25) {
				// pixelsurf detected
				pixeltick = cmd->tick_count + i;
				pixelsurf_cmd = scenario;
				pixelducking = (s == 0);
				ps_pos = csgo::local_player->origin();
				pixelsurfing = true;
				break;
			}

			// Replace old pixelsurf detection variables
			velocity = csgo::local_player->velocity();
			flags = csgo::local_player->flags();
		}
		prediction::end();
	}
}

void features::movement::pixelsurf::draw() {
	// Sanity checks
	if (!interfaces::engine->is_in_game() || !csgo::local_player->is_alive()) return;

	// Pixel surf detection indicator
	vec2_t pos;
	if (math::world_to_screen(ps_pos, pos) && ps_last_set > interfaces::globals->cur_time) {
		render::draw_circle_filled(pos.x, pos.y, 4, 4, color(var::misc::detection_indicator::color));
	}
}