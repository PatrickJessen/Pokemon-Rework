#pragma once
#include "../../../Map.h"

class ViridianCity : public Map, public ICheckpoint
{
public:
	ViridianCity(Character* player, int width, int height, int tileSize, int zoneLevel, int zoom);
	~ViridianCity();
	virtual Map* LoadNewMap() override;
	virtual Map* SpawnAtCheckpoint() override;
	virtual void Update() override;

};