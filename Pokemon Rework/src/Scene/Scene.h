#pragma once
#include "../Map/Map.h"
#include "../Draw/Draw.h"
#include "../Character/Trainer.h"

class Scene
{
public:
	Scene();
	~Scene();

public:
	void Update();
	void LoadNewScene(Map* map);

	Character* GetPlayer() { return player; }
	Map* GetMap() { return current; }

private:
	Map* current = nullptr;
	Draw* draw = nullptr;
	Character* player = nullptr;
};