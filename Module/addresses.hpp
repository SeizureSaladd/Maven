#pragma once

#include <iostream>
#include <Windows.h>

#include "offsets.hpp"

template <class func_prototype = std::uintptr_t>
inline auto aslr(std::uintptr_t address, std::uintptr_t old_base = 0x400000)
{
	static const auto new_base = reinterpret_cast<std::uintptr_t>(GetModuleHandleA(0));
	return func_prototype((address - old_base) + new_base);
}

/*
	Learn how to dump Roblox : https://www.youtube.com/watch?v=gscelOJrQ7k
	I am not going to provide you with updated addresses, you can get them yourself.
*/

namespace addresses {
	const auto print = aslr(0xDEADBEEF); // Search for string "Video recording started", jump to xref and first call will be the address.
	const auto scheduler = aslr(0xDEADBEEF); // Search for string "SchedulerRate", jump to xref and go into offset that is 2 instructions above - the first call will be the address.
	const auto luavm_load = aslr(0xDEADBEEF); // Search for string "oldResult, moduleRef", jump to xref and second call will be the address.
	const auto task_defer = aslr(0xDEADBEEF); // Error task.defer() and search for string that is threw.
}