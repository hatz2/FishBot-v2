#pragma once
#include <Windows.h>
#include <vector>
#include <string>
#include <TlHelp32.h>
#include <unordered_set>
#include <stdio.h>

std::vector<DWORD> GetPIDList(std::vector<std::wstring> processes)
{
    std::vector<DWORD> pidList;
    DWORD currentPID = GetCurrentProcessId();

    // Build a set of PIDs that have visible top-level windows
    std::unordered_set<DWORD> pidsWithWindows;

    EnumWindows([](HWND hwnd, LPARAM lParam) -> BOOL {
        if (IsWindowVisible(hwnd) && GetWindow(hwnd, GW_OWNER) == nullptr) {
            DWORD pid;
            GetWindowThreadProcessId(hwnd, &pid);
            reinterpret_cast<std::unordered_set<DWORD>*>(lParam)->insert(pid);
        }
        return TRUE;
        }, reinterpret_cast<LPARAM>(&pidsWithWindows));

    HANDLE snap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
    PROCESSENTRY32W entry;
    entry.dwSize = sizeof entry;

    if (Process32FirstW(snap, &entry)) {
        do {
            for (const auto& processName : processes) {
                if (std::wstring(entry.szExeFile) == processName &&
                    entry.th32ProcessID != currentPID &&
                    pidsWithWindows.count(entry.th32ProcessID)) //Match PID with visible windows
                {
                    pidList.emplace_back(entry.th32ProcessID);
                    break;
                }
            }
        } while (Process32NextW(snap, &entry));
    }

    CloseHandle(snap);
    return pidList;
}
