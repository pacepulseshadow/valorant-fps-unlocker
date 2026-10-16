#include <cstdio>
#include <cstring>
#include "config_layer/config_loader.hpp"
#include "fps_unlock/fps_unlocker.hpp"
#include "shared_lib/log.hpp"

using namespace vopt;

static void usage() {
    std::puts("vopt-cli <command>\n"
              "  fps unlock --target <n>\n"
              "  fps restore\n"
              "  diag [--redact]\n");
}

int main(int argc, char** argv) {
    log::init(L"vopt-cli.log");
    if (argc < 2) { usage(); return 1; }

    auto cfg = config::load_default();
    if (!cfg) { std::fprintf(stderr, "config: %s\n", cfg.error().c_str()); return 2; }

    std::string cmd = argv[1];
    if (cmd == "fps" && argc >= 3) {
        fps_unlock::Unlocker u(cfg->fps);
        std::string sub = argv[2];
        if (sub == "unlock") {
            uint32_t target = cfg->fps.target_fps;
            if (argc >= 5 && std::strcmp(argv[3], "--target") == 0)
                target = static_cast<uint32_t>(std::atoi(argv[4]));
            cfg->fps.target_fps = target;
            fps_unlock::Unlocker u2(cfg->fps);
            auto r = u2.apply();
            if (!r) { std::fprintf(stderr, "unlock failed: %d\n", (int)r.error()); return 3; }
            std::puts("ok");
            return 0;
        }
        if (sub == "restore") {
            auto r = u.restore();
            if (!r) { std::fprintf(stderr, "restore failed\n"); return 3; }
            std::puts("ok");
            return 0;
        }
    }
    if (cmd == "diag") {
        std::puts("vopt diag: build 0.6.2, admin=?, game=running");
        return 0;
    }
    usage();
    return 1;
}