#pragma once

#include <string>
#include <filesystem>
#include <queue>

std::filesystem::path get_config_path();
void clear_config();

#define GRID_SIZE 10
typedef std::array<char, GRID_SIZE> grid_row_t;
typedef std::array<grid_row_t, GRID_SIZE> grid_t;

typedef std::array<uint64_t, GRID_SIZE> heat_row_t;
typedef std::array<heat_row_t, GRID_SIZE> heat_t;

grid_t load_aiming_grid();
grid_t load_ship_grid();

void save_aiming_grid(const grid_t& grid);
void save_ship_grid(const grid_t& grid);

heat_t get_heat( std::queue<int> targets);

bool place_horizontal_ship(char ship, grid_t &grid, int row, int col, int len);
