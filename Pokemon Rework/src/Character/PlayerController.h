#pragma once
#include "Character.h"
#include "Trainer.h"
#include "../Map/Map.h"
#include "../Dialog/DialogManager.h"
#include "../Battle/BattleSystem.h"

class PlayerController
{
public:
	PlayerController(Character* player, Map* map);
	~PlayerController();

public:
	void Update(float elapsedTime);
	void Walk();
	BattleSystem* GetBattle() { return battle; }
private:
	bool TileCollision(TileType type);
	void Interact();
	bool IRanIntoPokemon();
	void Spawn();

private:
	Character* player = nullptr;
	Map* map = nullptr;
	BattleSystem* battle = nullptr;
	int lastDirection = 0;
	int timer = 0;
};