#pragma once
#include "battleship.h"
#include <assert.h>
#include <stdint.h>
#include <limits>
#include <vector>

uint8_t calculate_ship_length(Type id);  // forward declaration.

struct Ship 
{
    Type id;
    const uint8_t length;
    const Coordinate nw;
    const Coordinate se;
    const Direction direction;

    static Ship create(Type ship_id, Coordinate anchor, Direction right_or_down)
    {
        auto length = calculate_ship_length(ship_id);
        auto se = calculate_se(anchor, length, right_or_down);
        return Ship{ship_id, length, anchor, se, right_or_down};
    }

    bool overlaps(const Coordinate& two) const
    {
        if (direction == Direction::RIGHT)
        {
            return nw <= two && two <= se;
        }
        // direction is DOWN
        return (
            (two.col == nw.col) &&
            (two.row <= se.row) &&
            (two.row >= nw.row )
        );
    }

    bool overlaps(const Ship& two) const
    {
        if (direction == two.direction)
        {
            if (direction == Direction::RIGHT)
            {
                return nw <= two.se && two.nw <= se;
            }
            // direction is DOWN
            return (
                (two.nw.col == nw.col) &&
                (two.nw.row <= se.row) &&
                (two.se.row >= nw.row )
            );
        }

        // Ships are perpendicular.
        if (direction == Direction::RIGHT)
        {
            return (
                (nw.row <= two.se.row) && 
                (nw.row >= two.nw.row) &&
                (two.nw.col <= se.col) && 
                (two.nw.col >= nw.col)
            );
        }
        return (
            (nw.col <= two.se.col) && 
            (nw.col >= two.nw.col) &&
            (two.nw.row <= se.row) && 
            (two.nw.row >= nw.row)
        );
    }

    bool overlaps_any(const Positions &positions)
    {
        for (auto& pos : positions)
        {
            if (pos == -1)
            {
                break;
            }
            if (overlaps(Coordinate{pos}))
            {
                return true;
            }
        }
        return false;
    }

    bool overlaps_all(const Positions &positions)
    {
        for (auto& pos : positions)
        {
            if (pos == -1)
            {
                break;
            }
            if (!overlaps(Coordinate{pos}))
            {
                return false;
            }
        }
        return true;
    }

private:
    static Coordinate calculate_se(Coordinate nw, uint8_t length, Direction direction)
    {
        return (direction == Direction::RIGHT)
            ? Coordinate{ nw.row, static_cast<int8_t>(nw.col + length - 1) }
            : Coordinate{ static_cast<int8_t>(nw.row + length - 1), nw.col }
            ;
    }
};

inline uint8_t calculate_ship_length(Type id)
{
    switch (id)
    {
        case Type::CARRIER:  return 5;
        case Type::BATTLESHIP:  return 4;
        case Type::CRUISER:  return 3;
        case Type::SUB:  return 3;
        case Type::DESTROYER:  return 2;
    }
    assert(false);
    return 1;
}

template <int SIZE=GRID_DIM>
std::vector<Ship> ship_possibile_locations(Type id, const GridInfo& info)
{
    static_assert(SIZE <= GRID_DIM, "Template parameter too large");
    std::vector<Ship> locations;
    locations.reserve(180); // Big enough for all destroyer locations.
    for (int8_t row=0; row < SIZE; ++row)
    {
        for (int8_t col=0; col < SIZE; ++col)
        {
            auto right = Ship::create(id, Coordinate{row, col}, Direction::RIGHT);
            if (right.se.col < SIZE // Validity checks start with "still on the board"
                && (!right.overlaps_any(info.misses))
                // && right.overlaps_all(info.hits)
            )
            {
                locations.push_back(std::move(right));
            }
            auto down = Ship::create(id, Coordinate{row, col}, Direction::DOWN);
            if (down.se.row < SIZE // Validity checks start with "still on the board"
                && (!down.overlaps_any(info.misses))
            )
            {
                locations.push_back(std::move(down));
            }
        }
    }
    return locations;
}
