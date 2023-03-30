#include <pch.h>
#include "../features.hpp"

void features::misc::auto_weapon(c_usercmd* cmd) {
	// Sanity checks
	if (!interfaces::engine->is_in_game() || !csgo::local_player->is_alive()) return;

	// Check if we have a weapon and it has ammo
	auto weapon = csgo::local_player->active_weapon();
	if (!weapon || weapon->clip1_count() <= 0) return;

	auto weapon_data = weapon->get_weapon_data();
	if (!weapon_data || weapon_data->weapon_full_auto) return;

	if (weapon->next_primary_attack() > csgo::local_player->get_tick_base() * interfaces::globals->interval_per_tick) 
		cmd->buttons &= ~in_attack;
}
