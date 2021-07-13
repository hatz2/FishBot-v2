#pragma once

struct Skill
{
public:
	int ID;
	bool isReady;

	Skill(int skillID) : ID(skillID), isReady(true) {};
};

class BotManager
{
public:
	BotManager();
	int getPlayerID() const;
	int getSpLevel() const;
	void noMoreBait();
	void startFishing();
	void pickUpFish();
	void updateCooldown(int skillID);
	void setOnCooldown(int skillID);
	bool isRunning() const;
	void resetSkillCD();
	void start();
	void stop();

private:
	void useSkill(Skill& skill);

private:
	int* playerID;
	int8_t* spLevel;
	bool enabled;
	bool haveBait;
	Skill throwRodSkill{ 1 };
	Skill pickUpBait{ 2 };
	Skill baitSkill{ 3 };
	Skill expSkill{ 8 };
	Skill fishLineSkill{ 9 };
	Skill proBaitSkill{ 10 };
};