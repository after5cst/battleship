#include "battleship.h"
#include <assert.h>
#include <fstream>

static void save(const TypeGrid& grid, std::string name)
{
    auto path = get_config_path() / (name + ".grid");
    auto fp = std::ofstream(path);

    for (uint8_t row = 0; row < GRID_DIM; ++row)
    {
        for (uint8_t col = 0; col < GRID_DIM; ++col)
        {
            auto ch = static_cast<char>(grid[Coordinate(row, col).pos]);
            fp << (ch ? ch : ' '); // convert '\0' to ' '.
        }
        fp << std::endl;
    }
}

static TypeGrid load(std::string name)
{
    auto path = get_config_path() / (name + ".grid");
    std::ifstream file(path, std::ios::binary | std::ios::ate);
    std::streamsize size = file.tellg();
    file.seekg(0, std::ios::beg);

    std::vector<char> source_buffer(size);
    if (!file.read(source_buffer.data(), size))
    {
        throw std::runtime_error("Could not load file.");
    }

    auto offset = 0;
    auto grid = TypeGrid{};

    for (const auto& ch: source_buffer)
    {
        switch (ch)
        {
            case '\r':
            case '\n':
                break;
            default:
                grid[offset++] = static_cast<Type>(ch);
        }
    }
    assert(offset == 100);
    return grid;
}

TypeGrid load_aiming_grid()
{
    return load("aiming");
}

TypeGrid load_ship_grid()
{
    return load("ship");
}

void save_aiming_grid(const TypeGrid& grid)
{
    save(grid, "aiming");
}

void save_ship_grid(const TypeGrid& grid)
{
    save(grid, "ship");
}
