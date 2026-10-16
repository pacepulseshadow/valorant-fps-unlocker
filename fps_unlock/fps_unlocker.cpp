#include "fps_unlock/fps_unlocker.hpp"
#include "shared_lib/log.hpp"
#include "shared_lib/process_scan.hpp"
#include <windows.h>

namespace vopt::fps_unlock {

Unlocker::Unlocker(FpsConfig cfg) : cfg_(std::move(cfg)) {}

std::expected<void, UnlockStatus> Unlocker::apply() {
    if (!process_scan::is_running(L"VALORANT-Win64-Shipping.exe")) {
        log::warn("fps_unlock", "game not running, deferring apply");
        return std::unexpected(UnlockStatus::GameNotRunning);
    }

    auto cap = write_engine_cap(cfg_.target_fps);
    if (!cap) return cap;

    auto flags = patch_launch_flags();
    if (!flags) return flags;

    applied_ = true;
    log::info("fps_unlock", "unlocked to {} fps", cfg_.target_fps);
    return {};
}

std::expected<void, UnlockStatus> Unlocker::write_engine_cap(uint32_t fps) {
    // Engine reads this from the per-user GameUserSettings.ini.
    // We only touch the FrameRateLimit key.
    const auto path = cfg_.game_user_settings_path;
    if (path.empty()) return std::unexpected(UnlockStatus::UnsupportedPatch);

    if (!ini::set_uint(path, L"ScalabilityGroups", L"FrameRateLimit", fps)) {
        return std::unexpected(UnlockStatus::RegistryWriteFailed);
    }
    return {};
}

std::expected<void, UnlockStatus> Unlocker::patch_launch_flags() {
    if (!cfg_.use_high_priority) return {};
    // Best-effort: bump scheduling priority once the process is up.
    if (!process_scan::set_priority(L"VALORANT-Win64-Shipping.exe",
                                    HIGH_PRIORITY_CLASS)) {
        log::warn("fps_unlock", "priority bump failed (non-fatal)");
    }
    return {};
}

std::expected<void, UnlockStatus> Unlocker::restore() {
    if (!applied_) return {};
    return write_engine_cap(cfg_.stock_fps);
}

} // namespace vopt::fps_unlock