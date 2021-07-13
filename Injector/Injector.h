#pragma once
#include <Windows.h>
#include <vector>

bool Inject(DWORD pid, const char* dllPath)
{
    HANDLE hProc;
    LPVOID lpAllocMem;
    HANDLE hThread;
    
    hProc = OpenProcess(PROCESS_ALL_ACCESS, 0, pid);

    if (!hProc || hProc == INVALID_HANDLE_VALUE) 
        return false;

    lpAllocMem = VirtualAllocEx(hProc, 0, MAX_PATH, MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);

    if (!lpAllocMem) 
        return false;

    WriteProcessMemory(hProc, lpAllocMem, dllPath, strlen(dllPath) + 1, 0);
    hThread = CreateRemoteThread(hProc, 0, 0, (LPTHREAD_START_ROUTINE)LoadLibraryA, lpAllocMem, 0, 0);

    if (!hThread) 
        return false;

    CloseHandle(hThread);

    if (!hProc) 
        return false;

    CloseHandle(hProc);

    return true;
}