#include <pch.h>
#include "../features/features.hpp"

hooks::create_move::fn create_move_original = nullptr;
hooks::paint_traverse::fn paint_traverse_original = nullptr;
hooks::present::fn present_original = nullptr;
hooks::reset::fn reset_original = nullptr;
hooks::emit_sound::fn emit_sound_original = nullptr;
hooks::onscreen_sizechanged::fn onscreen_sizechanged_original = nullptr;
hooks::is_connected::fn is_connected_original = nullptr;
hooks::override_mouse_input::fn override_mouse_input_original = nullptr;
hooks::get_color_modulation::fn get_color_modulation_original = nullptr;
hooks::frame_stage_notify::fn frame_stage_notify_original = nullptr;
hooks::override_view::fn override_view_original = nullptr;
hooks::aspect_ratio::fn aspect_ratio_original = nullptr;
hooks::viewmodel_fov::fn viewmodel_fov_original = nullptr;
hooks::do_post_screen_effects::fn do_post_screen_effects_original = nullptr;
hooks::draw_model_execute::fn draw_model_execute_original = nullptr;
hooks::list_leaves_in_box::fn list_leaves_in_box_original = nullptr;
hooks::check_file_crcserver::fn check_file_crcserver_original = nullptr;
hooks::loose_file_allowed::fn loose_file_allowed_original = nullptr;
hooks::alloc_key_values::fn alloc_key_values_original = nullptr;
hooks::modify_eye_position::fn modify_eye_position_original = nullptr;
hooks::override_config::fn override_config_original = nullptr;
hooks::is_depth_of_field::fn is_depth_of_field_original = nullptr;
hooks::set_visuals_data::fn set_visuals_data_original = nullptr;
hooks::particle_collection_simulate::fn particle_collection_simulate_original = nullptr;

bool hooks::initialize() {
	auto create_move_target = reinterpret_cast<void*>(get_virtual(interfaces::clientmode, 24));
	auto paint_traverse_target = reinterpret_cast<void*>(get_virtual(interfaces::panel, 41));
	auto present_target = reinterpret_cast<void*>(get_virtual(interfaces::directx, 17));
	auto reset_target = reinterpret_cast<void*>(get_virtual(interfaces::directx, 16));
	auto emit_sound_target = reinterpret_cast<void*>(get_virtual(interfaces::engine_sound, 5));
	auto onscreen_sizechanged_target = reinterpret_cast<void*>(get_virtual(interfaces::surface, 116));
	auto is_connected_target = reinterpret_cast<void*>(get_virtual(interfaces::engine, 27));
	auto override_mouse_input_target = reinterpret_cast<void*>(get_virtual(interfaces::clientmode, 23));
	auto get_color_modulation_target = reinterpret_cast<void*>(util::pattern_scan(xorstr("materialsystem.dll"), xorstr("55 8B EC 83 EC ? 56 8B F1 8A 46")));
	auto frame_stage_notify_target = reinterpret_cast<void*>(get_virtual(interfaces::client, 37));
	auto override_view_target = reinterpret_cast<void*>(get_virtual(interfaces::clientmode, 18));
	auto aspect_ratio_target = reinterpret_cast<void*>(get_virtual(interfaces::engine, 101));
	auto viewmodel_fov_target = reinterpret_cast<void*>(get_virtual(interfaces::clientmode, 35));
	auto do_post_screen_effects_target = reinterpret_cast<void*>(get_virtual(interfaces::clientmode, 44));
	auto draw_model_execute_target = reinterpret_cast<void*>(get_virtual(interfaces::model_render, 21));
	auto list_leaves_in_box_target = reinterpret_cast<void*>(get_virtual(interfaces::engine->get_bsp_query(), 6));
	auto check_file_crcserver_target = reinterpret_cast<void*>(util::pattern_scan(xorstr("engine.dll"), xorstr("55 8B EC 81 EC ? ? ? ? 53 8B D9 89 5D F8 80")));
	auto loose_file_allowed_target = reinterpret_cast<void*>(get_virtual(interfaces::file_system, 128));
	auto alloc_key_values_target = reinterpret_cast<void*>(get_virtual(interfaces::key_values_system, 2));
	auto modify_eye_position_target = reinterpret_cast<void*>(util::pattern_scan(xorstr("client.dll"), xorstr("55 8B EC 83 E4 F8 83 EC 70 56 57 8B F9 89 7C 24 14 83 7F 60")));
	auto override_config_target = reinterpret_cast<void*>(get_virtual(interfaces::material_system, 21));
	auto is_depth_of_field_target = reinterpret_cast<void*>(util::pattern_scan(xorstr("client.dll"), xorstr("8B 0D ? ? ? ? 56 8B 01 FF 50 ? 8B F0 85 F6 75 ?")));
	auto set_visuals_data_target = reinterpret_cast<void*>(util::pattern_scan(xorstr("client.dll"), xorstr("55 8B EC 81 EC ? ? ? ? 53 8B D9 56 57 8B 53 5C")));
	auto particle_collection_simulate_target = reinterpret_cast<void*>(util::pattern_scan(xorstr("client.dll"), xorstr("55 8B EC 83 E4 F8 83 EC 30 56 57 8B F9 0F")));

	if (MH_Initialize() != MH_OK)
		throw std::runtime_error(xorstr("failed to initialize minhook"));

	if (MH_CreateHook(create_move_target, &create_move::run, reinterpret_cast<void**>(&create_move_original)) != MH_OK)
		throw std::runtime_error(xorstr("failed to initialize create_move hook"));

	if (MH_CreateHook(paint_traverse_target, &paint_traverse::run, reinterpret_cast<void**>(&paint_traverse_original)) != MH_OK)
		throw std::runtime_error(xorstr("failed to initialize paint_traverse hook"));

	if (MH_CreateHook(present_target, &present::run, reinterpret_cast<void**>(&present_original)) != MH_OK)
		throw std::runtime_error(xorstr("failed to initialize present hook"));

	if (MH_CreateHook(reset_target, &reset::run, reinterpret_cast<void**>(&reset_original)) != MH_OK)
		throw std::runtime_error(xorstr("failed to initialize reset hook"));

	if (MH_CreateHook(emit_sound_target, &emit_sound::run, reinterpret_cast<void**>(&emit_sound_original)) != MH_OK)
		throw std::runtime_error(xorstr("failed to initialize emit_sound_target hook"));

	if (MH_CreateHook(onscreen_sizechanged_target, &onscreen_sizechanged::run, reinterpret_cast<void**>(&onscreen_sizechanged_original)) != MH_OK)
		throw std::runtime_error(xorstr("failed to initialize onscreen_sizechanged hook"));

	if (MH_CreateHook(is_connected_target, &is_connected::run, reinterpret_cast<void**>(&is_connected_original)) != MH_OK)
		throw std::runtime_error(xorstr("failed to initialize is_connected hook"));

	if (MH_CreateHook(override_mouse_input_target, &override_mouse_input::run, reinterpret_cast<void**>(&override_mouse_input_original)) != MH_OK)
		throw std::runtime_error(xorstr("failed to initialize override_mouse_input hook"));

	if (MH_CreateHook(get_color_modulation_target, &get_color_modulation::run, reinterpret_cast<void**>(&get_color_modulation_original)) != MH_OK)
		throw std::runtime_error(xorstr("failed to initialize get_color_modulation hook"));

	if (MH_CreateHook(frame_stage_notify_target, &frame_stage_notify::run, reinterpret_cast<void**>(&frame_stage_notify_original)) != MH_OK)
		throw std::runtime_error(xorstr("failed to initialize frame_stage_notify_target hook"));

	if (MH_CreateHook(override_view_target, &override_view::run, reinterpret_cast<void**>(&override_view_original)) != MH_OK)
		throw std::runtime_error(xorstr("failed to initialize override_view hook"));

	if (MH_CreateHook(aspect_ratio_target, &aspect_ratio::run, reinterpret_cast<void**>(&aspect_ratio_original)) != MH_OK)
		throw std::runtime_error(xorstr("failed to initialize aspect_ratio hook"));

	if (MH_CreateHook(viewmodel_fov_target, &viewmodel_fov::run, reinterpret_cast<void**>(&viewmodel_fov_original)) != MH_OK)
		throw std::runtime_error(xorstr("failed to initialize viewmodel_fov hook"));

	if (MH_CreateHook(do_post_screen_effects_target, &do_post_screen_effects::run, reinterpret_cast<void**>(&do_post_screen_effects_original)) != MH_OK)
		throw std::runtime_error(xorstr("failed to initialize do_post_screen_effects hook"));

	if (MH_CreateHook(draw_model_execute_target, &draw_model_execute::run, reinterpret_cast<void**>(&draw_model_execute_original)) != MH_OK)
		throw std::runtime_error(xorstr("failed to initialize draw_model_execute_target hook"));

	if (MH_CreateHook(list_leaves_in_box_target, &list_leaves_in_box::run, reinterpret_cast<void**>(&list_leaves_in_box_original)) != MH_OK)
		throw std::runtime_error(xorstr("failed to initialize list_leaves_in_box hook"));

	if (MH_CreateHook(check_file_crcserver_target, &check_file_crcserver::run, reinterpret_cast<void**>(&check_file_crcserver_original)) != MH_OK)
		throw std::runtime_error(xorstr("failed to initialize check_file_crcserver hook"));

	if (MH_CreateHook(loose_file_allowed_target, &loose_file_allowed::run, reinterpret_cast<void**>(&loose_file_allowed_original)) != MH_OK)
		throw std::runtime_error(xorstr("failed to initialize loose_file_allowed hook"));

	if (MH_CreateHook(alloc_key_values_target, &alloc_key_values::run, reinterpret_cast<void**>(&alloc_key_values_original)) != MH_OK)
		throw std::runtime_error(xorstr("failed to initialize alloc_key_values hook"));

	if (MH_CreateHook(modify_eye_position_target, &modify_eye_position::run, reinterpret_cast<void**>(&modify_eye_position_original)) != MH_OK)
		throw std::runtime_error(xorstr("failed to initialize modify_eye_position hook"));

	if (MH_CreateHook(is_depth_of_field_target, &is_depth_of_field::run, reinterpret_cast<void**>(&is_depth_of_field_original)) != MH_OK)
		throw std::runtime_error(xorstr("failed to initialize is_depth_of_field hook"));

	if (MH_CreateHook(set_visuals_data_target, &set_visuals_data::run, reinterpret_cast<void**>(&set_visuals_data_original)) != MH_OK)
		throw std::runtime_error(xorstr("failed to initialize set_visuals_data hook"));

	if (MH_CreateHook(particle_collection_simulate_target, &particle_collection_simulate::run, reinterpret_cast<void**>(&particle_collection_simulate_original)) != MH_OK)
		throw std::runtime_error(xorstr("failed to initialize particle_collection_simulate hook"));

	//if (MH_CreateHook(override_config_target, &override_config::run, reinterpret_cast<void**>(&override_config_original)) != MH_OK)
		//throw std::runtime_error(xorstr("failed to initialize override_config hook"));

	if (MH_EnableHook(MH_ALL_HOOKS) != MH_OK)
		throw std::runtime_error(xorstr("failed to enable hooks"));

	console::log(xorstr("hooks initialized\n"));
	return true;
}

void hooks::release() {
	MH_Uninitialize();
	MH_DisableHook(MH_ALL_HOOKS);
	menu::release();
}

bool __stdcall hooks::create_move::run(float input_sample_frametime, c_usercmd* cmd) {
	create_move_original(input_sample_frametime, cmd);

	if (!cmd || !cmd->command_number) return true;

	// we should really get the local player instance from frameStageNotify but hey ho this also works.
	csgo::local_player = static_cast<player_t*>(interfaces::entity_list->get_client_entity(interfaces::engine->get_local_player()));
	csgo::global_cmd = cmd;

	auto net_channel = interfaces::clientstate->net_channel;
	auto old_viewangles = cmd->viewangles;
	auto old_forwardmove = cmd->forwardmove;
	auto old_sidemove = cmd->sidemove;

	if (var::misc::autoweapon) features::misc::auto_weapon(cmd);
	if (var::misc::rank_reveal) features::misc::rank_reveal(cmd);
	if (var::misc::doorspammer::enabled) features::misc::door_spammer(cmd);
	if (var::movement::bunnyhop::enabled) features::movement::bunnyhop(cmd);
	if (var::movement::staminahop::enabled) features::movement::staminahop(cmd);
	if (var::movement::fastduck) features::movement::fast_duck(cmd);
	if (var::movement::slidewalk) features::movement::slide_walk(cmd);
	if (var::movement::checkpoint::enabled) features::movement::checkpoint();
	if (var::movement::autoalign) features::movement::autoalign(cmd);
	features::misc::clantag();

	int pre_flags = csgo::local_player->flags();

	prediction::start(cmd);
	{
		if (var::legit::aimbot::enabled) features::legit::aimbot::run(cmd);
		if (var::legit::triggerbot::enabled) features::legit::triggerbot::run(cmd);
		if (var::legit::backtrack::enabled) features::legit::backtrack::run(cmd);
	} 
	prediction::end();

	if (var::movement::edgebug::enabled) features::movement::edgebug::run(cmd);
	if (var::movement::pixelsurf::enabled) features::movement::pixelsurf::run(cmd);
	if (var::movement::fakebackwards::enabled) features::movement::fakebackwards(cmd);

	math::correct_movement(old_viewangles, cmd, old_forwardmove, old_sidemove);

	if (var::movement::edgebug::enabled) features::movement::edgebug::lock(cmd);
	if (var::movement::pixelsurf::enabled) features::movement::pixelsurf::lock(cmd);
	if (var::movement::jumpbug::enabled) features::movement::jumpbug(cmd, pre_flags);
	if (var::movement::edgejump::enabled) features::movement::edgejump(cmd, pre_flags);
	if (var::movement::minijump::enabled) features::movement::minijump(cmd, pre_flags);
	if (var::movement::longjump::enabled) features::movement::longjump(cmd);
	if (var::movement::ladderglide::enabled) features::movement::ladderglide(cmd);
	if (var::movement::faststop) features::movement::fast_stop(cmd);
	if (var::movement::blockbot::enabled) features::movement::blockbot(cmd);

	cmd->forwardmove = std::clamp(cmd->forwardmove, -450.0f, 450.0f);
	cmd->sidemove = std::clamp(cmd->sidemove, -450.0f, 450.0f);
	cmd->upmove = std::clamp(cmd->upmove, -320.0f, 320.0f);

	cmd->viewangles.normalize();
	cmd->viewangles.x = std::clamp(cmd->viewangles.x, -89.0f, 89.0f);
	cmd->viewangles.y = std::clamp(cmd->viewangles.y, -180.0f, 180.0f);
	cmd->viewangles.z = 0.0f;

	return false;
}

void __stdcall hooks::paint_traverse::run(unsigned int panel, bool force_repaint, bool allow_force) {
	auto panel_to_draw = fnv::hash(interfaces::panel->get_panel_name(panel));

	if (var::visuals::remove_scope::enabled && strstr(interfaces::panel->get_panel_name(panel), xorstr("HudZoom"))) return;

	switch (panel_to_draw) {
		case fnv::hash("MatSystemTopPanel"):
			features::visuals::esp::run();
			if (var::visuals::watermark) features::visuals::watermark();
			if (var::visuals::local_dlight::enabled) features::visuals::local_dlight();
			if (var::visuals::indicators::enabled) features::visuals::indicators();
			if (var::visuals::snipercrosshair::enabled) features::visuals::sniper_crosshair();
			if (var::visuals::recoilcrosshair::enabled) features::visuals::recoil_crosshair();
			if (var::visuals::remove_scope::enabled) features::visuals::remove_scope();
			if (var::misc::detection_indicator::enabled) {
				features::movement::edgebug::draw();
				features::movement::pixelsurf::draw();
			}
			break;

		case fnv::hash("FocusOverlayPanel"):
			interfaces::panel->set_mouse_input_enabled(panel, menu::opened);
			break;
	}
	paint_traverse_original(interfaces::panel, panel, force_repaint, allow_force);
}

long __stdcall hooks::present::run(IDirect3DDevice9* device, RECT* source_rect, RECT* dest_rect, HWND dest_window_override, RGNDATA* dirty_region) {
	if (!menu::initialized) menu::initialize(device);

	device->SetRenderState(D3DRS_COLORWRITEENABLE, D3DCOLORWRITEENABLE_RED | D3DCOLORWRITEENABLE_GREEN | D3DCOLORWRITEENABLE_BLUE);
	IDirect3DVertexDeclaration9* vertexDeclaration;
	device->GetVertexDeclaration(&vertexDeclaration);

	ImGui_ImplDX9_NewFrame();
	ImGui_ImplWin32_NewFrame();
	gui::NewFrame();

	if (menu::opened) menu::render();
	if (var::visuals::speclist) features::visuals::speclist();

	gui::EndFrame();
	gui::Render();
	ImGui_ImplDX9_RenderDrawData(gui::GetDrawData());

	device->SetVertexDeclaration(vertexDeclaration);
	vertexDeclaration->Release();

	return present_original(device, source_rect, dest_rect, dest_window_override, dirty_region);
}

long __stdcall hooks::reset::run(IDirect3DDevice9* device, D3DPRESENT_PARAMETERS* params) {
	ImGui_ImplDX9_InvalidateDeviceObjects();
	ImGui_ImplDX9_CreateDeviceObjects();
	return reset_original(interfaces::directx, device, params);
}

void __stdcall hooks::emit_sound::run(void* filter, int index, int ichannel, const char* soundentry, unsigned int soundhash, const char* sample, float flvolume, int seed, float flattenuation, int iflags, int ipitch, const vec3_t* origin, const vec3_t* direction, void* utlvecorigins, bool updatepositions, float soundtime, int speakerentity, int unk) {
	if (!strcmp(soundentry, xorstr("UIPanorama.popup_accept_match_beep")) && var::misc::autoaccept) {
		static auto accept = reinterpret_cast<bool(__stdcall*)(const char*)>(util::pattern_scan(xorstr("client.dll"), xorstr("55 8B EC 83 E4 F8 8B 4D 08 BA ? ? ? ? E8 ? ? ? ? 85 C0 75 12")));
		if (accept) accept(xorstr(""));
	}
	// Fix prediction sound
	if (!prediction::in_prediction()) return emit_sound_original(interfaces::engine_sound, filter, index, ichannel, soundentry, soundhash, sample, flvolume, seed, flattenuation, iflags, ipitch, origin, direction, utlvecorigins, updatepositions, soundtime, speakerentity, unk);
}

// Fix fonts when changing resolution
void __fastcall hooks::onscreen_sizechanged::run(void* thisptr, int edx, int oldwidth, int oldheight) {
	onscreen_sizechanged_original(thisptr, oldwidth, oldheight);

	render::initialize();
}

// Allows access to inventory in game
bool __stdcall hooks::is_connected::run() {
	static void* force_inventory_open = util::pattern_scan(xorstr("client.dll"), xorstr("84 C0 75 05 B0 01 5F")) - 2;

	if (var::misc::unlock_inventory && _ReturnAddress() == force_inventory_open) {
		return false;
	}
	return is_connected_original(interfaces::engine);
}

// Override mouse
void __fastcall hooks::override_mouse_input::run(void* thisptr, int edx, float* x, float* y) {
	if (features::movement::edgebug::is_detected() || features::movement::pixelsurf::is_detected()) {
		*x *= var::movement::lock_factor;
		*y *= var::movement::lock_factor;
	}

	if (features::legit::aimbot::has_target && var::legit::aimbot::aimlock)
		*x = 0.f, *y = 0;

	override_mouse_input_original(thisptr, edx, x, y);
}

// Nightmode
void __fastcall hooks::get_color_modulation::run(void* ecx, void* edx, float* r, float* g, float* b) {
	get_color_modulation_original(ecx, r, g, b);

	auto material = reinterpret_cast<i_material*>(ecx);
	if (!var::visuals::nightmode::enabled || (!material || material->is_error_material()))
		return get_color_modulation_original(ecx, r, g, b);

	auto group = fnv::hash(material->get_texture_group_name());
	if (group != fnv::hash("World textures") && (group != fnv::hash("SkyBox textures")))
		return get_color_modulation_original(ecx, r, g, b);

	bool is_sky = group == fnv::hash("SkyBox textures");
	float brightness = var::visuals::nightmode::brightness / 100.f;
	*r *= is_sky ? var::visuals::nightmode::color[0] : brightness;
	*g *= is_sky ? var::visuals::nightmode::color[1] : brightness;
	*b *= is_sky ? var::visuals::nightmode::color[2] : brightness;
}

void __stdcall hooks::frame_stage_notify::run(int stage) {
	// Backtrack cvars
	static auto backtrack_init = (features::legit::backtrack::initialize(), false);

	if (stage == FRAME_RENDER_START) {
		if (var::legit::backtrack::enabled) features::legit::backtrack::update();
		if (var::visuals::trail::enabled) features::visuals::trail();
		features::visuals::wireframe_smoke();
		features::visuals::disable_postprocess();
		features::visuals::skybox();
	}
	else if (stage == FRAME_NET_UPDATE_POSTDATAUPDATE_START) {
		features::misc::knife();
		features::misc::glove();
	}
	return frame_stage_notify_original(interfaces::client, stage);
}

// Fov
void __stdcall hooks::override_view::run(view_setup_t* setup) {
	if (setup && interfaces::engine->is_in_game() && csgo::local_player) {
		if (!csgo::local_player->is_scoped()) {
			if (var::visuals::view::fov != 90) {
				setup->fov = var::visuals::view::fov;
			}

			// Roll
			auto viewmodel = reinterpret_cast<player_t*>(interfaces::entity_list->get_client_entity_handle(csgo::local_player->view_model()));
			auto angle = setup->angles;
			if (viewmodel) {
				if (var::visuals::view::angle != 0) {
					angle.z -= var::visuals::view::angle;
					viewmodel->set_angles(angle);
				}
			}
		}
		//interfaces::input->camera_in_third_person = util::bind(var::visuals::thirdperson::keybind, var::visuals::thirdperson::kb_style);
		//interfaces::input->camera_offset.z = var::visuals::thirdperson::distance;
	}
	if (var::visuals::motionblur::enabled) features::visuals::motionblur_render(setup);
	override_view_original(interfaces::clientmode, setup);
}

// Aspect ratio
float __fastcall hooks::aspect_ratio::run(void* ecx, void* edx, int32_t width, int32_t height) {
	if (interfaces::engine->is_in_game() && csgo::local_player && var::visuals::view::aspect != 0.0f) {
		return var::visuals::view::aspect;
	}
	aspect_ratio_original(ecx, edx, width, height);
}

// Viewmodel
float __stdcall hooks::viewmodel_fov::run() {
	if (interfaces::engine->is_in_game() && csgo::local_player && var::visuals::view::model != 60) {
		return var::visuals::view::model;
	}
	return viewmodel_fov_original();
}

bool __stdcall hooks::do_post_screen_effects::run(view_setup_t* setup) {
	if (var::visuals::glow::enabled) features::visuals::glow::run();
	features::visuals::flash_opacity();

	return do_post_screen_effects_original(interfaces::clientmode, setup);
}

void __fastcall hooks::draw_model_execute::run(void* thisptr, int edx, i_mat_render_context* ctx, const draw_model_state_t& state, const model_render_info_t& info, matrix_t* matrix) {
	static auto chams_init = (features::visuals::chams::initialize(), false);

	// Fixes arms and weapon chams drawing over eachother
	if (interfaces::studio_render->isforced_materialoverride() && !strstr(info.model->name, xorstr("arms")) && !strstr(info.model->name, xorstr("weapons/v_"))) {
		return draw_model_execute_original(thisptr, edx, ctx, state, info, matrix);
	}

	// Remove sleeves
	if (var::visuals::chams::arms::remove_sleeves && strstr(info.model->name, xorstr("sleeve"))) return;

	// Execute Chams Here
	if (var::visuals::chams::enabled) features::visuals::chams::run(thisptr, edx, ctx, state, info, matrix, draw_model_execute_original);

	draw_model_execute_original(thisptr, edx, ctx, state, info, matrix);
	interfaces::model_render->override_material(nullptr);
}

// Allows chams to render farther
#define MAX_COORD_FLOAT ( 16384.0f )
#define MIN_COORD_FLOAT ( -MAX_COORD_FLOAT )
int __fastcall hooks::list_leaves_in_box::run(void* bsp, void* edx, const vec3_t& mins, const vec3_t& maxs, unsigned short* list, int list_max) {
	static auto list_leaves = util::pattern_scan(xorstr("client.dll"), xorstr("56 52 FF 50 18")) + 5;
	auto info = *reinterpret_cast<renderable_info_t**>(reinterpret_cast<uintptr_t>(_AddressOfReturnAddress()) + 0x14);

	if (!var::visuals::chams::model_occlusion || (_ReturnAddress()) != list_leaves)
		return list_leaves_in_box_original(bsp, mins, maxs, list, list_max);

	if (!info || !info->renderable)
		return list_leaves_in_box_original(bsp, mins, maxs, list, list_max);

	auto entity = util::call_virtual_new<entity_t*>(info->renderable - 4, 7);

	if (!entity || entity->client_class()->class_id != class_ids::ccsplayer)
		return list_leaves_in_box_original(bsp, mins, maxs, list, list_max);

	info->flags &= ~0x100;
	info->flags2 |= 0x40;

	static vec3_t map_min = vec3_t(MIN_COORD_FLOAT, MIN_COORD_FLOAT, MIN_COORD_FLOAT);
	static vec3_t map_max = vec3_t(MAX_COORD_FLOAT, MAX_COORD_FLOAT, MAX_COORD_FLOAT);
	return list_leaves_in_box_original(bsp, map_min, map_max, list, list_max);
}

// Bypass sv_pure
void __fastcall hooks::check_file_crcserver::run(void*, void*) {
	return;
}
bool __fastcall hooks::loose_file_allowed::run(void*, void*) {
	return true;
}

void* __stdcall hooks::alloc_key_values::run(const std::int32_t size) {
	if (const std::uint32_t address = reinterpret_cast<std::uint32_t>(_ReturnAddress());
		address == reinterpret_cast<std::uint32_t>(interfaces::key_values_engine) ||
		address == reinterpret_cast<std::uint32_t>(interfaces::key_values_client))
		return nullptr;

	return alloc_key_values_original(interfaces::key_values_system, size);
}

// Fix landing anim
void __fastcall hooks::modify_eye_position::run(LPVOID ecx, uint32_t, vec3_t& inputeyeposition) {
	return;
}

bool __fastcall hooks::override_config::run(void* ecx, void* edx, material_system_config_t* config, bool update) {
	if (var::visuals::fullbright) config->full_bright = true;

	return override_config_original(ecx, edx, config, update);
}

// Motion blur
bool __stdcall hooks::is_depth_of_field::run() {
	if (var::visuals::motionblur::enabled) features::visuals::motionblur_run();
	return false;
}

void __fastcall hooks::set_visuals_data::run(void* ecx, void* edx, const char* shader_name) {
	set_visuals_data_original(ecx, edx, shader_name);
	auto visuals_data = reinterpret_cast<weapon_visuals_data_t*>((uintptr_t(ecx) - 0x4));
	std::string buffer;

	if (!visuals_data)
		return;

	if (!var::misc::knife::custom_color || var::misc::knife::model == 0)
		return;

	for (int i = 0; i <= 260; i++)
		buffer.append(&visuals_data->weapon_path[i]);

	if (!strstr(buffer.c_str(), xorstr("knife")))
		return;

	visuals_data->color1_r = var::misc::knife::color1[0] * 255;
	visuals_data->color1_g = var::misc::knife::color1[1] * 255;
	visuals_data->color1_b = var::misc::knife::color1[2] * 255;

	visuals_data->color2_r = var::misc::knife::color2[0] * 255;
	visuals_data->color2_g = var::misc::knife::color2[1] * 255;
	visuals_data->color2_b = var::misc::knife::color2[2] * 255;

	visuals_data->color3_r = var::misc::knife::color3[0] * 255;
	visuals_data->color3_g = var::misc::knife::color3[1] * 255;
	visuals_data->color3_b = var::misc::knife::color3[2] * 255;

	visuals_data->color4_r = var::misc::knife::color4[0] * 255;
	visuals_data->color4_g = var::misc::knife::color4[1] * 255;
	visuals_data->color4_b = var::misc::knife::color4[2] * 255;
}

void __fastcall hooks::particle_collection_simulate::run(particle_collection* this_ptr, void* edx) {
	particle_collection_simulate_original(this_ptr);

	particle_collection* root_colection = this_ptr;
	while (root_colection->parent)
		root_colection = root_colection->parent;

	const char* root_name = root_colection->definition.object->name.buffer;
	if (var::visuals::particles::enabled) {
		switch (fnv::hash(root_name)) {
		case fnv::hash("molotov_groundfire"):
		case fnv::hash("molotov_groundfire_00MEDIUM"):
		case fnv::hash("molotov_groundfire_00HIGH"):
		case fnv::hash("molotov_groundfire_fallback"):
		case fnv::hash("molotov_groundfire_fallback2"):
		case fnv::hash("molotov_explosion"):
		case fnv::hash("explosion_molotov_air"):
		case fnv::hash("extinguish_fire"):
		case fnv::hash("weapon_molotov_held"):
		case fnv::hash("weapon_molotov_fp"):
		case fnv::hash("weapon_molotov_thrown"):
		case fnv::hash("incgrenade_thrown_trail"):
			for (int i = 0; i < this_ptr->active_particle; i++) {
				float* color = this_ptr->particle_attribute.float_attribute_pointer(PARTICLE_ATTRIBUTE_TINT_RGB, i);
				color[0] = var::visuals::particles::color[0];
				color[4] = var::visuals::particles::color[1];
				color[8] = var::visuals::particles::color[2];
			}
			break;
		case fnv::hash("explosion_smokegrenade"):
		case fnv::hash("explosion_smokegrenade_fallback"):
			for (int i = 0; i < this_ptr->active_particle; i++) {
				float* color = this_ptr->particle_attribute.float_attribute_pointer(PARTICLE_ATTRIBUTE_TINT_RGB, i);
				color[0] = var::visuals::particles::color2[0];
				color[4] = var::visuals::particles::color2[1];
				color[8] = var::visuals::particles::color2[2];
				float* alpha = this_ptr->particle_attribute.float_attribute_pointer(PARTICLE_ATTRIBUTE_ALPHA, i);
				*alpha = var::visuals::particles::color2[3];
			}
			break;
		}
	}
}
