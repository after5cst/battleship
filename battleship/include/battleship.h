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

enum class Type : char {
    NOTHING = ' ',
    MISS = '-',
    HIT = '*',
    CARRIER = 'A',
    BATTLESHIP = 'B',
    CRUISER = 'C',
    DESTROYER = 'D',
    SUB = 'S',
    SUNK = 'K'
};

struct TypeGrid : public std::array<Type, GRID_AREA>
{
    static TypeGrid create()
    {
        TypeGrid peg_board;
        peg_board.fill(Type::NOTHING);
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
    Positions misses;
    Positions::iterator iter;
};

GridInfo build_grid_info(const TypeGrid& grid);
