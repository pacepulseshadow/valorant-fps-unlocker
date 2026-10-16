#pragma once
#include <filesystem>
#include <string_view>
#include <cstdint>

namespace vopt::ini {

bool set_uint(const std::filesystem::path& file,
              std::wstring_view section,
              std::wstring_view key,
              uint32_t value);

} // namespace vopt::ini