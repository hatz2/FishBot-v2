#pragma once
#include <Windows.h>
#include <vector>
#include <string>
#include <TlHelp32.h>

std::vector <DWORD> GetPIDList(std::vector <std::wstring> processes)
{
    std::vector<DWORD> pidList;
    DWORD currentPID = GetCurrentProcessId();

    HANDLE snap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);

    PROCESSENTRY32W entry;
    entry.dwSize = sizeof entry;

    if (Process32FirstW(snap, &entry))
    {
        do
        {
            for (auto processName : processes)
            {
                if (std::wstring(entry.szExeFile) == processName && entry.th32ProcessID != currentPID)
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