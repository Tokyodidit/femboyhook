#include <pch.h>
#include "notifications.hpp"

void notify::run(std::string text, bool console, bool chat) {
	// Print in console
	if (console) {
		interfaces::console->console_color_printf({ 196, 41, 213, 255 }, xorstr("[fbh] "));
		interfaces::console->console_printf(text.append(xorstr("\n")).c_str());
	}

	// Print in chat
	if (chat && interfaces::engine->is_in_game() && csgo::local_player && interfaces::chat_element) {
		std::string message = xorstr(" \x0E[fbh]\x01 ") + text;
		interfaces::chat_element->chat_printf(0, 0, message.c_str());
	}
}