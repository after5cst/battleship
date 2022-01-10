#pragma once
#include <stdint.h>
#include <limits>

struct Coordinate {
    uint8_t row = std::numeric_limits<uint8_t>::max();
    uint8_t col = std::numeric_limits<uint8_t>::max();

    bool valid() const { return (row < 10 && col < 10); }
};
