#pragma once
#include <string_view>
#include <windows.h>

namespace vopt::process_scan {

bool is_running(std::wstring_view exe_name);
bool set_priority(std::wstring_view exe_name, DWORD priority_class);
DWORD find_pid(std::wstring_view exe_name);

} // namespace vopt::process_scan