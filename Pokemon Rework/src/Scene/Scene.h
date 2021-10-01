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
	Checkpoint* GetCheckpoint() { return checkpoint; }
	void SetCurrent() { current = checkpoint->currentCheckpoint; }
	Map* GetCurrent() { return current; }

private:
	int x;
	Map* current = nullptr;
	const Map* current2 = nullptr;
	Draw draw;
	Character* player = nullptr;
	Map* lastCheckpoint = nullptr;
	Checkpoint* checkpoint;
};