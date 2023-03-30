#pragma once
#include "../../../dependencies/interfaces/i_game_event_manager.hpp"

class event_manager : public i_game_event_listener2 {
public:
	void fire_game_event(i_game_event* event);
	void initialize();
	void release();
};
extern event_manager event_listener;
