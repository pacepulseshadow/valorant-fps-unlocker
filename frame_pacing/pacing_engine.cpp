#include "frame_pacing/pacing_engine.hpp"
#include "shared_lib/log.hpp"
#include <windows.h>
#include <chrono>

namespace vopt::frame_pacing {

PacingEngine::PacingEngine(PacingConfig cfg) : cfg_(cfg) {}
PacingEngine::~PacingEngine() { stop(); }

void PacingEngine::start() {
    if (running_.exchange(true)) return;
    worker_ = std::thread(&PacingEngine::sample_loop, this);
}

void PacingEngine::stop() {
    if (!running_.exchange(false)) return;
    if (worker_.joinable()) worker_.join();
}

void PacingEngine::sample_loop() {
    using clock = std::chrono::steady_clock;
    auto last = clock::now();
    double acc = 0.0;
    int n = 0;

    while (running_.load()) {
        Sleep(cfg_.sample_interval_ms);
        auto now = clock::now();
        double dt = std::chrono::duration<double, std::milli>(now - last).count();
        last = now;

        acc += dt;
        if (++n >= cfg_.samples_per_window) {
            avg_ms_.store(acc / n);
            acc = 0.0;
            n = 0;
        }
    }
}

} // namespace vopt::frame_pacing