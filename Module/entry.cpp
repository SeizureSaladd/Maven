#include <iostream>
#include <thread>
#include <Windows.h>

#include "console/console.hpp"
#include "api/api.hpp"
#include "scheduler/scheduler.hpp"
#include "execution/execution.hpp"

auto main_thread() {
    console console_window{ "Maven - Bytecode Compressor" };

    std::string script = R"(
        local Name = "Niko Bellic" -- Grand Theft Auto IV reference
        print(string.format(\"Hello, my name is %s\", Name))
    )";

    execution::execute_script(get_lua_state(scheduler::get_script_context()), script);

	std::cin.get();
}

int __stdcall DllMain(void*, std::uintptr_t reason, void*) {
    if (reason == DLL_PROCESS_ATTACH)
    {
        system("start https://www.youtube.com/watch?v=pHdoKZkde_4");
        std::thread{ main_thread }.detach();
    }

	return 1;
}