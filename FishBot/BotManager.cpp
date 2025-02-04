#include <string>
#include "BotManager.h"
#include "Memory.h"
#include "Packetlogger.h"
#include "ConsoleView.h"

#define MAX_JOB_LEVEL 50
#define PRO_BAIT_SKILL_LEVEL 45
#define FISH_LINE__SKILL_LEVEL 25
#define EXP_SKILL_LEVEL 25
#define BAIT_SKILL_LEVEL 3
#define SKILL_DELAY 2000
#define BAIT_SKILL_ID 967
#define EXP_SKILL_ID 1007
#define FISH_LINE_SKILL_ID 1008
#define PRO_SKILL_ID 1009

BotManager::BotManager()
{
	playerID = (int*)(**(DWORD**)(Memory::FindPattern(
		(char*)"\xA1\x00\x00\x00\x00\x00\x00\x00\x00\xFF\xA1\x00\x00\x00\x00\x83\x38\x00\x76", 
		(char*)"x????????xx????xx?x") + 1) + 0x24);

	spLevel = (int8_t*)(***(DWORD***)(Memory::FindPattern(
		(char*)"\xA1\x00\x00\x00\x00\x8B\x00\x33\xD2\xE8\x00\x00\x00\x00\xB3\x01\xA1\x00\x00\x00\x00\x8B\x00\xE8\x00\x00\x00\x00\x84\xC0\x74\x21",
		(char*)"x????xxxxx????xxx????xxx????xxxx") + 1) + 0x1B4);

	haveBait = true;
	enabled = false;
}

int BotManager::getPlayerID() const
{
	if (playerID == nullptr) return 0;
	return *playerID;
}

int BotManager::getSpLevel() const
{
	if (spLevel == nullptr) return 0;
	return *spLevel;
}

void BotManager::noMoreBait()
{
	haveBait = false;
	Console::showNoBait();

	if (baitSkill.isReady)
		startFishing();
}

void BotManager::startFishing()
{
	int level = getSpLevel();

	if (level >= FISH_LINE__SKILL_LEVEL && fishLineSkill.isReady)
	{
		useSkill(fishLineSkill);
		Sleep(SKILL_DELAY);
	}

	if (level >= EXP_SKILL_LEVEL && level < MAX_JOB_LEVEL && expSkill.isReady)
	{
		useSkill(expSkill);
		Sleep(SKILL_DELAY);
	}

	if (level >= BAIT_SKILL_LEVEL && baitSkill.isReady)
	{
		useSkill(baitSkill);
		Sleep(SKILL_DELAY);
	}

	if (level >= PRO_BAIT_SKILL_LEVEL && proBaitSkill.isReady)
	{
		useSkill(proBaitSkill);
		return;
	}

	useSkill(throwRodSkill);
}

void BotManager::pickUpFish()
{
	useSkill(pickUpBait);
}

void BotManager::updateCooldown(int skillID)
{
	switch (skillID)
	{
	case 3:
		baitSkill.isReady = true;

		if (!haveBait && getSpLevel() >= BAIT_SKILL_LEVEL && enabled)
		{
			Sleep(SKILL_DELAY);
			startFishing();
		}

		break;
	case 8:
		expSkill.isReady = true;
		break;
	case 9:
		fishLineSkill.isReady = true;
		break;
	case 10:
		proBaitSkill.isReady = true;
		break;
	default:
		break;
	}
}

void BotManager::setOnCooldown(int skillID)
{
	switch (skillID)
	{
	case BAIT_SKILL_ID:
		baitSkill.isReady = false;
		break;
	case EXP_SKILL_ID:
		expSkill.isReady = false;
		break;
	case FISH_LINE_SKILL_ID:
		fishLineSkill.isReady = false;
		break;
	case PRO_SKILL_ID:
		proBaitSkill.isReady = false;
		break;
	default:
		break;
	}
}

bool BotManager::isRunning() const
{
	return enabled;
}

void BotManager::resetSkillCD()
{
	throwRodSkill.isReady = true;
	pickUpBait.isReady = true;
	baitSkill.isReady = true;
	expSkill.isReady = true;
	fishLineSkill.isReady = true;
	proBaitSkill.isReady = true;
}

void BotManager::start()
{
	enabled = true;
}

void BotManager::stop()
{
	enabled = false;
}

void BotManager::useSkill(Skill& skill)
{
	std::string packet;

	packet += "u_s ";
	packet += std::to_string(skill.ID);
	packet += " 1 ";
	packet += std::to_string(getPlayerID());

	Console::showUseSkill(skill.ID);
	Packetlogger::SendPacket(packet.c_str());
}