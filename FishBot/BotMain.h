#pragma once
#include "PacketManager.h"
#include "SafeQueue.h"
#include "BotManager.h"
#include "ConsoleView.h"

void RunBot(SafeQueue* qRecv, BotManager* botManager)
{
	bool isRunning;

	Console::showHeader();

	while (!GetAsyncKeyState(VK_F12))
	{
		isRunning = botManager->isRunning();

		while (!qRecv->empty())
		{
			std::string packet = qRecv->front();
			PacketManager::HandlePacket(packet);
			qRecv->pop();
		}

		if (GetAsyncKeyState(VK_F5) && !isRunning)
		{
			Console::showBotStarted();
			botManager->start();
			botManager->startFishing();
		}

		if (GetAsyncKeyState(VK_F8) && isRunning)
		{
			Console::showBotStopped();
			botManager->stop();
		}

		Sleep(20);
	}
}