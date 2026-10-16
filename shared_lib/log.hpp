#pragma once
#include <string_view>
#include <format>
#include <filesystem>

namespace vopt::log {

void init(const std::filesystem::path& file);
void shutdown();

enum class Level { Debug, Info, Warn, Error };

void write(Level lvl, std::string_view tag, std::string_view msg);

template <class... Args>
inline void info(std::string_view tag, std::format_string<Args...> fmt, Args&&... a) {
    write(Level::Info, tag, std::format(fmt, std::forward<Args>(a)...));
}

template <class... Args>
inline void warn(std::string_view tag, std::format_string<Args...> fmt, Args&&... a) {
    write(Level::Warn, tag, std::format(fmt, std::forward<Args>(a)...));
}

template <class... Args>
inline void error(std::string_view tag, std::format_string<Args...> fmt, Args&&... a) {
    write(Level::Error, tag, std::format(fmt, std::forward<Args>(a)...));
}

} // namespace vopt::log