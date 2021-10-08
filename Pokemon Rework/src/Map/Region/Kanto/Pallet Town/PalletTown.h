#pragma once
#include "../../../Map.h"
#include "../Routes/Route1.h"
#include "../../../ICheckpoint.h"

class PalletTown : public Map, public ICheckpoint
{
public:
	PalletTown(Character* player, int width, int height, int tileSize, int zoneLevel, int zoom);
	~PalletTown();
	virtual Map* LoadNewMap() override;
	virtual Map* SpawnAtCheckpoint() override;
	virtual void Update() override;

private:
	Map* route1 = nullptr;
};