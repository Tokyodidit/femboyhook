#pragma once
#include "../../source-sdk/math/vector3d.hpp"
#include "../../source-sdk/misc/color.hpp"

class iv_debug_overlay {
public:
	void add_box_overlay(const vec3_t& origin, const vec3_t& min, const vec3_t& max, const vec3_t& orientation, color clr, float duration) {
		using original_fn = void(__thiscall*)(void*, const vec3_t&, const vec3_t&, const vec3_t&, const vec3_t&, int, int, int, int, float);
		return (*(original_fn**)this)[1](this, origin, min, max, orientation, clr.r, clr.g, clr.b, clr.a, duration);
	}

	void add_line_overlay(const vec3_t& origin, const vec3_t& dst, color clr, bool depth, float duration) {
		using original_fn = int(__thiscall*)(iv_debug_overlay*, const vec3_t&, const vec3_t&, int, int, int, bool, float);
		(*(original_fn**)this)[5](this, origin, dst, clr.r, clr.g, clr.b, depth, duration);
	}

	bool world_to_screen(const vec3_t& in, vec3_t& out) {
		using original_fn = int(__thiscall*)(iv_debug_overlay*, const vec3_t&, vec3_t&);
		int return_value = (*(original_fn * *)this)[13](this, in, out);
		return static_cast<bool>(return_value != 1);
	}

	bool screen_position(const vec3_t& in, vec3_t& out) {
		using original_fn = bool(__thiscall*)(iv_debug_overlay*, const vec3_t&, vec3_t&);
		return (*(original_fn * *)this)[11](this, std::ref(in), std::ref(out));
	}
};