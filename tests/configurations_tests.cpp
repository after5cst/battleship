#include "gtest/gtest.h"
#include "ship.h"

// Things to track:
// KNOWN ship hits
// HIT locations
// MISS locations
// Ship SUNK (if known)

// TODO : Build these things (HitLocs, etc.) from the PegBoard.  That way,
//        I still have a single source of truth.  It only needs to be
//        figured out once per turn, which should be fast enough.

TEST(ConfigurationsTests, test_ship_possibile_locations) {

    auto grid = PegBoard::create();
    auto locations = ship_possibile_locations<2>(Type::DESTROYER);
    ASSERT_EQ(locations.size(), 4);

    grid = PegBoard::create();
    locations = ship_possibile_locations<3>(Type::DESTROYER);
    ASSERT_EQ(locations.size(), 12);
}
