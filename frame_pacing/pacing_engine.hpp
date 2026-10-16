#pragma once
#include <atomic>
#include <thread>
#include <cstdint>
#include "frame_pacing/pacing_config.hpp"

namespace vopt::frame_pacing {

class PacingEngine {
public:
    explicit PacingEngine(PacingConfig cfg);
    ~PacingEngine();

    void start();
    void stop();

    // Rolling 1s average, updated by the sampler thread.
    double avg_frametime_ms() const noexcept { return avg_ms_.load(); }

private:
    void sample_loop();

    PacingConfig cfg_;
    std::atomic<bool> running_{false};
    std::atomic<double> avg_ms_{0.0};
    std::thread worker_;
};

} // namespace vopt::frame_pacing