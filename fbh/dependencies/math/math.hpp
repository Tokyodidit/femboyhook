#pragma once

namespace math {
	void correct_movement(vec3_t old_angles, c_usercmd* cmd, float old_forwardmove, float old_sidemove);
	vec3_t calculate_angle(const vec3_t& source, const vec3_t& destination, const vec3_t& viewangles);
	float calculate_fov(const vec3_t& source, const vec3_t& destination, const vec3_t& viewangles);
	void sin_cos(float r, float* s, float* c);
	vec3_t angle_vector(vec3_t angle);
	void transform_vector(vec3_t&, matrix_t&, vec3_t&);
	void vector_angles(const vec3_t&, vec3_t&);
	void angle_vectors(vec3_t&, vec3_t*, vec3_t*, vec3_t*);
	void angle_vectors(const vec3_t&, vec3_t*);
	vec3_t vector_add(vec3_t&, vec3_t&);
	vec3_t vector_subtract(vec3_t&, vec3_t&);
	vec3_t vector_multiply(vec3_t&, vec3_t&);
	vec3_t vector_divide(vec3_t&, vec3_t&);
	bool screen_transform(const vec3_t& point, vec3_t& screen);
	bool world_to_screen(const vec3_t& origin, vec2_t& screen);
	color color_lerp(color a, color b, float t);
	color color_alpha(color a, float t);
	color color_lerpa(color a, color b, float t);

};
