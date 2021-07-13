#include "Memory.h"

MODULEINFO GetModuleInfo()
{
    MODULEINFO modinfo = { 0 };
    HMODULE hModule = GetModuleHandle(NULL);

    if (hModule == 0)
        return modinfo;

    GetModuleInformation(GetCurrentProcess(), hModule, &modinfo, sizeof(MODULEINFO));
    return modinfo;
}

DWORD Memory::FindPattern(char* pattern, char* mask)
{
    MODULEINFO mInfo = GetModuleInfo();
    DWORD base = (DWORD)mInfo.lpBaseOfDll;
    DWORD size = (DWORD)mInfo.SizeOfImage;

    DWORD patternLength = strlen(mask);

    for (DWORD i = 0; i < size - patternLength; i++)
    {
        bool found = true;
        for (DWORD j = 0; j < patternLength; j++)
            found &= mask[j] == '?' || pattern[j] == *(char*)(base + i + j);

        if (found)
            return base + i;
    }

    return NULL;
}

bool Memory::Hook(void* toHook, void* ourFunc, int len)
{
    if (len < 5) return false;

    DWORD curProtection;
    VirtualProtect(toHook, len, PAGE_EXECUTE_READWRITE, &curProtection);

    memset(toHook, 0x90, len);

    DWORD relativeAdress = ((DWORD)ourFunc - (DWORD)toHook) - 5;

    *(BYTE*)toHook = 0xE9;
    *(DWORD*)((DWORD)toHook + 1) = relativeAdress;

    DWORD temp;
    VirtualProtect(toHook, len, curProtection, &temp);

    return true;
}

void Memory::Patch(BYTE* dst, BYTE* src, unsigned int size)
{
    DWORD oldprotect;
    VirtualProtect(dst, size, PAGE_EXECUTE_READWRITE, &oldprotect);

    memcpy(dst, src, size);
    VirtualProtect(dst, size, oldprotect, &oldprotect);
}