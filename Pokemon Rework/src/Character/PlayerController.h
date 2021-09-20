#pragma once
#include "Character.h"
#include "Trainer.h"
#include "../Map/Map.h"
#include "../Dialog/DialogManager.h"

class PlayerController
{
public:
	PlayerController(Character* player, Map* map, DialogManager* manager);
	~PlayerController();

public:
	void Update();

private:
	bool TileCollision();
	void Interact();

private:
	Character* player = nullptr;
	DialogManager* manager = nullptr;
	Map* map = nullptr;
	int lastDirection = 0;
};