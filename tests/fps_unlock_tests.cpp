#include <cassert>
#include <cstdio>
#include "fps_unlock/fps_config.hpp"
#include "fps_unlock/fps_unlocker.hpp"

using namespace vopt::fps_unlock;

static void test_default_target() {
    FpsConfig cfg{};
    Unlocker u(cfg);
    assert(u.current_target() == 360);
}

static void test_restore_without_apply_is_noop() {
    FpsConfig cfg{};
    Unlocker u(cfg);
    auto r = u.restore();
    assert(r.has_value()); // no-op must succeed
}

int main() {
    test_default_target();
    test_restore_without_apply_is_noop();
    std::puts("fps_unlock tests ok");
    return 0;
}