#pragma once
#include "Character.h"
#include "Trainer.h"
#include "../Map/Map.h"

class PlayerController
{
public:
	PlayerController(Character* player, Map* map);
	~PlayerController();

public:
	void Update();

private:
	bool TileCollision();

private:
	Character* player = nullptr;
	Map* map = nullptr;
	int lastDirection = 0;
};