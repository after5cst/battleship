#include "gtest/gtest.h"
#include "battleship.h"

#include <fstream>

TEST(ConfigTests, testCanCallGetConfigPath) {
    auto path = get_config_path();
    ASSERT_EQ(true, std::filesystem::is_directory(path));
}

TEST(ConfigTests, testCanResetGame) {
    auto path = get_config_path();

    std::array<std::filesystem::path, 2> files = {
        path / "deleteme.file",
        path / "deleteme" / "deleteme.file"
    };

    // Put stuff in the directory so that we have something to reset.
    for (const auto& file_path: files)
    {
        if (!std::filesystem::is_regular_file(file_path))
        {
            std::filesystem::create_directories(file_path.parent_path());
            std::ofstream(file_path) << "data";
        }
    }

    clear_config();

    // Make sure the stuff we added is now gone.
    for (const auto& file_path: files)
    {
        ASSERT_FALSE(std::filesystem::is_regular_file(file_path));
    }

}

TEST(GridTests, testGridInitializesToZero) {
    auto grid = grid_t{};
    for (const auto& row : grid) {
        for (const auto& pos: row) {
            ASSERT_EQ(pos, 0);
        }
    }
    auto heat = heat_t{};
    for (const auto& row : heat) {
        for (const auto& pos: row) {
            ASSERT_EQ(pos, 0);
        }
    }
}

TEST(GridTests, testCanSaveAndLoadGrid) {
    clear_config();
    auto grid = load_aiming_grid();
    // Prove a new grid is entirely blank.
    for (const auto& row : grid) {
        for (const auto& pos: row) {
            ASSERT_EQ(pos, ' ');
        }
    }
    // Modify it, save, reload, and verify changes are there.
    for (auto i = 0; i < GRID_SIZE; ++i)
    {
        grid[i][i] = 'A';
    }
    save_aiming_grid(grid);
    grid = load_aiming_grid();
    for (auto i = 0; i < GRID_SIZE; ++i)
    {
        for (auto j = 0; j < GRID_SIZE; ++j)
        {
            ASSERT_EQ(grid[i][j], (i == j ? 'A' : ' '));
        }
    }
}

TEST(GridTests, testCanHeatSingleShip) {
    clear_config();
    std::queue<int> targets;
    targets.push(10); // push a ship of size 10.
    auto heat = get_heat(targets);
    // TODO : FINISH
}
