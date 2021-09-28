#pragma once
#include "Scene/Scene.h"
#include "Map/Region/Kanto/Pallet Town/PalletTown.h"
#include "Character/PlayerController.h"
#include "Character/NpcController.h"
#include "Battle/BattleSystem.h"

enum class GameState { Free, TrainerBattle, PokemonBattle, Encounter, Dialog };

class GameController
{
public:
	GameController();
	~GameController();

public:
	void Update(float elapsedTime);

private:
	void ConstantUpdate(float elapsedTime);
	void WalkInDoor();
	void CheckForInteraction();
	void StartBattle();
	void ReturnToLastCheckpoint();

private:
	Scene* scene = nullptr;
	PlayerController* controller = nullptr;
	NpcController npcController;
	GameState state = GameState::Free;
	Map* nextMap = nullptr;
	DialogManager* dialogManager = nullptr;
	BattleSystem* battle = nullptr;
	bool encounterStarted = false;
	bool encountered = false;
	std::thread t1;
};

