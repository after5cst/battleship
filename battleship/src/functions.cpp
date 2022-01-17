#include "ship.h"

GridInfo build_grid_info(const TypeGrid& grid)
{
    GridInfo result;
    auto miss_index = 0;

    for (int8_t pos = 0; pos < GRID_AREA; ++pos)
    {
        switch (grid[pos])
        {
            case Type::MISS:
                result.misses[miss_index++] = pos;
            default:
                break;
        }
    }

    
    result.misses[miss_index] = -1;
    return result;
}