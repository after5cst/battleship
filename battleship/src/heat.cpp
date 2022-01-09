#include "battleship.h"
#include <assert.h>
#include <fstream>
#include <utility>

struct coordinate {
    int x;
    int y;
};


bool place_horizontal_ship(char ship, grid_t &grid, int row, int col, int len)
{
    auto& grid_row = grid[row];
    if (col < 0)
    {
        assert (false);
        return false;
    }
    if (GRID_SIZE <= (col + len))
    {
        assert (false);
        return false;
    }
    for (auto i = col; i < (col + len); ++i)
    {
        const auto &ch = grid_row[i];
        switch (ch)
        {
            case ' ':  break;  // empty
            case 'X':  break;  // A 'hit', but unknown which ship
            default:
                if (ch != ship)
                {
                    return false;
                }
        }
    }
    // Safe to place.
    for (auto i = col; i < (col + len); ++i)
    {
        grid_row[i] = ship;
    }
    return true;
}

bool calculate_heat(heat_t& heat, const grid_t &input_grid, std::queue<int> targets)
{
    if (targets.empty())
    {
        assert(false);
        return false;
    }
    const auto ship_size = targets.front();
    targets.pop();

    for (auto row = 0; row < GRID_SIZE + 1 - ship_size; ++row)
    {
        for (auto col = 0; col < GRID_SIZE + 1 - ship_size; ++col)
        {
            auto grid = grid_t{input_grid};
            // STOPPED HERE.  NEED TO ACTUALLY ACCUMULATE HEAT AND DO VERTICAL.
            if (place_horizontal_ship('?', grid, row, col, ship_size))
            {
                // if (targets.empty())
                // increment_heat(heat, )
            }
        }
    }
    return true;
}

heat_t get_heat( std::queue<int> targets)
{
    // Heat only makes sense for aiming.  We know where *our* ships are.
    auto grid = load_aiming_grid();
    auto heat = heat_t{};
    calculate_heat(heat, grid, std::move(targets));
    return heat;
}
