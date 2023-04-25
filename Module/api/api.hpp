#pragma once

#include <iostream>

#include "../addresses.hpp"

inline auto print(std::uint8_t type, const char* content) {
	return reinterpret_cast<int(__cdecl*)(std::uint8_t, const char*)>(addresses::print)(type, content);
}

inline auto get_scheduler() {
	return reinterpret_cast<int(__cdecl*)()>(addresses::scheduler)();
}

inline auto task_defer(int lua_state) {
	return reinterpret_cast<std::uintptr_t(__cdecl*)(int)>(addresses::task_defer)(lua_state);
}

inline auto luavm_load(int lua_state, std::string* source, const char* chunk, int environment) {
	return reinterpret_cast<std::uintptr_t(__fastcall*)(int,
		std::string*, const char*, int)>(addresses::luavm_load)(lua_state,
		source, chunk, environment);
}

inline auto get_lua_state(int script_context) {
	return ((script_context + 244) ^ *reinterpret_cast<std::uintptr_t*>(script_context + 244));
}

inline auto r_decrement_top(int lua_state) {
	*reinterpret_cast<std::uintptr_t*>(lua_state + offsets::lua_state::top) -= 16;
}