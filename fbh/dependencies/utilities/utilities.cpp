#include <pch.h>
#include "utilities.hpp"
#include "../utilities/csgo.hpp"

std::uint8_t* util::pattern_scan(const char* module_name, const char* signature) {
	const auto module_handle = GetModuleHandleA(module_name);

	if (!module_handle)
		return nullptr;

	static auto pattern_to_byte = [](const char* pattern) {
		auto bytes = std::vector<int>{};
		auto start = const_cast<char*>(pattern);
		auto end = const_cast<char*>(pattern) + std::strlen(pattern);

		for (auto current = start; current < end; ++current) {
			if (*current == '?') {
				++current;

				if (*current == '?')
					++current;

				bytes.push_back(-1);
			} else {
				bytes.push_back(std::strtoul(current, &current, 16));
			}
		}
		return bytes;
	};

	auto dos_header = reinterpret_cast<PIMAGE_DOS_HEADER>(module_handle);
	auto nt_headers =
		reinterpret_cast<PIMAGE_NT_HEADERS>(reinterpret_cast<std::uint8_t*>(module_handle) + dos_header->e_lfanew);

	auto size_of_image = nt_headers->OptionalHeader.SizeOfImage;
	auto pattern_bytes = pattern_to_byte(signature);
	auto scan_bytes = reinterpret_cast<std::uint8_t*>(module_handle);

	auto s = pattern_bytes.size();
	auto d = pattern_bytes.data();

	for (auto i = 0ul; i < size_of_image - s; ++i) {
		bool found = true;

		for (auto j = 0ul; j < s; ++j) {
			if (scan_bytes[i + j] != d[j] && d[j] != -1) {
				found = false;
				break;
			}
		}
		if (found)
			return &scan_bytes[i];
	}

	throw std::runtime_error(std::string(xorstr("Wrong signature: ")) + signature);
}

void util::load_skybox(const char* sky_name) {
	using Fn = void(__fastcall*)(const char*);
	static auto load_named_sky_fn = reinterpret_cast<Fn>(util::pattern_scan(xorstr("engine.dll"), xorstr("55 8B EC 81 EC ? ? ? ? 56 57 8B F9 C7 45")));
	load_named_sky_fn(sky_name);
}

void util::set_clantag(const char* name) {
	using Fn = int(__fastcall*)(const char*, const char*);
	static auto apply_clan_tag_fn = reinterpret_cast<Fn>(util::pattern_scan(xorstr("engine.dll"), xorstr("53 56 57 8B DA 8B F9 FF 15")));
	apply_clan_tag_fn(name, name);
}

bool util::bind(int key, int style) {
	switch (style) {
		case 1: return true; break;
		case 2: return GetAsyncKeyState(key); break;
		case 3: return GetKeyState(key); break;
		case 4: return !GetAsyncKeyState(key); break;
	}
}
