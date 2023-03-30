#pragma once
#include "../../dependencies/utilities/csgo.hpp"
#include "../../dependencies/imgui/imgui.h"
#include "../../dependencies/imgui/imgui_impl_dx9.h"
#include "../../dependencies/imgui/imgui_impl_win32.h"
#include "variables.hpp"
#include "config.hpp"
#include "fonts.h"
#include "../features/skins/skins.hpp"

namespace menu {
	inline bool opened = false;
	inline bool initialized = false;
	inline HWND window;
	inline WNDPROC original_process;
	inline ImFont* defaultfont;
	inline ImFont* title;
	inline ImFont* group;
	inline ImFont* icons;

	void render();
	bool initialize(IDirect3DDevice9* device);
	void release();

	namespace tabs {
		void aim();
		void aim_other();
		void visual();
		void visual_local();
		void esp();
		void esp_model();
		void misc();
		void misc_movement();
		void config();
		void config_extra();
	}

	LRESULT WINAPI wndproc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam);
};