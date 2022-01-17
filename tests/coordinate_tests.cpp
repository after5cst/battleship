#include "gtest/gtest.h"
#include "ship.h"

// TEST(CoordinateTests, test_coords_can_be_compared) {
//     auto coord1 = Coordinate{1, 2};
//     auto coord2 = Coordinate{1, 2};
//     ASSERT_TRUE(coord1 == coord2);
//     ASSERT_FALSE(coord1 != coord2);

//     auto coord3 = Coordinate{2, 2};
//     ASSERT_FALSE(coord1 == coord3);
//     ASSERT_TRUE(coord1 != coord3);
// }

TEST(ShipTests, test_ship_detects_coordinate_overlap) {
    auto ship = Ship::create(Type::DESTROYER, {1,1}, Direction::DOWN);
    // Doesn't overlap with row above.
    ASSERT_FALSE(ship.overlaps(Coordinate{0,0}));
    ASSERT_FALSE(ship.overlaps(Coordinate{0,1}));
    ASSERT_FALSE(ship.overlaps(Coordinate{0,2}));
    // overlaps with center column only on rows 2 and 3.
    ASSERT_FALSE(ship.overlaps(Coordinate{1,0}));
    ASSERT_TRUE(ship.overlaps(Coordinate{1,1}));
    ASSERT_FALSE(ship.overlaps(Coordinate{1,2}));
    ASSERT_FALSE(ship.overlaps(Coordinate{2,0}));
    ASSERT_TRUE(ship.overlaps(Coordinate{2,1}));
    ASSERT_FALSE(ship.overlaps(Coordinate{2,2}));
    // Doesn't overlap with row below.
    ASSERT_FALSE(ship.overlaps(Coordinate{3,0}));
    ASSERT_FALSE(ship.overlaps(Coordinate{3,1}));
    ASSERT_FALSE(ship.overlaps(Coordinate{3,2}));
}

TEST(ShipTests, test_ship_detects_parallel_ship_overlap_different_col) {
    
    auto ship1 = Ship::create(Type::CARRIER, {2,1}, Direction::DOWN);
    auto ship2 = Ship::create(Type::CARRIER, {2,2}, Direction::DOWN);
    ASSERT_FALSE(ship1.overlaps(ship2));
    ASSERT_FALSE(ship2.overlaps(ship1));
}

TEST(ShipTests, test_ship_detects_parallel_ship_overlap_same_col) {
    auto battleship = Ship::create(Type::BATTLESHIP, {2,1}, Direction::DOWN);
    for (int8_t i=0; i <10; ++i)
    {
        auto destroyer = Ship::create(Type::DESTROYER, {i,1}, Direction::DOWN);
        if (i < 1 || i >= 6)
        {
            ASSERT_FALSE(battleship.overlaps(destroyer));
            ASSERT_FALSE(destroyer.overlaps(battleship));
        }
        else
        {
            ASSERT_TRUE(battleship.overlaps(destroyer));
            ASSERT_TRUE(destroyer.overlaps(battleship));
        }
    }
}

TEST(ShipTests, test_ship_detects_perpendicular_ship_overlap) {
    
    auto ship1 = Ship::create(Type::DESTROYER, {0,2}, Direction::DOWN);
    // Sail W -> E through the staionary ship at coordinate {0,2}
    for (int8_t i=0; i <4; ++i)
    {
        auto ship2 = Ship::create(Type::DESTROYER, {0,i}, Direction::RIGHT);
        if (i < 1 || i > 2)
        {
            ASSERT_FALSE(ship1.overlaps(ship2));
            ASSERT_FALSE(ship2.overlaps(ship1));
        }
        else
        {
            ASSERT_TRUE(ship1.overlaps(ship2));
            ASSERT_TRUE(ship2.overlaps(ship1));
        }
    }
}

TEST(ShipTests, test_ship_detects_perpendicular_ship_non_overlap) {
    
    auto ship1 = Ship::create(Type::DESTROYER, {2,2}, Direction::DOWN);
    // Sail E -> W with a second ship N of the stationary ship.
    for (int8_t i=0; i <5; ++i)
    {
        auto ship2 = Ship::create(Type::DESTROYER, {0,i}, Direction::RIGHT);
        ASSERT_FALSE(ship1.overlaps(ship2));
        ASSERT_FALSE(ship2.overlaps(ship1));
    }
    
    // Sail N -> S with a second ship W of the stationary ship.
    auto ship3 = Ship::create(Type::DESTROYER, {2,2}, Direction::RIGHT);
    for (int8_t i=0; i <5; ++i)
    {
        auto ship2 = Ship::create(Type::DESTROYER, {i,0}, Direction::DOWN);
        ASSERT_FALSE(ship3.overlaps(ship2));
        ASSERT_FALSE(ship2.overlaps(ship3));
    }
}
