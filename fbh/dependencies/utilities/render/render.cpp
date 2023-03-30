#include <pch.h>
#include "render.hpp"

unsigned long render::fonts::watermark_font;
unsigned long render::fonts::esp_font;
unsigned long render::fonts::esp_flags_font;
unsigned long render::fonts::indicators_font;
unsigned long render::fonts::indicators_font2;
unsigned long render::fonts::indicators_font3;
unsigned long render::fonts::indicators_font4;
unsigned long render::fonts::indicators_font5;

void render::initialize() {
	// Create sureface fonts
	render::fonts::watermark_font = interfaces::surface->font_create();
	render::fonts::esp_font = interfaces::surface->font_create();
	render::fonts::esp_flags_font = interfaces::surface->font_create();
	render::fonts::indicators_font = interfaces::surface->font_create();
	render::fonts::indicators_font2 = interfaces::surface->font_create();
	render::fonts::indicators_font3 = interfaces::surface->font_create();
	render::fonts::indicators_font4 = interfaces::surface->font_create();
	render::fonts::indicators_font5 = interfaces::surface->font_create();

	interfaces::surface->set_font_glyph(render::fonts::watermark_font, xorstr("Tahoma"), 11, 500, 0, 0, font_flags::fontflag_dropshadow);
	interfaces::surface->set_font_glyph(render::fonts::esp_font, xorstr("Tahoma"), 11, 500, 0, 0, font_flags::fontflag_outline);
	interfaces::surface->set_font_glyph(render::fonts::esp_flags_font, xorstr("Small Fonts"), 10, 400, 0, 0, font_flags::fontflag_outline);
	interfaces::surface->set_font_glyph(render::fonts::indicators_font, xorstr("Ink Free"), 30, 999, 0, 0, font_flags::fontflag_antialias);
	interfaces::surface->set_font_glyph(render::fonts::indicators_font2, xorstr("Verdana"), 30, 620, 0, 0, font_flags::fontflag_antialias);
	interfaces::surface->set_font_glyph(render::fonts::indicators_font3, xorstr("Impact"), 35, 400, 0, 0, font_flags::fontflag_antialias);
	interfaces::surface->set_font_glyph(render::fonts::indicators_font4, xorstr("Tahoma"), 30, 725, 0, 0, font_flags::fontflag_antialias);
	interfaces::surface->set_font_glyph(render::fonts::indicators_font5, xorstr("Arial"), 30, 600, 0, 0, font_flags::fontflag_antialias);

	console::log(xorstr("render initialized\n"));
}

void render::draw_line(std::int32_t x1, std::int32_t y1, std::int32_t x2, std::int32_t y2, color color) {
	interfaces::surface->set_drawing_color(color.r, color.g, color.b, color.a);
	interfaces::surface->draw_line(x1, y1, x2, y2);
}

void render::text(std::int32_t x, std::int32_t y, unsigned long font, const wchar_t* text, bool centered, color color) {
	interfaces::surface->draw_text_font(font);
	int text_width, text_height;

	if (centered) {
		interfaces::surface->get_text_size(font, text, text_width, text_height);
		interfaces::surface->draw_text_pos(x - text_width / 2, y);
	} else
		interfaces::surface->draw_text_pos(x, y);

	interfaces::surface->set_text_color(color.r, color.g, color.b, color.a);
	interfaces::surface->draw_render_text(text, wcslen(text));
}

void render::text(std::int32_t x, std::int32_t y, unsigned long font, std::string text, bool centered, color color) {
	wchar_t temp[128];
	int text_width, text_height;
	if (MultiByteToWideChar(CP_UTF8, 0, text.c_str(), -1, temp, 128) > 0) {
		interfaces::surface->draw_text_font(font);
		if (centered) {
			interfaces::surface->get_text_size(font, temp, text_width, text_height);
			interfaces::surface->draw_text_pos(x - text_width / 2, y);
		} else
			interfaces::surface->draw_text_pos(x, y);
		interfaces::surface->set_text_color(color.r, color.g, color.b, color.a);
		interfaces::surface->draw_render_text(temp, wcslen(temp));
	}
}

void render::draw_rect(std::int32_t x, std::int32_t y, std::int32_t width, std::int32_t height, color color) {
	interfaces::surface->set_drawing_color(color.r, color.g, color.b, color.a);
	interfaces::surface->draw_outlined_rect(x, y, width, height);
}

void render::draw_filled_rect(std::int32_t x, std::int32_t y, std::int32_t width, std::int32_t height, color color) {
	interfaces::surface->set_drawing_color(color.r, color.g, color.b, color.a);
	interfaces::surface->draw_filled_rectangle(x, y, width, height);
}

void render::draw_rect_fade_vertical(std::int32_t x, std::int32_t y, std::int32_t width, std::int32_t height, color top, color bottom) {
	interfaces::surface->set_drawing_color(top.r, top.g, top.b, top.a);
	interfaces::surface->draw_filled_rect_fade(x, y, width, height, 255, 255, false);
	interfaces::surface->set_drawing_color(bottom.r, bottom.g, bottom.b, bottom.a);
	interfaces::surface->draw_filled_rect_fade(x, y, width, height, 0, 255, false);
}

void render::draw_rect_fade_horizontal(std::int32_t x, std::int32_t y, std::int32_t width, std::int32_t height, color left, color right) {
	interfaces::surface->set_drawing_color(left.r, left.g, left.b, left.a);
	interfaces::surface->draw_filled_rect_fade(x, y, width, height, 255, 255, true);
	interfaces::surface->set_drawing_color(right.r, right.g, right.b, right.a);
	interfaces::surface->draw_filled_rect_fade(x, y, width, height, 0, 255, true);
}

void render::draw_outline(std::int32_t x, std::int32_t y, std::int32_t width, std::int32_t height, color color) {
	interfaces::surface->set_drawing_color(color.r, color.g, color.b, color.a);
	interfaces::surface->draw_outlined_rect(x, y, width, height);
}

void render::draw_textured_polygon(std::int32_t vertices_count, vertex_t* vertices, color color) {
	static unsigned char buf[4] = { 255, 255, 255, 255 };
	unsigned int texture_id{};
	if (!texture_id) {
		texture_id = interfaces::surface->create_new_texture_id(true);
		interfaces::surface->set_texture_rgba(texture_id, buf, 1, 1);
	}
	interfaces::surface->set_drawing_color(color.r, color.g, color.b, color.a);
	interfaces::surface->set_texture(texture_id);
	interfaces::surface->draw_polygon(vertices_count, vertices);
}

void render::draw_circle(std::int32_t x, std::int32_t y, std::int32_t radius, std::int32_t segments, color color) {
	float step = M_PI * 2.0 / segments;
	for (float a = 0; a < (M_PI * 2.0); a += step) {
		float x1 = radius * cos(a) + x;
		float y1 = radius * sin(a) + y;
		float x2 = radius * cos(a + step) + x;
		float y2 = radius * sin(a + step) + y;
		interfaces::surface->set_drawing_color(color.r, color.g, color.b, color.a);
		interfaces::surface->draw_line(x1, y1, x2, y2);
	}
}

void render::draw_circle_filled(std::int32_t x, std::int32_t y, std::int32_t points, std::int32_t radius, color color) {
	std::vector<vertex_t> vertices;
	float step = M_PI_F * 2.0f / points;
	for (float a = 0; a < (M_PI_F * 2.0f); a += step)
		vertices.push_back(vertex_t(vec2_t(radius * cosf(a) + x, radius * sinf(a) + y)));

	interfaces::surface->set_drawing_color(color.r, color.g, color.b, color.a);
	interfaces::surface->draw_textured_polygon(points, vertices.data());
}

void render::draw_corner_box(int x, int y, int w, int h, color color) {
	interfaces::surface->set_drawing_color(color.r, color.g, color.b, color.a);
	interfaces::surface->draw_line(x, y, x, y + (h / 5));
	interfaces::surface->draw_line(x, y, x + (w / 5), y);
	interfaces::surface->draw_line(x + w, y, x + w - (w / 5), y);
	interfaces::surface->draw_line(x + w, y, x + w, y + (h / 5));
	interfaces::surface->draw_line(x, y + h, x + (w / 5), y + h);
	interfaces::surface->draw_line(x, y + h, x, y + h - (h / 5));
	interfaces::surface->draw_line(x + w, y + h, x + w - (w / 5), y + h);
	interfaces::surface->draw_line(x + w, y + h, x + w, y + h - (h / 5));
}

vec2_t render::get_text_size(unsigned long font, std::string text) {
	std::wstring a(text.begin(), text.end());
	const wchar_t* wstr = a.c_str();
	static int w, h;

	interfaces::surface->get_text_size(font, wstr, w, h);
	return { static_cast<float>(w), static_cast<float>(h) };
}

void render::draw_beam(color clr, int width, int life, int flag, vec3_t start, vec3_t end) {
	BeamInfo_t beam_info;
	beam_info.m_nType = TE_BEAMPOINTS;
	beam_info.m_pszModelName = xorstr("sprites/purplelaser1.vmt");
	beam_info.m_nModelIndex = interfaces::model_info->get_model_index(xorstr("sprites/purplelaser1.vmt"));
	beam_info.m_flHaloScale = 0;
	beam_info.m_flLife = life;
	beam_info.m_flWidth = width;
	beam_info.m_flEndWidth = width;
	beam_info.m_flFadeLength = 0;
	beam_info.m_flAmplitude = 0;
	beam_info.m_flRed = clr.r;
	beam_info.m_flGreen = clr.g;
	beam_info.m_flBlue = clr.b;
	beam_info.m_flBrightness = clr.a;
	beam_info.m_flSpeed = 0;
	beam_info.m_nStartFrame = 0;
	beam_info.m_flFrameRate = 0;
	beam_info.m_nSegments = 2;
	beam_info.m_nFlags = flag;
	beam_info.m_vecStart = start;
	beam_info.m_vecEnd = end;

	auto beam = interfaces::render_beams->create_beam_point(beam_info);
	if (beam) interfaces::render_beams->draw_beam(beam);
}

void render::draw_beam_circle(color clr, int width, vec3_t pos) {
	BeamInfo_t beam_info;
	beam_info.m_nType = TE_BEAMRINGPOINT;
	beam_info.m_pszModelName = xorstr("sprites/purplelaser1.vmt");
	beam_info.m_nModelIndex = interfaces::model_info->get_model_index(xorstr("sprites/purplelaser1.vmt"));
	beam_info.m_flHaloScale = 0;
	beam_info.m_flLife = 0.50f;
	beam_info.m_flWidth = width;
	beam_info.m_flFadeLength = 0;
	beam_info.m_flAmplitude = 0;
	beam_info.m_flRed = clr.r;
	beam_info.m_flGreen = clr.g;
	beam_info.m_flBlue = clr.b;
	beam_info.m_flBrightness = clr.a;
	beam_info.m_flSpeed = 0;
	beam_info.m_nStartFrame = 0;
	beam_info.m_flFrameRate = 0;
	beam_info.m_nSegments = -1;
	beam_info.m_nFlags = FBEAM_SHADEIN;
	beam_info.m_vecCenter = pos;
	beam_info.m_flStartRadius = 50;
	beam_info.m_flEndRadius = 500;

	auto beam = interfaces::render_beams->create_beam_ring_point(beam_info);
	if (beam) interfaces::render_beams->draw_beam(beam);
}

void render::draw_dlight(player_t* player, color clr, int radius) {
	vec3_t origin = player->origin();
	dlight_t* dlight = interfaces::effects->cl_alloc_dlight(player->index());
	dlight->color.r = clr.r;
	dlight->color.g = clr.g;
	dlight->color.b = clr.b;
	dlight->color.exponent = 5.f;
	dlight->direction = origin;
	dlight->origin = origin;
	dlight->radius = radius;
	dlight->die_time = interfaces::globals->cur_time + 0.1f;
	dlight->decay = dlight->radius / 2.f;
	dlight->key = player->index();
}
