#include <pch.h>
#include "../features.hpp"

void features::movement::autoalign(c_usercmd* cmd) {
	// Sanity checks
	if (!interfaces::engine->is_in_game() || !csgo::local_player->is_alive()) return;

	// Movement checks
	if (csgo::local_player->move_type() == movetype_ladder || csgo::local_player->move_type() == movetype_noclip) return;

	vec3_t wishdir;
	bool done = false;

	if ((cmd->buttons & in_forward) && !(cmd->buttons & in_back) && !(cmd->buttons & in_moveleft) && !(cmd->buttons & in_moveright)) {
		wishdir = { std::cos(DEG2RAD(cmd->viewangles.y)) * 17.f, std::sin(DEG2RAD(cmd->viewangles.y)) * 17.f, 0.f };
		done = true;
	}
	if ((cmd->buttons & in_back) && !(cmd->buttons & in_forward) && !(cmd->buttons & in_moveleft) && !(cmd->buttons & in_moveright)) {
		wishdir = { std::cos(DEG2RAD(cmd->viewangles.y + 180.f)) * 17.f, std::sin(DEG2RAD(cmd->viewangles.y + 180.f)) * 17.f, 0.f };
		done = true;
	}
	if ((cmd->buttons & in_moveleft) && !(cmd->buttons & in_back) && !(cmd->buttons & in_forward) && !(cmd->buttons & in_moveright)) {
		wishdir = { std::cos(DEG2RAD(cmd->viewangles.y + 90.f)) * 17.f, std::sin(DEG2RAD(cmd->viewangles.y + 90.f)) * 17.f, 0.f };
		done = true;
	}
	if ((cmd->buttons & in_moveright) && !(cmd->buttons & in_back) && !(cmd->buttons & in_moveleft) && !(cmd->buttons & in_forward)) {
		wishdir = { std::cos(DEG2RAD(cmd->viewangles.y - 90.f)) * 17.f, std::sin(DEG2RAD(cmd->viewangles.y - 90.f)) * 17.f, 0.f };
		done = true;
	}

	if (!done)
		return;

	const auto startPos = csgo::local_player->abs_origin();
	const auto endPos = startPos + wishdir;

	trace_t trace;
	trace_filter filter;
	filter.skip = csgo::local_player;
	ray_t ray;
	ray.initialize(startPos, endPos);
	interfaces::trace_ray->run(ray, MASK_PLAYERSOLID, &filter, &trace);
	if ((trace.flFraction < 1.f) && (trace.plane.normal.z == 0.f)) {
		vec3_t Angles{ trace.plane.normal.x * -16.005f, trace.plane.normal.y * -16.005f, 0.f };
		const auto endPos2 = startPos + Angles;
		trace_t trace2;
		ray_t ray2;
		ray.initialize(startPos, endPos2);
		interfaces::trace_ray->run(ray2, MASK_PLAYERSOLID, &filter, &trace2);
		if (trace.plane != trace2.plane) {
			vec3_t to_wall = Angles.toangle();
			float mVel = hypotf(csgo::local_player->velocity().x, csgo::local_player->velocity().y);
			float ideal = RAD2DEG(atanf(28.33f / mVel));
			vec3_t dvelo = csgo::local_player->velocity();
			dvelo.z = 0.f;
			vec3_t velo_angle = dvelo.toangle();
			vec3_t delta = velo_angle - to_wall;
			delta.normalize();
			if (delta.y >= 0.f)
				to_wall.y += ideal;
			else
				to_wall.y -= ideal;
			float rotation = DEG2RAD(to_wall.y - cmd->viewangles.y);
			float cos_rot = cos(rotation);
			float sin_rot = sin(rotation);

			float forwardmove = cos_rot * 450.f;
			float sidemove = -sin_rot * 450.f;
			cmd->forwardmove = forwardmove;
			cmd->sidemove = sidemove;
		}
	}
}