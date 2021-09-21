#pragma once
#include "../Dialog/DialogManager.h"
#include "Character.h"
#include <thread>

enum class NpcState { Idle, Walking };

class NpcController
{

public:
	void Update(Character* character, Character* player);
	void TrainerInSight(Character* character, Character* player);

private:
	NpcState state;
	int idleTimer = 0;
	int timeBetweenWalking = 200;
	int currentPattern = 0;
	AnimationDirection dir;
	bool isWalking = false;
};
