#pragma once
#include <filesystem>

namespace vopt::paths {

std::filesystem::path user_config_dir();
std::filesystem::path valorant_user_settings();

} // namespace vopt::paths