#pragma once

#include <iostream>
#include <Windows.h>

#include "offsets.hpp"

__forceinline std::uint32_t rebase(std::uint32_t address) {
	static std::uint32_t base = reinterpret_cast<std::uint32_t>(GetModuleHandleA(0));

	return ((base - 0x400000) + address);
}

/*
	Learn how to dump Roblox : https://www.youtube.com/watch?v=gscelOJrQ7k
	I am not going to provide you with updated addresses, you can get them yourself.
*/

namespace addresses {
	const std::uint32_t print{}; // Search for string "Video recording started", jump to xref and first call will be the address.
	const std::uint32_t scheduler{}; // Search for string "SchedulerRate", jump to xref and go into offset that is 2 instructions above - the first call will be the address.
	const std::uint32_t luavm_load{}; // Search for string "oldResult, moduleRef", jump to xref and second call will be the address.
	const std::uint32_t task_defer{}; // Error task.defer() and search for string that is threw.
}