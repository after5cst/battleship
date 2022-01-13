#pragma once
#include "battleship.h"
#include <stdint.h>


struct Coordinate {
    const uint8_t row;
    const uint8_t col;

    // bool valid() const { return (row < GRID_SIZE) && (col < GRID_SIZE); }

    // friend bool operator== (const Coordinate& c1, const Coordinate& c2)
    // {
    //     return ((c1.col == c2.col) && (c1.row == c2.row) && c1.valid());
    // }
    // friend bool operator!= (const Coordinate& c1, const Coordinate& c2)
    // {
    //     return !(c1 == c2);
    // }
};

enum class Direction{ RIGHT, DOWN };
