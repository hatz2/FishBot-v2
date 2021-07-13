#include "PacketManager.h"
#include "BotManager.h"
#include "ConsoleView.h"

#define DELAY 1000

BotManager* botManager;

std::vector<std::string> split(std::string str, char pattern);
void HandleSayi(std::vector <std::string> packetSplitted);
void HandleSay(std::vector <std::string> packetSplitted);
void HandleSr(std::vector <std::string> packetSplitted);
void HandleGuri(std::vector <std::string> packetSplitted);
void HandleSu(std::vector <std::string> packetSplitted);
void HandleEff(std::vector <std::string> packetSplitted);

void PacketManager::Initialize(BotManager* botMan)
{
    botManager = botMan;
}

void PacketManager::HandlePacket(std::string packet)
{
    int pos = packet.find('\n');
    if (pos != std::string::npos)
        packet.erase(pos);

    std::vector <std::string> packetSplitted = split(packet, ' ');

    if (packetSplitted.size() < 1) return;

    std::string opcode = packetSplitted[0];

    if (opcode == "sayi")
        HandleSayi(packetSplitted);
    else if (opcode == "say")
        HandleSay(packetSplitted);
    else if (opcode == "sr")
        HandleSr(packetSplitted);
    else if (opcode == "guri")
        HandleGuri(packetSplitted);
    else if (opcode == "su")
        HandleSu(packetSplitted);
    else if (opcode == "eff")
        HandleEff(packetSplitted);
}

std::vector<std::string> split(std::string str, char pattern) {

    int posInit = 0;
    int posFound = 0;
    std::string splitted;
    std::vector<std::string> results;

    while (posFound >= 0) {
        posFound = str.find(pattern, posInit);
        splitted = str.substr(posInit, posFound - posInit);
        posInit = posFound + 1;
        results.push_back(splitted);
    }

    return results;
}

void HandleSayi(std::vector <std::string> packetSplitted)
{
    if (!botManager->isRunning()) return;
    if (packetSplitted.size() < 5) return;
    if (packetSplitted[1] != "1") return;
    if (packetSplitted[2] != std::to_string(botManager->getPlayerID())) return;
    if (packetSplitted[4] != "2497") return;

    Sleep(DELAY);
    botManager->noMoreBait();
}

void HandleSay(std::vector <std::string> packetSplitted)
{
    if (!botManager->isRunning()) return;
    if (packetSplitted.size() < 6) return;
    if (packetSplitted[1] != "1") return;
    if (packetSplitted[2] != std::to_string(botManager->getPlayerID())) return;
    if (packetSplitted[3] != "10") return;
    if (packetSplitted[4] != "fish") return;
    if (packetSplitted[5] != "data") return;

    Sleep(DELAY);
    botManager->startFishing();
}

void HandleSr(std::vector <std::string> packetSplitted)
{
    if (packetSplitted.size() < 2) return;

    int skillID = std::atoi(packetSplitted[1].c_str());
    Console::showSkillReload(skillID);
    botManager->updateCooldown(skillID);
}

void HandleGuri(std::vector <std::string> packetSplitted)
{
    if (!botManager->isRunning()) return;
    if (packetSplitted.size() < 5) return;
    if (packetSplitted[1] != "6") return;
    if (packetSplitted[2] != "1") return;
    if (packetSplitted[3] != std::to_string(botManager->getPlayerID())) return;

    if (packetSplitted[4] == "30")
    {
        Console::showFishDetected("Normal");
        Sleep(DELAY);
        botManager->pickUpFish();
    }

    else if (packetSplitted[4] == "31")
    {
        Console::showFishDetected("Legendary");
        Sleep(DELAY);
        botManager->pickUpFish();
    }

    else if (packetSplitted[4] == "0")
    {
        Sleep(DELAY);
        botManager->startFishing();
    }
}

void HandleSu(std::vector <std::string> packetSplitted)
{
    if (packetSplitted.size() < 16) return;

    int casterID = std::atoi(packetSplitted[2].c_str());
    int skillID = std::atoi(packetSplitted[5].c_str());

    if (casterID == botManager->getPlayerID())
    {
        botManager->setOnCooldown(skillID);
    }
}

void HandleEff(std::vector <std::string> packetSplitted)
{
    if (packetSplitted.size() < 4) return;
    if (packetSplitted[1] != "1") return;
    if (packetSplitted[2] != std::to_string(botManager->getPlayerID())) return;
    if (packetSplitted[3] != "8") return;

    botManager->resetSkillCD();
}