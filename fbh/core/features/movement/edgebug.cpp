#include <pch.h>
#include "../features.hpp"

// Credits to nateboss105 the goat for the edgebugger :D

// Edgebug variables
bool edgebugging, ducking = false;
int tick, eb_counter = 0;
float last_set = 0;
vec3_t eb_pos;

// Edgebug detected
bool features::movement::edgebug::is_detected() {
	return edgebugging;
}

void features::movement::edgebug::lock(c_usercmd* cmd) {
	// Sanity checks
	if (!interfaces::engine->is_in_game() || !csgo::local_player->is_alive()) return;

	// Is in edgebug
	if (edgebugging) {
		prediction::restore(interfaces::prediction->Split->nCommandsPredicted - 1);
		if (csgo::local_player->flags() & fl_onground || tick < cmd->tick_count) {
			//eb_counter++;
			notify::run(xorstr("eb assisted"), false, var::misc::movement_notify);
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
			if (var::misc::effects::detection_beam) render::draw_beam_circle(color(var::misc::effects::color), 3, eb_pos);
			// Release movement
			last_set = interfaces::globals->cur_time + 3.0f;
			edgebugging = false;
			return;
		}

		// No movement for you
		cmd->sidemove = 0.f;
		cmd->forwardmove = 0.f;
		cmd->upmove = 0.f;
		cmd->mousedx = 0.f;

		// Lock movement
		if (ducking) {
			cmd->buttons |= in_duck; // Force duck
		}
		else {
			cmd->buttons &= ~in_duck; // Force stand
		}
		return;
	}
}

void features::movement::edgebug::run(c_usercmd* cmd) {
	// Return if we are edgebugging
	if (edgebugging) return;

	// Sanity checks
	if (!interfaces::engine->is_in_game() || !csgo::local_player->is_alive()) return;

	// Keybind check
	if (!util::bind(var::movement::edgebug::keybind, var::movement::edgebug::kb_style)) return;

	// Check for edgebug
	if ((csgo::local_player->flags() & fl_onground || csgo::local_player->move_type() == movetype_ladder || csgo::local_player->move_type() == movetype_noclip) || csgo::local_player->velocity().z >= 0) return;

	for (int s = 0; s < 2; s++) {
		// Break if found in first scenario
		if (edgebugging) break;

		// Restore to first tick
		prediction::restore(interfaces::prediction->Split->nCommandsPredicted - 1);

		int flags = csgo::local_player->flags();
		vec3_t velocity = csgo::local_player->velocity();

		for (int i = 0; i < var::movement::ticks; i++) {
			c_usercmd* scenario = new c_usercmd(*cmd);

			// Send movement for scenario
			scenario->sidemove = 0.f;
			scenario->forwardmove = 0.f;
			scenario->upmove = 0.f;
			scenario->mousedx = 0.f;

			if (s == 0) {
				scenario->buttons |= in_duck;
			}
			else {
				scenario->buttons &= ~in_duck;
			}

			// Start the prediction
			prediction::start(scenario);

			if (floor(velocity.z) < -7 && floor(csgo::local_player->velocity().z) == -7 && !(flags & fl_onground)) {
				// Edgebug detected
				tick = cmd->tick_count + i;
				ducking = (s == 0);
				eb_pos = csgo::local_player->origin();
				edgebugging = true;
				break;
			}
			else if ((flags & fl_onground) || csgo::local_player->move_type() == movetype_ladder) break;

			// Replace old edgebug detection variables
			velocity = csgo::local_player->velocity();
			flags = csgo::local_player->flags();
		}
		prediction::end();
	}
}

void features::movement::edgebug::draw() {
	// Sanity checks
	if (!interfaces::engine->is_in_game() || !csgo::local_player->is_alive()) return;

	// Edgebug detection indicator
	vec2_t pos;
	if (math::world_to_screen(eb_pos, pos) && last_set > interfaces::globals->cur_time) {
		render::draw_circle_filled(pos.x, pos.y, 4, 4, color(var::misc::detection_indicator::color));
	}
}