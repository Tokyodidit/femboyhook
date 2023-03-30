#include <pch.h>
#include "interfaces.hpp"
#include "../utilities/csgo.hpp"

bool interfaces::initialize() {
	client = get_interface<i_base_client_dll, interface_type::index>(xorstr("client.dll"), xorstr("VClient018"));
	entity_list = get_interface<i_client_entity_list, interface_type::index>(xorstr("client.dll"), xorstr("VClientEntityList003"));
	engine = get_interface<iv_engine_client, interface_type::index>(xorstr("engine.dll"), xorstr("VEngineClient014"));
	engine_sound = get_interface<i_engine_sound, interface_type::index>(xorstr("engine.dll"), xorstr("IEngineSoundClient003"));
	panel = get_interface<i_panel, interface_type::index>(xorstr("vgui2.dll"), xorstr("VGUI_Panel009"));
	surface = get_interface<i_surface, interface_type::index>(xorstr("vguimatsurface.dll"), xorstr("VGUI_Surface031"));
	material_system = get_interface<i_material_system, interface_type::index>(xorstr("materialsystem.dll"), xorstr("VMaterialSystem080"));
	model_info = get_interface<iv_model_info, interface_type::index>(xorstr("engine.dll"), xorstr("VModelInfoClient004"));
	model_render = get_interface<iv_model_render, interface_type::index>(xorstr("engine.dll"), xorstr("VEngineModel016"));
	render_view = get_interface<i_render_view, interface_type::index>(xorstr("engine.dll"), xorstr("VEngineRenderView014"));
	console = get_interface<i_console, interface_type::index>(xorstr("vstdlib.dll"), xorstr("VEngineCvar007"));
	localize = get_interface<i_localize, interface_type::index>(xorstr("localize.dll"), xorstr("Localize_001"));
	event_manager = get_interface<i_game_event_manager2, interface_type::index>(xorstr("engine.dll"), xorstr("GAMEEVENTSMANAGER002"));
	debug_overlay = get_interface<iv_debug_overlay, interface_type::index>(xorstr("engine.dll"), xorstr("VDebugOverlay004"));
	inputsystem = get_interface<i_inputsytem, interface_type::index>(xorstr("inputsystem.dll"), xorstr("InputSystemVersion001"));
	trace_ray = get_interface<trace, interface_type::index>(xorstr("engine.dll"), xorstr("EngineTraceClient004"));
	game_movement = get_interface<player_game_movement, interface_type::index>(xorstr("client.dll"), xorstr("GameMovement001"));
	prediction = get_interface<player_prediction, interface_type::index>(xorstr("client.dll"), xorstr("VClientPrediction001"));
	file_system = get_interface<i_file_system, interface_type::index>(xorstr("filesystem_stdio.dll"), xorstr("VFileSystem017"));
	effects = get_interface<iv_effects, interface_type::index>(xorstr("engine.dll"), xorstr("VEngineEffects001"));
	local_effects = get_interface<i_effects, interface_type::index>(xorstr("client.dll"), xorstr("IEffects001"));
	studio_render = get_interface<iv_studio_render, interface_type::index>(xorstr("studiorender.dll"), xorstr("VStudioRender026"));
	surface_props_physics = get_interface<physics_surface_props, interface_type::index>(xorstr("vphysics.dll"), xorstr("VPhysicsSurfaceProps001"));

	// Custom interfaces 
	clientmode = **reinterpret_cast<i_client_mode***>((*reinterpret_cast<uintptr_t**>(client))[10] + 5);
	globals = **reinterpret_cast<c_global_vars_base***>((*reinterpret_cast<uintptr_t**>(client))[11] + 10);
	clientstate = **reinterpret_cast<i_client_state***>(util::pattern_scan(xorstr("engine.dll"), xorstr("A1 ? ? ? ? 8B 80 ? ? ? ? C3")) + 1);
	directx = **reinterpret_cast<IDirect3DDevice9***>(util::pattern_scan(xorstr("shaderapidx9.dll"), xorstr("A1 ? ? ? ? 50 8B 08 FF 51 0C")) + 1);
	input = *reinterpret_cast<i_input**>(util::pattern_scan(xorstr("client.dll"), xorstr("B9 ? ? ? ? F3 0F 11 04 24 FF 50 10")) + 1);
	glow_manager = reinterpret_cast<glow_manager_t*>(*reinterpret_cast<uintptr_t*>(util::pattern_scan(xorstr("client.dll"), xorstr("0F 11 05 ? ? ? ? 83 C8 01")) + 3));
	move_helper = **reinterpret_cast<player_move_helper***>(util::pattern_scan(xorstr("client.dll"), xorstr("8B 0D ? ? ? ? 8B 46 08 68")) + 2);
	weapon_system = *reinterpret_cast<i_weapon_system**>(util::pattern_scan(xorstr("client.dll"), xorstr("8B 35 ? ? ? ? FF 10 0F B7 C0")) + 2);
	render_beams = *reinterpret_cast<i_view_render_beams**>((util::pattern_scan(xorstr("client.dll"), xorstr("B9 ? ? ? ? A1 ? ? ? ? FF 10 A1 ? ? ? ? B9")) + 1));
	chat_element = findhudelement<CHudChat>(xorstr("CHudChat"));

	if (const HINSTANCE handle = GetModuleHandle(xorstr("vstdlib.dll")))											
		key_values_system = reinterpret_cast<void* (__cdecl*)()>(GetProcAddress(handle, "KeyValuesSystem"))();	
	key_values_engine = util::pattern_scan(xorstr("engine.dll"), xorstr("85 C0 74 ? 51 6A ? 56 8B C8 E8 ? ? ? ? 8B F0"));
	key_values_client = util::pattern_scan(xorstr("client.dll"), xorstr("85 C0 74 ? 6A ? 6A ? 56 8B C8 E8 ? ? ? ? 8B F0"));
	
	console::log(xorstr("interfaces initialized\n"));
	return true;
}
