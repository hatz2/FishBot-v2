#include <Windows.h>
#include <iostream>
#include "Packetlogger.h"
#include "BotManager.h"
#include "BotMain.h"

DWORD WINAPI MainThread(LPVOID param)
{
    BotManager botManager;
    SafeQueue qRecv;

    AllocConsole();
    FILE* file = new FILE;
    freopen_s(&file, "CONOUT$", "w", stdout);

    SetConsoleTitleA("Fish Bot");
    HWND consoleHwnd = GetConsoleWindow();
    RECT ConsoleRect;
    GetWindowRect(consoleHwnd, &ConsoleRect);
    MoveWindow(consoleHwnd, ConsoleRect.left, ConsoleRect.top, 400, 400, TRUE);

    PacketManager::Initialize(&botManager);
    Packetlogger::Initialize(&qRecv);
    Packetlogger::HookRecv();

    RunBot(&qRecv, &botManager);

    Packetlogger::UnhookRecv();
    if (file != nullptr)
        fclose(file);

    FreeConsole();
    return 0;
}

BOOL APIENTRY DllMain( HMODULE hModule, DWORD  ul_reason_for_call, LPVOID lpReserved)
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
        CreateThread(0, 0, MainThread, hModule, 0, 0);
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}