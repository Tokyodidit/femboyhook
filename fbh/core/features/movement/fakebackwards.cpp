#include <pch.h>
#include "../features.hpp"

// this isnt object orientated, please cry that im locally storing these bariables here :big_smile:

// we add this to our view angle
float adjusted_angle = 0.f;
// the last time we clicked out keybind
float last_update_time = 0.f;
// if we should actually spin around or not
bool should_adjust = false;
// turns true if we need to quickly turn around for ladders n shit
bool readjust = false;

// TODO: fix this rofl, left it as static for now tho.
void features::movement::fakebackwards(c_usercmd* cmd) {
	// checks if in game
	if (!interfaces::engine->is_in_game() || !csgo::local_player->is_alive()) return;

	should_adjust = util::bind(var::movement::fakebackwards::keybind, var::movement::fakebackwards::kb_style);

	readjust = (csgo::local_player->move_type() == movetype_ladder || csgo::local_player->move_type() == movetype_noclip) || (cmd->buttons & in_attack);

	const auto adjust_angle = [](bool should_adjust, bool should_readjust, int angle) -> float {
		if (should_readjust) return 0.f;
		if (!should_adjust) return 0.f;
		switch (angle) {
		case 0: // right
			return 90.f;
			break;
		case 1: // backwards
			return 180.f;
			break;
		case 2: // right
			return -90.f; // this might need to be 270.f i dont know yet :big_smile:
			break;
		default: // what the fork....
			return 0.f;
		}
	};

	const auto frametime = [&](float ms) -> float { return (1.f / ms) * interfaces::globals->frame_time; };

	// goofy ah naming idc
	const auto wanted_angle = adjust_angle(should_adjust, readjust, var::movement::fakebackwards::angle);

	// TODO: upon pressing our bind we should randomise the adjust time value to make it look more legit (IG). ~ weird
	const auto adjust_time = readjust ? 0.6f : 0.3f;

	adjusted_angle += (wanted_angle - adjusted_angle) * frametime(adjust_time);

	if (should_adjust && !readjust)
		cmd->viewangles.y += wanted_angle; //adjusted_angle;

	cmd->buttons &= ~(in_forward | in_back | in_moveright | in_moveleft);
	cmd->forwardmove = -1;
	cmd->sidemove = -1;
}

void features::movement::fakebackwards_render() {
	// checks if in game
	if (!interfaces::engine->is_in_game() || !csgo::local_player->is_alive()) return;
	// ladder and movement checks
	if (csgo::local_player->move_type() == movetype_ladder || csgo::local_player->move_type() == movetype_noclip) return;
	// checks if attacking
	if (csgo::global_cmd->buttons & in_attack) return;
	// keybind check
	if (!util::bind(var::movement::fakebackwards::keybind, var::movement::fakebackwards::kb_style)) return;

	// TODO: add a circle that spins, maybe a poly too so its filled. that would be pretty nice.
}