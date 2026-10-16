#pragma once
#include <cstdint>
#include <filesystem>

namespace vopt::fps_unlock {

struct FpsConfig {
    uint32_t target_fps = 360;
    uint32_t stock_fps = 144;
    bool     use_high_priority = true;
    bool     disable_vsync = true;
    std::filesystem::path game_user_settings_path;
};

} // namespace vopt::fps_unlock