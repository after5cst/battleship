#include "gtest/gtest.h"
#include "ship.h"

// Things to track:
// KNOWN ship hits
// HIT locations
// MISS locations
// Ship SUNK (if known)

TEST(ConfigurationsTests, test_ship_possibile_locations) {
    auto locations = ship_possibile_locations<2>('D');
    ASSERT_EQ(locations.size(), 4);
    locations = ship_possibile_locations<3>('D');
    ASSERT_EQ(locations.size(), 12);
}
