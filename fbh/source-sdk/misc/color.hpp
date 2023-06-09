#pragma once
#include <cstdint>
#include <d3d9.h>

struct color {
	int a, r, g, b;
	color() = default;
	color(const int r, const int g, const int b, const int a = 255) {
		this->r = r;
		this->g = g;
		this->b = b;
		this->a = a;
	}

	explicit color(const float color[4]) {
		this->r = color[0] * 255;
		this->g = color[1] * 255;
		this->b = color[2] * 255;
		this->a = color[3] * 255;
	}

	explicit color(const uint32_t color) {
		this->a = (color >> 24) & 0xff;
		this->r = (color >> 16) & 0xff;
		this->g = (color >> 8) & 0xff;
		this->b = (color & 0xff);
	}

	static color from_uint(const uint32_t uint) {
		return color(uint);
	}

	static D3DCOLOR from_color(const color col) {
		return D3DCOLOR_ARGB(col.a, col.r, col.g, col.b);
	}

	constexpr uint32_t convert() const {
		return ((b & 0x0ff) << 16) | ((g & 0x0ff) << 8) | (r & 0x0ff);
	}

	static color black(const int a = 255) { return { 0, 0, 0, a }; }
	static color white(const int a = 255) { return { 255, 255, 255, a }; }
	static color red(const int   a = 255) { return { 255, 0, 0, a }; }
	static color green(const int a = 255) { return { 0, 255, 0, a }; }
	static color blue(const int  a = 255) { return { 0, 0, 255, a }; }
};
