#pragma once
#include <cstdint>
#include <string>
#include <expected>
#include "fps_unlock/fps_config.hpp"

namespace vopt::fps_unlock {

enum class UnlockStatus {
    Ok,
    NotElevated,
    GameNotRunning,
    UnsupportedPatch,
    RegistryWriteFailed,
};

class Unlocker {
public:
    explicit Unlocker(FpsConfig cfg);

    // Removes the engine-level FPS cap and pushes the target frame budget.
    std::expected<void, UnlockStatus> apply();

    // Restores the stock cap. Safe to call even if apply() never ran.
    std::expected<void, UnlockStatus> restore();

    uint32_t current_target() const noexcept { return cfg_.target_fps; }

private:
    std::expected<void, UnlockStatus> write_engine_cap(uint32_t fps);
    std::expected<void, UnlockStatus> patch_launch_flags();

    FpsConfig cfg_;
    bool applied_ = false;
};

} // namespace vopt::fps_unlock