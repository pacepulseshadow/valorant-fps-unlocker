#pragma once
#include <windows.h>
#include "overlay_core/overlay_config.hpp"

namespace vopt::overlay_core {

class OverlayHost {
public:
    explicit OverlayHost(OverlayConfig cfg);
    ~OverlayHost();

    // Creates the layered window and pumps messages until WM_QUIT.
    int run_message_loop();

private:
    static LRESULT CALLBACK wnd_proc(HWND, UINT, WPARAM, LPARAM);
    bool register_class();
    bool create_window();

    OverlayConfig cfg_;
    HWND hwnd_ = nullptr;
};

} // namespace vopt::overlay_core