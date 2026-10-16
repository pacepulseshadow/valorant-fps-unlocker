#include "shared_lib/paths.hpp"
#include <windows.h>
#include <shlobj.h>

namespace vopt::paths {

std::filesystem::path user_config_dir() {
    PWSTR p = nullptr;
    std::filesystem::path out;
    if (SUCCEEDED(SHGetKnownFolderPath(FOLDERID_RoamingAppData, 0, nullptr, &p))) {
        out = std::filesystem::path(p) / L"valorant-fps-unlocker";
        std::filesystem::create_directories(out);
    }
    if (p) CoTaskMemFree(p);
    return out;
}

std::filesystem::path valorant_user_settings() {
    PWSTR p = nullptr;
    std::filesystem::path out;
    if (SUCCEEDED(SHGetKnownFolderPath(FOLDERID_LocalAppData, 0, nullptr, &p))) {
        out = std::filesystem::path(p) /
              L"VALORANT" / L"Saved" / L"Config" / L"WindowsClient" /
              L"GameUserSettings.ini";
    }
    if (p) CoTaskMemFree(p);
    return out;
}

} // namespace vopt::paths