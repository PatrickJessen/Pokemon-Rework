#pragma once
#include "Character.h"
#include "Trainer.h"
#include "../Map/Map.h"
#include "../Dialog/DialogManager.h"

class PlayerController
{
public:
	PlayerController(Character* player, Map* map);
	~PlayerController();

public:
	void Update(float elapsedTime);
	void Walk();
private:
	bool TileCollision();
	bool NPCCollision();
	void Interact();

private:
	Character* player = nullptr;
	Map* map = nullptr;
	int lastDirection = 0;
	int timer = 0;
};