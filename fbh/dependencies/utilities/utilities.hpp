#pragma once
#include <cstdint>
#include "../../source-sdk/math/vector3d.hpp"

namespace util {
	template< typename t >
	__forceinline static t call_virtual( void *name, int offset ) {
		int *table = *( int ** ) name;
		int address = table[ offset ];
		return ( t ) ( address );
	}
	template<typename T, typename ...Args>
	constexpr auto call_virtual_new(void* class_base, int index, Args... args) {
		return ((*reinterpret_cast<T(__thiscall***)(void*, Args...)>(class_base))[index])(class_base, args...);
	}

	std::uint8_t* pattern_scan(const char* module_name, const char* signature);
	void load_skybox(const char* sky_name);
	void set_clantag(const char* name);
	bool bind(int key, int style);
}
