#pragma once
#include "../../../dependencies/utilities/csgo.hpp"

namespace prediction {
	bool in_prediction();
	void start(c_usercmd* cmd);
	void end();
	void restore(int predicted_frame);

	inline bool in_progress;
	inline player_move_data data;
	inline float old_cur_time;
	inline float old_frame_time;
	inline int* prediction_random_seed;
};
