#include <iostream>
#include <Windows.h>
#include <string_view>

class console {
private:
    std::FILE* file_stream{};
    const char* ascii_title = R"(
  __  __                       
 |  \/  |                      
 | \  / | __ ___   _____ _ __  
 | |\/| |/ _` \ \ / / _ \ '_ \ 
 | |  | | (_| |\ V /  __/ | | |
 |_|  |_|\__,_| \_/ \___|_| |_|
)";
public:
    explicit console(std::string_view title);
    ~console();
};