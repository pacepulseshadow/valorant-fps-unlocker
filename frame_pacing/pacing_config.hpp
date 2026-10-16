#pragma once
#include <cstdint>

namespace vopt::frame_pacing {

struct PacingConfig {
    uint32_t sample_interval_ms = 16;
    uint32_t samples_per_window = 60;
    bool     enable_nvidia_reflex_hint = true;
    bool     enable_amd_anti_lag_hint = false;
};

} // namespace vopt::frame_pacing