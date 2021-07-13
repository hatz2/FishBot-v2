#pragma once
#include <Windows.h>
#include <Psapi.h>

namespace Memory
{
    DWORD FindPattern(char* pattern, char* mask);
    bool Hook(void* toHook, void* ourFunc, int len);
    void Patch(BYTE* dst, BYTE* src, unsigned int size);
}