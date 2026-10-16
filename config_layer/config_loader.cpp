#include "config_layer/config_loader.hpp"
#include "shared_lib/json_lite.hpp"
#include "shared_lib/paths.hpp"

namespace vopt::config {

std::expected<AppConfig, std::string> load_default() {
    auto p = paths::user_config_dir() / L"valorant-fps-unlocker.json";
    if (!std::filesystem::exists(p)) {
        return AppConfig{}; // sane defaults
    }
    return load_from(p);
}

std::expected<AppConfig, std::string> load_from(const std::filesystem::path& p) {
    auto doc = json_lite::parse_file(p);
    if (!doc) return std::unexpected("failed to parse config: " + doc.error());

    AppConfig cfg{};
    cfg.fps.target_fps = doc->get_u32("fps.target_fps", 360);
    cfg.fps.use_high_priority = doc->get_bool("fps.high_priority", true);
    cfg.pacing.sample_interval_ms = doc->get_u32("pacing.sample_ms", 16);
    cfg.overlay.alpha = static_cast<uint8_t>(doc->get_u32("overlay.alpha", 200));
    cfg.overlay.show_fps = doc->get_bool("overlay.show_fps", true);
    cfg.verbose_logging = doc->get_bool("log.verbose", false);
    return cfg;
}

} // namespace vopt::config