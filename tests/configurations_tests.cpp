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
    ASSERT_EQ(info.positions[CellType::MISS][0], -1);  // No misses found.

    grid[12] = CellType::MISS;
    grid[24] = CellType::MISS;
    grid[6] = CellType::MISS;
    info = build_grid_info(grid);
    ASSERT_EQ(info.positions[CellType::MISS][0], 6);
    ASSERT_EQ(info.positions[CellType::MISS][1], 12);
    ASSERT_EQ(info.positions[CellType::MISS][2], 24);
    ASSERT_EQ(info.positions[CellType::MISS][3], -1);  // No more misses.
}

TEST(ConfigurationsTests, test_ship_possibile_locations_empty_grid) {

    auto grid = TypeGrid::create();
    auto info = build_grid_info(grid);
    auto locations = ship_possibile_locations<2>(CellType::DESTROYER, info);
    ASSERT_EQ(locations.size(), 4);

    locations = ship_possibile_locations<3>(CellType::DESTROYER, info);
    ASSERT_EQ(locations.size(), 12);
}

TEST(ConfigurationsTests, test_ship_possibile_locations_deducts_misses) {

    auto grid = TypeGrid::create();
    grid[Coordinate(0,0).pos] = CellType::MISS;
    auto info = build_grid_info(grid);
    auto locations = ship_possibile_locations<3>(CellType::DESTROYER, info);
    ASSERT_EQ(locations.size(), 10);
    
    grid[Coordinate(0,2).pos] = CellType::MISS;
    info = build_grid_info(grid);
    locations = ship_possibile_locations<3>(CellType::DESTROYER, info);
    ASSERT_EQ(locations.size(), 8);
    
    grid[Coordinate(2,0).pos] = CellType::MISS;
    info = build_grid_info(grid);
    locations = ship_possibile_locations<3>(CellType::DESTROYER, info);
    ASSERT_EQ(locations.size(), 6);
    
    grid[Coordinate(2,2).pos] = CellType::MISS;
    info = build_grid_info(grid);
    locations = ship_possibile_locations<3>(CellType::DESTROYER, info);
    ASSERT_EQ(locations.size(), 4);
    
    grid[Coordinate(1,1).pos] = CellType::MISS;
    info = build_grid_info(grid);
    locations = ship_possibile_locations<3>(CellType::DESTROYER, info);
    ASSERT_EQ(locations.size(), 0);
}

TEST(ConfigurationsTests, test_ship_possibile_locations_ensures_hits_overlap) {

    auto grid = TypeGrid::create();
    grid[Coordinate(1,1).pos] = CellType::DESTROYER;
    auto info = build_grid_info(grid);
    auto locations = ship_possibile_locations<3>(CellType::DESTROYER, info);
    ASSERT_EQ(locations.size(), 4);
    
    // Another known ship location should reduce possibilities.
    grid[Coordinate(1,0).pos] = CellType::SUB;
    info = build_grid_info(grid);
    locations = ship_possibile_locations<3>(CellType::DESTROYER, info);
    ASSERT_EQ(locations.size(), 3);    

    // A single location when all ship pieces have been placed.
    grid[Coordinate(1,2).pos] = CellType::DESTROYER;
    info = build_grid_info(grid);
    locations = ship_possibile_locations<3>(CellType::DESTROYER, info);
    ASSERT_EQ(locations.size(), 1);
}
