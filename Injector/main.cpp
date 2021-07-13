#include <iostream>
#include "Utils.h"
#include "Injector.h"

#define MAX_SIZE 255

int main()
{
    std::vector <std::wstring> targetProcessess = { L"NostaleClientX.exe", L"NostaleX.dat", L"CustomClient.exe" };
    std::vector <DWORD> pidList = GetPIDList(targetProcessess);
    std::string dllPath;
    char currentDirectory[MAX_SIZE] = { 0 };
    
    GetCurrentDirectoryA(MAX_SIZE, currentDirectory);

    dllPath = currentDirectory;
    dllPath += "\\FishBot.dll";

    for (auto pid : pidList)
    {
        if (Inject(pid, dllPath.c_str()))
            printf("[%d]: DLL Injected successfully.\n", pid);

        else
            printf("[%d]: DLL Injection failed.\n", pid);
    }

    printf("\n[INFO]: Injection finished.\n\n");

    for (int i = 5; i > 0; i--)
    {
        printf("[EXIT]: Closing this window in %d seconds.\n", i);
        Sleep(1000);
    }
}