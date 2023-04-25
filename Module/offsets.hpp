#pragma once

#include <iostream>

namespace offsets {
	namespace lua_state {
		const auto top{ 20 };
	}

	namespace scheduler {
		const auto start{ 308 };
		const auto end{ 312 };
		const auto context{ 304 };
		const auto lua_state{ 308 };
	}
}