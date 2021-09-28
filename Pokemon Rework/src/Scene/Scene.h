#pragma once
#include "../Map/Map.h"
#include "../Draw/Draw.h"
#include "../Character/Trainer.h"
#include "../Map/Checkpoint.h"

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
	Draw GetDraw() { return draw; }
	void SetNewCheckpoint();
	Map* GetLastCheckpoint();
	Checkpoint GetCheckpoint() { return checkpoint; }

private:
	int x;
	Map* current = nullptr;
	Draw draw;
	Character* player = nullptr;
	Map* lastCheckpoint = nullptr;
	Checkpoint checkpoint;
};