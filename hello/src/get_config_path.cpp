#include "hello.h"
#include "cfgpath.h"

static const auto INITIAL_BUFFER_SIZE = 512;


std::filesystem::path get_config_path()
{
    auto buffer = std::make_unique<char>(INITIAL_BUFFER_SIZE);
    *buffer = 0;
    for (auto size = INITIAL_BUFFER_SIZE; *buffer == 0; size *= 2)
    {
        get_user_config_folder(buffer.get(), sizeof(buffer) - 1, "battleship");
    }
    if (!std::filesystem::exists(buffer.get()) &&
        !std::filesystem::create_directories(buffer.get()))
    {
            throw std::runtime_error("Could not find or create config path");
    }
    return std::filesystem::path(buffer.get());
}
