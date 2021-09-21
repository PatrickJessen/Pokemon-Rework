#pragma once
#include "../Dialog/DialogManager.h"
#include "Character.h"

enum class NpcState { Idle, Walking };

class NpcController
{
public:
	NpcController(Character* character);
	~NpcController();

public:
	void Update();

private:
	Character* character;
	std::vector<int> movePattern;
	NpcState state;
	int idleTimer = 0;
	int timeBetweenWalking = 2;
};
