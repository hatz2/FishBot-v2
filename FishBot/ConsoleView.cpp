#include "ConsoleView.h"
#include <ctime>

#define INFO_HEADER "[INFO]: "

std::string getCurrentTime();

void Console::showHeader()
{
	std::string text;
	text += "-------- [Fishbot made by Hatz] --------\n\n";
	text += INFO_HEADER;
	text += "F5  => START BOT\n\n";
	text += INFO_HEADER;
	text += "F8  => STOP BOT\n\n";
	text += INFO_HEADER;
	text += "F12 => EXIT BOT\n\n";
	text += "\n---------------- [Logs] ----------------\n\n";

	std::cout << text;
}

void Console::showUseSkill(int skillID)
{
	std::string text = getCurrentTime();
	text += "Using skill ";
	text += std::to_string(skillID);
	text += "\n";

	std::cout << text;
}

void Console::showSkillReload(int skillID)
{
	std::string text = getCurrentTime();
	text += "Skill ready to use ";
	text += std::to_string(skillID);
	text += "\n";

	std::cout << text;
}

void Console::showFishDetected(std::string type)
{
	std::string text = getCurrentTime();
	text += type;
	text += " fish detected\n";

	std::cout << text;
}

void Console::showNoBait()
{
	std::string text = getCurrentTime();
	text += "You don't have enough baits\n";

	std::cout << text;
}

void Console::showBotStarted()
{
	std::string text = getCurrentTime();
	text += "Bot started\n";

	std::cout << text;
}

void Console::showBotStopped()
{
	std::string text = getCurrentTime();
	text += "Bot stopped\n";

	std::cout << text;
}

std::string getCurrentTime()
{
	time_t rawTime;
	struct tm timeInfo;
	char buffer[255];

	time(&rawTime);
	localtime_s(&timeInfo, &rawTime);

	strftime(buffer, sizeof(buffer), "%H:%M:%S", &timeInfo);
	return "[" + std::string(buffer) + "]: ";
}