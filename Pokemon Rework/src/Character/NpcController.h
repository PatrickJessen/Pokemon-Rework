#pragma once
#include "../Dialog/DialogManager.h"
#include "Character.h"
#include <thread>
#include "../Battle/BattleSystem.h"

enum class NpcState { Idle, Walking };

class NpcController
{

public:
	void Update(Character* character, Character* player);
	bool TrainerInSight(Character* character, Character* player);
	BattleSystem* GetBattleSystem() { return battle; }
	void StartEncounter(Character* character, Character* player, DialogManager* dialog);

	bool movePatternIsDone = false;
private:
	NpcState state;
	int idleTimer = 0;
	int timeBetweenWalking = 200;
	int currentPattern = 0;
	AnimationDirection dir;
	bool isWalking = false;
	BattleSystem* battle;
	int timer = 0;
	bool encounterStarted = false;
	bool encountered = false;
};
