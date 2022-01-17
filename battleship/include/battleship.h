#pragma once

#include <array>
#include <assert.h>
#include <memory>
#include <string>
#include <filesystem>
#include <queue>


#define GRID_DIM 10
#define GRID_AREA (GRID_DIM * GRID_DIM)

struct Coordinate {
    const int8_t row;
    const int8_t col;
    const int8_t pos;

    Coordinate(int8_t r, int8_t c) : row(r), col(c), pos(r * GRID_DIM + c) {}
    Coordinate(int8_t p) : row(p / GRID_DIM), col(p % GRID_DIM), pos(p) {}

    bool operator <(const Coordinate& two) const
    {
        return pos < two.pos;
    }

    bool operator <=(const Coordinate& two) const
    {
        return pos <= two.pos;
    }

    bool operator >(const Coordinate& two) const
    {
        return pos > two.pos;
    }

    bool operator >=(const Coordinate& two) const
    {
        return pos <= two.pos;
    }

    bool operator ==(const Coordinate& two) const
    {
        return pos == two.pos;
    }

    bool operator !=(const Coordinate& two) const
    {
        return pos != two.pos;
    }
};

enum class Direction{ RIGHT, DOWN };

enum CellType{
    NOTHING = 0,
    MISS = 1,
    HIT = 2,
    CARRIER = 3,
    BATTLESHIP = 4,
    CRUISER = 5,
    DESTROYER = 6,
    SUB = 7,
    SUNK = 8,
    MAX = 9
};

struct TypeGrid : public std::array<CellType, GRID_AREA>
{
    static TypeGrid create()
    {
        TypeGrid peg_board;
        peg_board.fill(CellType::NOTHING);
        return peg_board;
    }
};

std::filesystem::path get_config_path();
void clear_config();

TypeGrid load_aiming_grid();
TypeGrid load_ship_grid();

void save_aiming_grid(const TypeGrid& grid);
void save_ship_grid(const TypeGrid& grid);

typedef std::array<int8_t, GRID_AREA> Positions;

struct GridInfo
{
    Positions positions[CellType::MAX];
};

GridInfo build_grid_info(const TypeGrid& grid);
