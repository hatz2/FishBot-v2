#pragma once
#include <iostream>
#include <string>

namespace Console
{
	void showHeader();
	void showUseSkill(int skillID);
	void showSkillReload(int skillID);
	void showFishDetected(std::string type);
	void showNoBait();
	void showBotStarted();
	void showBotStopped();
}