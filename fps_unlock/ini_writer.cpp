#include "fps_unlock/ini_writer.hpp"
#include <windows.h>
#include <string>

namespace vopt::ini {

bool set_uint(const std::filesystem::path& file,
              std::wstring_view section,
              std::wstring_view key,
              uint32_t value) {
    std::wstring v = std::to_wstring(value);
    return WritePrivateProfileStringW(
        std::wstring(section).c_str(),
        std::wstring(key).c_str(),
        v.c_str(),
        file.wstring().c_str()) == TRUE;
}

} // namespace vopt::ini