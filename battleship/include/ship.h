#pragma once
#include "coordinate.h"
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
            return (
                (two.row == nw.row) &&
                (two.col <= se.col) &&
                (two.col >= nw.col )
            );
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
                return (
                    (two.nw.row == nw.row) &&
                    (two.nw.col <= se.col) &&
                    (two.se.col >= nw.col )
                );
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
private:
    static Coordinate calculate_se(Coordinate nw, uint8_t length, Direction direction)
    {
        return (direction == Direction::RIGHT)
            ? Coordinate{ nw.row, static_cast<uint8_t>(nw.col + length - 1) }
            : Coordinate{ static_cast<uint8_t>(nw.row + length - 1), nw.col }
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

template <int SIZE=GRID_SIZE>
std::vector<Ship> ship_possibile_locations(Type id/*,TODO: filtering*/)
{
    std::vector<Ship> locations;
    locations.reserve(180); // Big enough for all destroyer locations.
    for (uint8_t row=0; row < SIZE; ++row)
    {
        for (uint8_t col=0; col < SIZE; ++col)
        {
            auto right = Ship::create(id, Coordinate{row, col}, Direction::RIGHT);
            if (right.se.col < SIZE) // Validity checks start with "still on the board"
            {
                locations.push_back(std::move(right));
            }
            auto down = Ship::create(id, Coordinate{row, col}, Direction::DOWN);
            if (right.se.col < SIZE) // Validity checks start with "still on the board"
            {
                locations.push_back(std::move(down));
            }
        }
    }
    return locations;
}
