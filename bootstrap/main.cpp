#include <windows.h>
#include <cstdio>
#include "config_layer/config_loader.hpp"
#include "fps_unlock/fps_unlocker.hpp"
#include "frame_pacing/pacing_engine.hpp"
#include "overlay_core/overlay_host.hpp"
#include "shared_lib/log.hpp"

using namespace vopt;

static bool has_admin() {
    BOOL admin = FALSE;
    PSID grp = nullptr;
    SID_IDENTIFIER_AUTHORITY nt = SECURITY_NT_AUTHORITY;
    if (AllocateAndInitializeSid(&nt, 2, SECURITY_BUILTIN_DOMAIN_RID,
            DOMAIN_ALIAS_RID_ADMINS, 0, 0, 0, 0, 0, 0, &grp)) {
        CheckTokenMembership(nullptr, grp, &admin);
        FreeSid(grp);
    }
    return admin == TRUE;
}

int WINAPI wWinMain(HINSTANCE, HINSTANCE, PWSTR, int) {
    log::init(L"valorant-fps-unlocker.log");
    log::info("boot", "valorant-fps-unlocker 0.6.2 starting");

    if (!has_admin()) {
        log::warn("boot", "not elevated; some FPS unlock paths disabled");
    }

    auto cfg = config::load_default();
    if (!cfg) {
        log::error("boot", "config load failed: {}", cfg.error());
        return 1;
    }

    fps_unlock::Unlocker unlocker(cfg->fps);
    frame_pacing::PacingEngine pacing(cfg->pacing);
    overlay_core::OverlayHost overlay(cfg->overlay);

    unlocker.apply();
    pacing.start();
    overlay.run_message_loop();
    return 0;
}