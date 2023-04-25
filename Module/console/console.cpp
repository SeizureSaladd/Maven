#include "console.hpp"

console::console(std::string_view title) {
    AllocConsole();
    SetConsoleTitleA(title.data());

    freopen_s(&file_stream, "CONIN$", "r", stdin);
    freopen_s(&file_stream, "CONOUT$", "w", stdout);
    freopen_s(&file_stream, "CONOUT$", "w", stderr);

    std::printf("%s\n\n", ascii_title);
}

console::~console() {
    FreeConsole();
}