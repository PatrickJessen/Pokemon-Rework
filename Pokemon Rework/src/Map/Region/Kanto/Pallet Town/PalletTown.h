#pragma once
#include "../../../Map.h"
#include "../Routes/Route1.h"

class PalletTown : public Map
{
public:
	PalletTown(Character* player, int width, int height, int tileSize, int zoneLevel, int zoom);
	~PalletTown();
	virtual Map* LoadNewMap() override;
private:
	Route1* route1 = nullptr;
};