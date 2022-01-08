#pragma once

#include <string>
#include <filesystem>

const std::string generateHelloString(const std::string & personName);

std::filesystem::path get_config_path();
