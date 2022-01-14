#include "gtest/gtest.h"
#include "ship.h"

// Things to track:
// KNOWN ship hits
// HIT locations
// MISS locations
// Ship SUNK (if known)

TEST(ConfigurationsTests, test_ship_possibile_locations) {

    auto grid = Grid::create(2);
    auto locations = ship_possibile_locations<2>(Type::DESTROYER);
    ASSERT_EQ(locations.size(), 4);

    grid = Grid::create(3);
    locations = ship_possibile_locations<3>(Type::DESTROYER);
    ASSERT_EQ(locations.size(), 12);
}
