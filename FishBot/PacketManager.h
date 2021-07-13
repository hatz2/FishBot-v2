#pragma once
#include <Windows.h>
#include <string>
#include <vector>
#include "BotManager.h"

namespace PacketManager
{
	void Initialize(BotManager* botMan);
	void HandlePacket(std::string packet);
}