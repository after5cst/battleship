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

TEST(GridTests, testGridInitializesToSpace) {
    auto grid = Grid::create(2);
    auto empty = std::string("    ");
    ASSERT_EQ(std::string(grid->data), empty);
}

TEST(GridTests, testCanSaveAndLoadGrid) {
    clear_config(2);
    auto grid = load_aiming_grid();
    // Prove a new grid is entirely blank.
    auto empty = std::string("    ");
    ASSERT_EQ(std::string(grid->data), empty);

    // Modify it, save, reload, and verify changes are there.
    grid->data[2] = 'A';
    save_aiming_grid(grid.get());
    grid = load_aiming_grid();
    auto not_empty = std::string("  A ");
    ASSERT_EQ(std::string(grid->data), not_empty);
}
