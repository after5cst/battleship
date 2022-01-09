#include "battleship.h"
#include <fstream>

static void save(const grid_t& grid, std::string name)
{
    auto path = get_config_path() / (name + ".grid");
    auto fp = std::ofstream(path);

    for (const auto& row : grid) {
        for (const auto& pos: row) {
            fp << (pos ? pos : ' ');  // Convert 0x00 to space.
        }
        fp << std::endl;
    }
}

static grid_t load(std::string name)
{
    auto path = get_config_path() / (name + ".grid");
    auto fp = std::ifstream(path, std::ios::in);
    if (!fp.good())
    {
        throw std::runtime_error("Could not load file.");
    }

    auto grid = grid_t();
    
    for (auto& row : grid) {
        std::string line;
        std::getline(fp, line);
        auto iter = line.begin();
        for (auto& pos: row) {
            pos = *iter;
            ++iter;
        }
    }
    return grid;
}

grid_t load_aiming_grid()
{
    return load("aiming");
}

grid_t load_ship_grid()
{
    return load("ship");
}

void save_aiming_grid(const grid_t& grid)
{
    save(grid, "aiming");
}

void save_ship_grid(const grid_t& grid)
{
    save(grid, "ship");
}
