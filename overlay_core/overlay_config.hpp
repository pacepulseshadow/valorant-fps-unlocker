#pragma once
#include <cstdint>
#include <string>

namespace vopt::overlay_core {

struct OverlayConfig {
    bool     enabled = true;
    uint8_t  alpha = 200;
    bool     show_fps = true;
    bool     show_frametime_graph = true;
    bool     show_ping = false;
    std::wstring font_family = L"Consolas";
};

} // namespace vopt::overlay_core