#include "gtest/gtest.h"
#include "battleship.h"

TEST(BattleshipTests, testCanCallGetConfigPath) {
    auto path = get_config_path();
    ASSERT_EQ(true, std::filesystem::is_directory(path));
}
