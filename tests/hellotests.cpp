#include "gtest/gtest.h"
#include "hello.h"

TEST(HelloTests, testHello) {
    ASSERT_STREQ("Hello Jim", generateHelloString("Jim").c_str());
}

TEST(HelloTests, testCanCallGetConfigPath) {
    auto path = get_config_path();
    ASSERT_EQ(true, std::filesystem::is_directory(path));
}
