#include "battleship.h"
#include <assert.h>
#include <fstream>
#include <unordered_map>


static const std::unordered_map<CellType, char> MAP_CELL_TYPE_TO_CHAR = {
    { CellType::NOTHING, ' ' },
    { CellType::MISS, '-' },
    { CellType::HIT, '*' },
    { CellType::CARRIER, 'A' },
    { CellType::BATTLESHIP, 'B' },
    { CellType::CRUISER, 'C' },
    { CellType::DESTROYER, 'D' },
    { CellType::SUB, 'S' },
    { CellType::SUNK, '!' },
    { CellType::MAX, '%' },
};


static const std::unordered_map<char, CellType> MAP_CHAR_TO_CELL_TYPE = {
    { ' ', CellType::NOTHING },
    { '-', CellType::MISS },
    { '*', CellType::HIT },
    { 'A', CellType::CARRIER },
    { 'B', CellType::BATTLESHIP },
    { 'C', CellType::CRUISER },
    { 'D', CellType::DESTROYER },
    { 'S', CellType::SUB },
    { '!', CellType::SUNK },
    { '?', CellType::MAX },
};

static void save(const TypeGrid& grid, std::string name)
{
    auto path = get_config_path() / (name + ".grid");
    auto fp = std::ofstream(path);

    for (uint8_t row = 0; row < GRID_DIM; ++row)
    {
        for (uint8_t col = 0; col < GRID_DIM; ++col)
        {
            auto iter = MAP_CELL_TYPE_TO_CHAR.find(grid[Coordinate(row, col).pos]);
            if (iter != MAP_CELL_TYPE_TO_CHAR.end())
            {
                fp << iter->second;
            }
            else
            {
                assert(false);
                fp << '?';
            }
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
        auto iter = MAP_CHAR_TO_CELL_TYPE.find(ch);
        if (iter != MAP_CHAR_TO_CELL_TYPE.end())
        {
            grid[offset++] = iter->second;
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
