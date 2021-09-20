#pragma once
#include "Scene/Scene.h"
#include "Map/Region/Kanto/Pallet Town/PalletTown.h"
#include "Character/PlayerController.h"

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

private:
	Scene* scene = nullptr;
	PlayerController* controller = nullptr;
	GameState state = GameState::Free;
	Map* nextMap = nullptr;
};

