#include "shared_lib/json_lite.hpp"
#include <fstream>
#include <sstream>
#include <regex>

namespace vopt::json_lite {

std::expected<Doc, std::string> parse_file(const std::filesystem::path& p) {
    std::ifstream in(p);
    if (!in) return std::unexpected("cannot open " + p.string());
    std::stringstream ss; ss << in.rdbuf();
    Doc d; d.raw = ss.str();
    return d;
}

static std::string find_scalar(const std::string& raw, const std::string& key) {
    // Minimal dotted-key lookup; not a full parser. Good enough for our schema.
    std::string leaf = key;
    auto pos = leaf.find_last_of('.');
    if (pos != std::string::npos) leaf = leaf.substr(pos + 1);
    std::regex re("\"" + leaf + "\"\\s*:\\s*(\"[^\"]*\"|true|false|[0-9]+)");
    std::smatch m;
    if (std::regex_search(raw, m, re)) return m[1].str();
    return {};
}

uint32_t Doc::get_u32(const std::string& key, uint32_t def) const {
    auto v = find_scalar(raw, key);
    if (v.empty()) return def;
    try { return static_cast<uint32_t>(std::stoul(v)); } catch (...) { return def; }
}

bool Doc::get_bool(const std::string& key, bool def) const {
    auto v = find_scalar(raw, key);
    if (v.empty()) return def;
    return v == "true";
}

std::string Doc::get_str(const std::string& key, const std::string& def) const {
    auto v = find_scalar(raw, key);
    if (v.size() >= 2 && v.front() == '"' && v.back() == '"')
        return v.substr(1, v.size() - 2);
    return v.empty() ? def : v;
}

} // namespace vopt::json_lite