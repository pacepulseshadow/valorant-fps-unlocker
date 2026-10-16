#include <cassert>
#include <cstdio>
#include <thread>
#include <chrono>
#include "frame_pacing/pacing_engine.hpp"

using namespace vopt::frame_pacing;

int main() {
    PacingConfig cfg{};
    cfg.sample_interval_ms = 5;
    cfg.samples_per_window = 4;

    PacingEngine e(cfg);
    e.start();
    std::this_thread::sleep_for(std::chrono::milliseconds(60));
    e.stop();

    // Should have produced at least one window.
    assert(e.avg_frametime_ms() > 0.0);
    std::puts("pacing tests ok");
    return 0;
}