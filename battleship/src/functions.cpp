#include "ship.h"

GridInfo build_grid_info(const TypeGrid& grid)
{
    GridInfo result = {0};
    // Make coordinate lists of each cell type, terminated by coordinate -1.
    auto lengths = std::array<int8_t, CellType::MAX>{0};

    for (int8_t pos = 0; pos < GRID_AREA; ++pos)
    {
        auto cell_type = grid[pos];
        auto &position = result.positions[cell_type];
        position[lengths[cell_type]++] = pos;
    }

    for (auto i = 0; i < CellType::MAX; ++i)
    {
        auto offset = lengths[i];
        if (offset < CellType::MAX)
        {
            result.positions[i][offset] = -1;
        }
    }

    return result;
}