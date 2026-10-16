#pragma once
#include <expected>
#include <string>
#include <filesystem>
#include <cstdint>

namespace vopt::json_lite {

class Doc {
public:
    uint32_t get_u32(const std::string& key, uint32_t def) const;
    bool     get_bool(const std::string& key, bool def) const;
    std::string get_str(const std::string& key, const std::string& def) const;

    std::string raw;
};

std::expected<Doc, std::string> parse_file(const std::filesystem::path&);

} // namespace vopt::json_lite