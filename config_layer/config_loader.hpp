#pragma once
#include <expected>
#include <string>
#include <filesystem>
#include "fps_unlock/fps_config.hpp"
#include "frame_pacing/pacing_config.hpp"
#include "overlay_core/overlay_config.hpp"

namespace vopt::config {

struct AppConfig {
    fps_unlock::FpsConfig    fps;
    frame_pacing::PacingConfig pacing;
    overlay_core::OverlayConfig overlay;
    bool verbose_logging = false;
};

std::expected<AppConfig, std::string> load_default();
std::expected<AppConfig, std::string> load_from(const std::filesystem::path&);

} // namespace vopt::config