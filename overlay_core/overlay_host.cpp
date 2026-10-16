#include "overlay_core/overlay_host.hpp"
#include "shared_lib/log.hpp"

namespace vopt::overlay_core {

static constexpr wchar_t kClassName[] = L"VoptOverlayHost";

OverlayHost::OverlayHost(OverlayConfig cfg) : cfg_(cfg) {}
OverlayHost::~OverlayHost() {
    if (hwnd_) DestroyWindow(hwnd_);
    UnregisterClassW(kClassName, GetModuleHandleW(nullptr));
}

bool OverlayHost::register_class() {
    WNDCLASSEXW wc{};
    wc.cbSize = sizeof(wc);
    wc.lpfnWndProc = &OverlayHost::wnd_proc;
    wc.hInstance = GetModuleHandleW(nullptr);
    wc.lpszClassName = kClassName;
    wc.hCursor = LoadCursor(nullptr, IDC_ARROW);
    return RegisterClassExW(&wc) != 0;
}

bool OverlayHost::create_window() {
    hwnd_ = CreateWindowExW(
        WS_EX_TOPMOST | WS_EX_LAYERED | WS_EX_TRANSPARENT | WS_EX_TOOLWINDOW,
        kClassName, L"Valorant-Optimizer Overlay",
        WS_POPUP, 0, 0, GetSystemMetrics(SM_CXSCREEN),
        GetSystemMetrics(SM_CYSCREEN),
        nullptr, nullptr, GetModuleHandleW(nullptr), nullptr);
    if (!hwnd_) return false;
    SetLayeredWindowAttributes(hwnd_, 0, cfg_.alpha, LWA_ALPHA);
    ShowWindow(hwnd_, SW_SHOWNOACTIVATE);
    return true;
}

int OverlayHost::run_message_loop() {
    if (!register_class() || !create_window()) {
        log::error("overlay", "failed to init overlay host");
        return 1;
    }
    MSG msg{};
    while (GetMessageW(&msg, nullptr, 0, 0) > 0) {
        TranslateMessage(&msg);
        DispatchMessageW(&msg);
    }
    return 0;
}

LRESULT CALLBACK OverlayHost::wnd_proc(HWND h, UINT m, WPARAM w, LPARAM l) {
    if (m == WM_DESTROY) { PostQuitMessage(0); return 0; }
    return DefWindowProcW(h, m, w, l);
}

} // namespace vopt::overlay_core