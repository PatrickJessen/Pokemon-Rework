#pragma once

class Map;

class ICheckpoint
{
public:
	virtual Map* SpawnAtCheckpoint() = 0;
};