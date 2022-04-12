#include "Packetlogger.h"
#include "NostaleString.h"
#include <iostream>

#define HOOK_SIZE 5

SafeQueue* qRecv;
DWORD SendAddy;
DWORD RecvHookAddy;
DWORD TNTClient;
DWORD originalCallAddy;
DWORD jmpBackAddy;
BYTE originalBytes[10]{ 0 };

void __declspec(naked) CustomRecv()
{
	__asm
	{
		pushad;
		pushfd;
	}

	LPSTR packet;

	__asm
	{
		mov packet, edx;
	}

	qRecv->push(packet);

	__asm
	{
		popfd;
		popad;
		call originalCallAddy;
		jmp jmpBackAddy;
	}
}

void Packetlogger::Initialize(SafeQueue* safeQueue)
{
	RecvHookAddy = Memory::FindPattern(
		(char*)"\xe8\x00\x00\x00\x00\x33\xc0\x55\x68\x00\x00\x00\x00\x64\xff\x00\x64\x89\x00\x8d\x45\x00\x8b\x55",
		(char*)"x????xxxx????xx?xx?xx?xx");

	TNTClient = Memory::FindPattern(
		(char*)"\xA1\x00\x00\x00\x00\x8B\x00\xE8\x00\x00\x00\x00\xA1\x00\x00\x00\x00\x8B\x00\x33\xD2\x89\x10",
		(char*)"x????xxx????x????xxxxxx") + 1;

	SendAddy = Memory::FindPattern((char*)"\xeb\x00\xeb\x00\x39\x19\x8b\xd6", (char*)"x?x?xxxx") - 6;

	qRecv = safeQueue;

	jmpBackAddy = RecvHookAddy + HOOK_SIZE;

	DWORD callArgAddy = *(DWORD*)(RecvHookAddy + 1);
	originalCallAddy = RecvHookAddy + callArgAddy + HOOK_SIZE;
	memcpy_s(originalBytes, HOOK_SIZE, (LPVOID)RecvHookAddy, HOOK_SIZE);
}


void Packetlogger::SendPacket(LPCSTR szPacket)
{
	NostaleStringA str(szPacket);
	char* packet = str.get();

	__asm
	{
		mov eax, dword ptr ds : [TNTClient];
		mov eax, dword ptr ds : [eax];
		mov eax, dword ptr ds : [eax];
		mov eax, dword ptr ds : [eax];
		mov edx, packet;
		call SendAddy;
	}
}

void Packetlogger::HookRecv()
{
	Memory::Hook((LPVOID)RecvHookAddy, CustomRecv, HOOK_SIZE);
}

void Packetlogger::UnhookRecv()
{
	Memory::Patch((BYTE*)RecvHookAddy, originalBytes, HOOK_SIZE);
}