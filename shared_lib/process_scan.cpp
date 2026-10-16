#include "shared_lib/process_scan.hpp"
#include <tlhelp32.h>
#include <cwctype>
#include <algorithm>

namespace vopt::process_scan {

static bool ieq(std::wstring_view a, std::wstring_view b) {
    if (a.size() != b.size()) return false;
    for (size_t i = 0; i < a.size(); ++i)
        if (std::towlower(a[i]) != std::towlower(b[i])) return false;
    return true;
}

DWORD find_pid(std::wstring_view exe_name) {
    HANDLE snap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
    if (snap == INVALID_HANDLE_VALUE) return 0;
    PROCESSENTRY32W pe{}; pe.dwSize = sizeof(pe);
    DWORD pid = 0;
    if (Process32FirstW(snap, &pe)) {
        do {
            if (ieq(pe.szExeFile, exe_name)) { pid = pe.th32ProcessID; break; }
        } while (Process32NextW(snap, &pe));
    }
    CloseHandle(snap);
    return pid;
}

bool is_running(std::wstring_view exe_name) { return find_pid(exe_name) != 0; }

bool set_priority(std::wstring_view exe_name, DWORD priority_class) {
    DWORD pid = find_pid(exe_name);
    if (!pid) return false;
    HANDLE h = OpenProcess(PROCESS_SET_INFORMATION, FALSE, pid);
    if (!h) return false;
    BOOL ok = SetPriorityClass(h, priority_class);
    CloseHandle(h);
    return ok == TRUE;
}

} // namespace vopt::process_scan