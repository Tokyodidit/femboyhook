#include <pch.h>
#include "features/features.hpp"

/*  
	Copyright (c) 2022 femboyhook.xyz

	credits gilbert and nate for the help <3 
	shoutout the dumb dog venom for the $$$ 

	boy what the hell! you ever just wanna die? same...
	why would breezetix fart on his sister!?
	all my homies hate aiden and patoke
	shoutout the slime nightmare
	god i hate faggots
*/

unsigned long WINAPI initialize(void* instance) {
	while (!GetModuleHandleA(xorstr("serverbrowser.dll"))) Sleep(200);

	// Show debug console
	#ifdef _DEBUG
	console::initialize(xorstr("fbh console"));
	#endif

	// Initialize
	try {
		interfaces::initialize();
		hooks::initialize();
		event_listener.initialize();
		render::initialize();
		kit_parser.initialize();
		features::misc::animation_hook();
		features::discord::initialize();
		notify::run(xorstr("initialized - csgo build: ") + std::to_string(interfaces::engine->get_engine_build_number()), true, false);
	}
	catch (const std::runtime_error& error) {
		FreeLibraryAndExitThread(static_cast<HMODULE>(instance), EXIT_FAILURE);
	}

	// Unload cheat
	while (!var::unload::enabled)
		std::this_thread::sleep_for(std::chrono::milliseconds(50));

	notify::run(xorstr("unloading"), true, false);
	menu::opened = false;
	features::discord::release();

	// Wait for everything to fully unload
	std::this_thread::sleep_for(std::chrono::milliseconds(50));

	FreeLibraryAndExitThread(static_cast<HMODULE>(instance), EXIT_SUCCESS);
}

unsigned long WINAPI release() {
	hooks::release();
	event_listener.release();
	features::misc::animation_unhook();

	#ifdef _DEBUG
	console::release();
	#endif
	return TRUE;
}

std::int32_t WINAPI DllMain(const HMODULE instance [[maybe_unused]], const unsigned long reason, const void* reserved [[maybe_unused]] ) {
	DisableThreadLibraryCalls(instance);
	switch (reason) {
		case DLL_PROCESS_ATTACH: {
			if (auto handle = CreateThread(nullptr, NULL, initialize, instance, NULL, nullptr))
				CloseHandle(handle);
			break;
		}
		case DLL_PROCESS_DETACH: {
			release();
			break;
		}
	}
	return true;
}
