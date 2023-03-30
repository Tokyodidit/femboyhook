#include <pch.h>
#include "../utilities/csgo.hpp"

void math::correct_movement(vec3_t old_angles, c_usercmd* cmd, float old_forwardmove, float old_sidemove) {
	float delta_view;
	float f1;
	float f2;

	if (old_angles.y < 0.f)
		f1 = 360.0f + old_angles.y;
	else
		f1 = old_angles.y;

	if (cmd->viewangles.y < 0.0f)
		f2 = 360.0f + cmd->viewangles.y;
	else
		f2 = cmd->viewangles.y;

	if (f2 < f1)
		delta_view = abs(f2 - f1);
	else
		delta_view = 360.0f - abs(f1 - f2);

	delta_view = 360.0f - delta_view;

	cmd->forwardmove = cos(DEG2RAD(delta_view)) * old_forwardmove + cos(DEG2RAD(delta_view + 90.f)) * old_sidemove;
	cmd->sidemove = sin(DEG2RAD(delta_view)) * old_forwardmove + sin(DEG2RAD(delta_view + 90.f)) * old_sidemove;
}

vec3_t math::calculate_angle(const vec3_t& source, const vec3_t& destination, const vec3_t& viewangles) {
	vec3_t delta = source - destination;
	vec3_t angles;

	angles.z = 0.0f;
	angles.y = RAD2DEG(atanf(delta.y / delta.x)) - viewangles.y;
	angles.x = RAD2DEG(atanf(delta.z / std::hypotf(delta.x, delta.y))) - viewangles.x;

	if (delta.x >= 0.0)
		angles.y += 180.0f;

	angles.normalize();
	return angles;
}

float math::calculate_fov(const vec3_t& source, const vec3_t& destination, const vec3_t& viewangles) {
	auto angle = calculate_angle(source, destination, viewangles);
	auto fov = std::hypot(angle.x, angle.y);
	return fov;
}

void math::sin_cos(float r, float* s, float* c) {
	*s = sin(r);
	*c = cos(r);
}

vec3_t math::angle_vector(vec3_t angle) {
	float sp, sy, cp, cy;
	sin_cos(angle[0] / 180.f * M_PI_F, &sp, &cp);
	sin_cos(angle[1] / 180.f * M_PI_F, &sy, &cy);

	return vec3_t(cp * cy, cp * sy, -sp);
}

void math::transform_vector(vec3_t& a, matrix_t& b, vec3_t& out) {
	out.x = a.dot(b.mat_val[0]) + b.mat_val[0][3];
	out.y = a.dot(b.mat_val[1]) + b.mat_val[1][3];
	out.z = a.dot(b.mat_val[2]) + b.mat_val[2][3];
}

void math::vector_angles(const vec3_t& forward, vec3_t& angles) {
	vec3_t view;
	if (!forward[0] && !forward[1])
	{
		view[0] = 0.0f;
		view[1] = 0.0f;
	}
	else
	{
		view[1] = atan2(forward[1], forward[0]) * 180.0f / M_PI;

		if (view[1] < 0.0f)
			view[1] += 360.0f;

		view[2] = sqrt(forward[0] * forward[0] + forward[1] * forward[1]);
		view[0] = atan2(forward[2], view[2]) * 180.0f / M_PI;
	}

	angles[0] = -view[0];
	angles[1] = view[1];
	angles[2] = 0.f;
}

void math::angle_vectors(vec3_t& angles, vec3_t* forward, vec3_t* right, vec3_t* up) {
	float sp, sy, sr, cp, cy, cr;
	sin_cos(DEG2RAD(angles[0]), &sp, &cp);
	sin_cos(DEG2RAD(angles[1]), &sy, &cy);
	sin_cos(DEG2RAD(angles[2]), &sr, &cr);

	if (forward) {
		forward->x = cp * cy;
		forward->y = cp * sy;
		forward->z = -sp;
	}
	if (right) {
		right->x = -1 * sr * sp * cy + -1 * cr * -sy;
		right->y = -1 * sr * sp * sy + -1 * cr * cy;
		right->z = -1 * sr * cp;
	}
	if (up) {
		up->x = cr * sp * cy + -sr * -sy;
		up->y = cr * sp * sy + -sr * cy;
		up->z = cr * cp;
	}
}

void math::angle_vectors(const vec3_t& angles, vec3_t* forward) {
	float sp, sy, cp, cy;
	sin_cos(DEG2RAD(angles[0]), &sp, &cp);
	sin_cos(DEG2RAD(angles[1]), &sy, &cy);

	forward->x = cp * cy;
	forward->y = cp * sy;
	forward->z = -sp;
}

vec3_t math::vector_add(vec3_t& a, vec3_t& b) {
	return vec3_t(a.x + b.x,
		a.y + b.y,
		a.z + b.z);
}

vec3_t math::vector_subtract(vec3_t& a, vec3_t& b) {
	return vec3_t(a.x - b.x,
		a.y - b.y,
		a.z - b.z);
}

vec3_t math::vector_multiply(vec3_t& a, vec3_t& b) {
	return vec3_t(a.x * b.x,
		a.y * b.y,
		a.z * b.z);
}

vec3_t math::vector_divide(vec3_t& a, vec3_t& b) {
	return vec3_t(a.x / b.x,
		a.y / b.y,
		a.z / b.z);
}

bool math::screen_transform(const vec3_t& point, vec3_t& screen) {
	auto matrix = interfaces::engine->world_to_screen_matrix();

	float w = matrix[3][0] * point.x + matrix[3][1] * point.y + matrix[3][2] * point.z + matrix[3][3];
	screen.x = matrix[0][0] * point.x + matrix[0][1] * point.y + matrix[0][2] * point.z + matrix[0][3];
	screen.y = matrix[1][0] * point.x + matrix[1][1] * point.y + matrix[1][2] * point.z + matrix[1][3];
	screen.z = 0.0f;

	int inverse_width = static_cast<int>((w < 0.001f) ? -1.0f / w :
		1.0f / w);

	screen.x *= inverse_width;
	screen.y *= inverse_width;
	return (w < 0.001f);
}

bool math::world_to_screen(const vec3_t& origin, vec2_t& screen) {
	static std::uintptr_t view_matrix;
	if (!view_matrix)
		view_matrix = *reinterpret_cast<std::uintptr_t*>(reinterpret_cast<std::uintptr_t>(util::pattern_scan(xorstr("client.dll"), xorstr("0F 10 05 ? ? ? ? 8D 85 ? ? ? ? B9"))) + 3) + 176;

	const auto& matrix = *reinterpret_cast<view_matrix_t*>(view_matrix);

	const auto w = matrix.m[3][0] * origin.x + matrix.m[3][1] * origin.y + matrix.m[3][2] * origin.z + matrix.m[3][3];
	if (w < 0.001f)
		return false;

	int x, y;
	interfaces::engine->get_screen_size(x, y);

	screen.x = static_cast<float>(x) / 2.0f;
	screen.y = static_cast<float>(y) / 2.0f;

	screen.x *= 1.0f + (matrix.m[0][0] * origin.x + matrix.m[0][1] * origin.y + matrix.m[0][2] * origin.z + matrix.m[0][3]) / w;
	screen.y *= 1.0f - (matrix.m[1][0] * origin.x + matrix.m[1][1] * origin.y + matrix.m[1][2] * origin.z + matrix.m[1][3]) / w;

	return true;
}

color math::color_lerp(color a, color b, float t) {
	return color(a.r + (b.r - a.r) * t, a.g + (b.g - a.g) * t, a.b + (b.b - a.b) * t, a.a + (b.a - a.a) * t);
}

color math::color_alpha(color a, float t) {
	return color(a.r, a.g, a.b, a.a * t);
}
color math::color_lerpa(color a, color b, float t) {
	return color(a.r + (b.r - a.r) * t, a.g + (b.g - a.g) * t, a.b + (b.b - a.b) * t, (a.a + b.a) / 2 * t);
}