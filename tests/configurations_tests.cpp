#include "gtest/gtest.h"
#include "ship.h"

// Things to track:
// KNOWN ship hits
// HIT locations
// MISS locations
// Ship SUNK (if known)

// TODO : Build these things (HitLocs, etc.) from the TypeGrid.  That way,
//        I still have a single source of truth.  It only needs to be
//        figured out once per turn, which should be fast enough.

TEST(ConfigurationsTests, test_build_grid_info_finds_misses) {
    auto grid = TypeGrid::create();
    auto info = build_grid_info(grid);
    ASSERT_EQ(info.misses[0], -1);  // No misses found.

    grid[12] = Type::MISS;
    grid[24] = Type::MISS;
    grid[6] = Type::MISS;
    info = build_grid_info(grid);
    ASSERT_EQ(info.misses[0], 6);
    ASSERT_EQ(info.misses[1], 12);
    ASSERT_EQ(info.misses[2], 24);
    ASSERT_EQ(info.misses[3], -1);  // No more misses.
}

TEST(ConfigurationsTests, test_ship_possibile_locations_empty_grid) {

    auto grid = TypeGrid::create();
    auto info = build_grid_info(grid);
    auto locations = ship_possibile_locations<2>(Type::DESTROYER, info);
    ASSERT_EQ(locations.size(), 4);

    locations = ship_possibile_locations<3>(Type::DESTROYER, info);
    ASSERT_EQ(locations.size(), 12);
}

TEST(ConfigurationsTests, test_ship_possibile_locations_deducts_misses) {

    auto grid = TypeGrid::create();
    grid[Coordinate(0,0).pos] = Type::MISS;
    auto info = build_grid_info(grid);
    auto locations = ship_possibile_locations<3>(Type::DESTROYER, info);
    ASSERT_EQ(locations.size(), 10);
    
    grid[Coordinate(0,2).pos] = Type::MISS;
    info = build_grid_info(grid);
    locations = ship_possibile_locations<3>(Type::DESTROYER, info);
    ASSERT_EQ(locations.size(), 8);
    
    grid[Coordinate(2,0).pos] = Type::MISS;
    info = build_grid_info(grid);
    locations = ship_possibile_locations<3>(Type::DESTROYER, info);
    ASSERT_EQ(locations.size(), 6);
    
    grid[Coordinate(2,2).pos] = Type::MISS;
    info = build_grid_info(grid);
    locations = ship_possibile_locations<3>(Type::DESTROYER, info);
    ASSERT_EQ(locations.size(), 4);
    
    grid[Coordinate(1,1).pos] = Type::MISS;
    info = build_grid_info(grid);
    locations = ship_possibile_locations<3>(Type::DESTROYER, info);
    ASSERT_EQ(locations.size(), 0);
}

// TEST(ConfigurationsTests, test_ship_possibile_locations_ensures_hits_overlap) {

//     auto grid = TypeGrid::create();
//     grid[Coordinate(1,1).pos] = Type::DESTROYER;
//     auto info = build_grid_info(grid);
//     auto locations = ship_possibile_locations<3>(Type::DESTROYER, info);
//     ASSERT_EQ(locations.size(), 4);
    
//     grid[Coordinate(0,2).pos] = Type::DESTROYER;
//     info = build_grid_info(grid);
//     locations = ship_possibile_locations<3>(Type::DESTROYER, info);
//     ASSERT_EQ(locations.size(), 1);
// }
