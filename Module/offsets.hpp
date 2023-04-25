#pragma once

#include <iostream>

namespace offsets {
	namespace lua_state {
		const std::uint32_t top{ 20 };
	}

	namespace scheduler {
		const std::uint32_t start{ 308 };
		const std::uint32_t end{ 312 };
		const std::uint32_t context{ 304 };
		const std::uint32_t lua_state{ 308 };
	}
}