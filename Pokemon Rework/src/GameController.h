#pragma once
#include "Scene/Scene.h"
#include "Map/Region/Kanto/Pallet Town/PalletTown.h"
#include "Character/PlayerController.h"
#include "Character/NpcController.h"
#include "Battle/BattleSystem.h"

enum class GameState { Free, Battle, Dialog };

class GameController
{
public:
	GameController();
	~GameController();

public:
	void Update();

private:
	void ConstantUpdate();
	void WalkInDoor();
	void CheckForInteraction();

private:
	Scene* scene = nullptr;
	PlayerController* controller = nullptr;
	NpcController npcController;
	GameState state = GameState::Free;
	Map* nextMap = nullptr;
	DialogManager* dialogManager = nullptr;
	BattleSystem* battle;
};

