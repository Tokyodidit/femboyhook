#include <pch.h>
#include "../features.hpp"

std::vector<std::string> clantag_frames{ xorstr("$"), xorstr("S$"), xorstr("St"), xorstr("St$"), xorstr("Sta"), xorstr("Sta$"), xorstr("Star"), xorstr("Star$"), xorstr("Star."), xorstr("Star.$"), xorstr("Star.h"), xorstr("Star.h$"), xorstr("Star.ho"), xorstr("Star.ho$"), xorstr("Star.hoo"), xorstr("Star.hoo$")};
int last_frame;
bool reset = false;

void features::misc::clantag() {
	// Sanity checks
	if (!interfaces::engine->is_in_game() || !csgo::local_player) return;

	if (var::misc::clantag) {
		// This will move 1 frame every second
		float tps = 0.4f / interfaces::globals->interval_per_tick;
		int current_frame = static_cast<int>(floor(interfaces::globals->tick_count / tps)) % clantag_frames.size();

		// Check if last frame was the current frame
		if (last_frame != current_frame) {
			util::set_clantag(clantag_frames[current_frame].c_str());
			last_frame = current_frame;
		}

		reset = true;
	}
	else if (reset) {
		// Reset clantag
		util::set_clantag(xorstr(""));
		reset = false;
	}
}