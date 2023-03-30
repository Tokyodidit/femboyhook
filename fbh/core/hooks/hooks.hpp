#pragma once

namespace hooks {
	bool initialize();
	void release();

	inline unsigned int get_virtual(void* _class, unsigned int index) { return static_cast<unsigned int>((*static_cast<int**>(_class))[index]); }

	namespace create_move {
		using fn = bool(__stdcall*)(float, c_usercmd*);
		bool __stdcall run(float input_sample_frametime, c_usercmd* cmd);
	}

	namespace paint_traverse {
		using fn = void(__thiscall*)(i_panel*, unsigned int, bool, bool);
		void __stdcall run(unsigned int panel, bool force_repaint, bool allow_force);
	}

	namespace present {
		using fn = long(__stdcall*)(IDirect3DDevice9*, RECT*, RECT*, HWND, RGNDATA*);
		long __stdcall run(IDirect3DDevice9* device, RECT* source_rect, RECT* dest_rect, HWND dest_window_override, RGNDATA* dirty_region);
	}

	namespace reset {
		using fn = long(__thiscall*)(void*, IDirect3DDevice9*, D3DPRESENT_PARAMETERS*);
		long __stdcall run(IDirect3DDevice9* device, D3DPRESENT_PARAMETERS* params);
	}

	namespace emit_sound {
		using fn = void(__thiscall*)(void*, void*, int, int, const char*, unsigned int, const char*, float, int, float, int, int, const vec3_t*, const vec3_t*, void*, bool, float, int, int);
		void __stdcall run(void* filter, int index, int ichannel, const char* soundentry, unsigned int soundhash, const char* sample, float volume, int seed, float flattenuation, int iflags, int ipitch, const vec3_t* origin, const vec3_t* direction, void* utlvecorigins, bool updatepositions, float soundtime, int speakerentity, int unk);
	}

	namespace onscreen_sizechanged {
		using fn = void(__thiscall*)(void*, int, int);
		void __fastcall run(void* thisptr, int edx, int oldwidth, int oldheight);
	}

	namespace is_connected {
		using fn = bool(__thiscall*)(iv_engine_client*);
		bool __stdcall run();
	}

	namespace override_mouse_input {
		using fn = void(__fastcall*)(void*, int, float*, float*);
		void __fastcall run(void* thisptr, int edx, float* x, float* y);
	}

	namespace get_color_modulation {
		using fn = void(__thiscall*)(void*, float*, float*, float*);
		void __fastcall run(void* ecx, void* edx, float* r, float* g, float* b);
	}

	namespace frame_stage_notify {
		using fn = void(__thiscall*)(void*, int);
		void __stdcall run(int stage);
	}

	namespace override_view {
		using fn = void(__thiscall*)(i_client_mode*, view_setup_t*);
		void __stdcall run(view_setup_t* setup);
	}

	namespace aspect_ratio {
		using fn = void(__fastcall*)(void*, void*, int32_t, int32_t);
		float __fastcall run(void* ecx, void* edx, int32_t width, int32_t height);
	}

	namespace viewmodel_fov {
		using fn = float(__thiscall*)();
		float __stdcall run();
	}

	namespace do_post_screen_effects {
		using fn = bool(__thiscall*)(void*, view_setup_t*);
		bool __stdcall run(view_setup_t* setup);
	}

	namespace draw_model_execute {
		using fn = void(__fastcall*)(void*, int, i_mat_render_context*, const draw_model_state_t&, const model_render_info_t&, matrix_t*);
		void __fastcall run(void* thisptr, int edx, i_mat_render_context* ctx, const draw_model_state_t& state, const model_render_info_t& pInfo, matrix_t* pCustomBoneToWorld);
	}

	namespace list_leaves_in_box {
		using fn = int(__thiscall*)(void*, const vec3_t&, const vec3_t&, unsigned short*, int);
		int __fastcall run(void* bsp, void* edx, const vec3_t& mins, const vec3_t& maxs, unsigned short* list, int list_max);
	}

	namespace check_file_crcserver {
		using fn = void(__thiscall*)(void*, void*);
		void __fastcall run(void*, void*);
	}

	namespace loose_file_allowed {
		using fn = bool(__thiscall*)(void*, void*);
		bool __fastcall run(void*, void*);
	}

	namespace alloc_key_values {
		using fn = void* (__thiscall*)(void*, const std::int32_t);
		void* __stdcall run(const std::int32_t size);
	}

	namespace modify_eye_position {
		using fn = void(__fastcall*)(LPVOID, uint32_t, vec3_t&);
		void __fastcall run(LPVOID ecx, uint32_t, vec3_t& inputeyeposition);
	}

	namespace override_config {
		using fn = bool(__thiscall*)(void*, void*, material_system_config_t*, bool);
		bool __fastcall run(void* ecx, void* edx, material_system_config_t* config, bool update);
	}

	namespace is_depth_of_field {
		using fn = bool(__thiscall*)();
		bool __stdcall run();
	}

	namespace set_visuals_data {
		using fn = bool(__fastcall*)(void*, void*, const char*);
		void __fastcall run(void* ecx, void* edx, const char* shader_name);
	}

	namespace particle_collection_simulate {
		using fn = void(__thiscall*)(particle_collection*);
		void __fastcall run(particle_collection* this_ptr, void* edx);
	}
}